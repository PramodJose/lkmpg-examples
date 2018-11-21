/*
**	First try at building a character device. Creates a read-only character device that says how many times it has been read from.
**	Author: algorhythm (pramodgeorgejose@am.students.amrita.edu).
**	Date: 21 -11 -2018.
**	Adapted from: https://www.tldp.org/LDP/lkmpg/2.4/html/c577.htm (LKMPG)
**	Kernel Version: 4.15.0-39-generic
*/

#include <linux/module.h>		// Because this is a kernel module! :)
#include <linux/kernel.h>		// For KERN_INFO
#include <linux/init.h>			// For the __init and __exit macros
#include <linux/fs.h>			// For the file operations struct; used while registering the device.
#include <linux/uaccess.h>		// In the LKMPG code, this has been included as asm/uaccess.h. But this header file is actually under linux
					// (it may have been moved here in this version of the kernel). It is used for put_user().
#include <uapi/asm-generic/errno.h>	// In the LKMPG code, this has been included as asm/errno.h. But now, it is present under uapi/asm-generic/.
					// It has probably been moved here. Note: There is an errno.h under linux also, but that does not provide the
					// definitions for EBUSY and EINVAL; which we need in this module.


#define SUCCESS 0
#define DEV_NAME "chardev"		// Name of the device as it would appear under /proc/devices (does this location exist?)
#define BUF_LEN 80


// Some metadata about our module...
MODULE_AUTHOR("algorhythm; (pramodgeorgejose@am.students.amrita.edu)");
MODULE_DESCRIPTION("First try at building a character device");
MODULE_LICENSE("GPL");


// Forward declaractions...
static int __init initializer(void);
static void __exit cleaner(void);

	// The following definitions have been looked up on elixir.bootlin.com. Search for "file_operations" under fs.h.
	// These are the functions of the device that we would be implementing.
static int dev_open (struct inode *, struct file *);
static int dev_release (struct inode *, struct file *);
static ssize_t dev_read (struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_write (struct file *, const char __user *, size_t, loff_t *);


// Registering our init and exit functions...
module_init(initializer);
module_exit(cleaner);


// Some global variables..
static struct file_operations fops = 
{
	.open = dev_open,
	.release = dev_release,
	.read = dev_read,
	.write = dev_write
};	// provide the address of each of our functions in an instance of file_operations structure.

static int major;
static bool dev_opened = false; 


static int __init initializer(void)
{
	major = register_chardev(0, DEV_NAME, &fops);		// This function has been defined in fs.h
	printk(KERN_INFO "Inserting character device module..\n");
	return SUCCESS;
}

static void __exit cleaner(void)
{
	int ret_val = unregister_chrdev(major, DEV_NAME);	// This function has been defined in fs.h
	if(ret_val < 0)
		printk(KERN_ALERT "Error while unregistering device %d, %s. Error code: %d\n", major, DEV_NAME, ret_val);
	else
		printk(KERN_INFO "The character device %s has now been removed.\n", DEV_NAME);
}

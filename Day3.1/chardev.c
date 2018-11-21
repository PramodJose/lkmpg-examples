/*
**	First try at building a character device.
**	Author: algorhythm (pramodgeorgejose@am.students.amrita.edu).
**	Date: 21 -11 -2018.
**	Adapted from: https://www.tldp.org/LDP/lkmpg/2.4/html/c577.htm (LKMPG)
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


// ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);

// Registering our init and exit functions...
module_init(initializer);
module_exit(cleaner);



static struct file_operations fops = 
{
	.read = 
}

static int __init initializer(void)
{
	printk(KERN_INFO "Inserting character device module..\n");
	return SUCCESS;
}

static void __exit cleaner(void)
{
	printk(KERN_INFO "The character device has now been removed completely\n");
}

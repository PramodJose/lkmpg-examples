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
					// definitions for EBUSY and EINVAL; which we need in this module. There are other errno.h files, but, I found only this
					// one working as expected.
#include <linux/umh.h>			// Can also include kmod.h; it includes this header. 


#define SUCCESS 0
#define DEV_NAME "chrdev"		// Name of the device as it would appear under /proc/devices (does this location exist?)
#define PATH_TO_DEV "/dev/" DEV_NAME // Path to device file
#define BUF_LEN 80


// Some metadata about our module...
MODULE_AUTHOR("algorhythm; (pramodgeorgejose@am.students.amrita.edu)");
MODULE_DESCRIPTION("First try at building a character device");
MODULE_LICENSE("GPL");


// Forward declaractions...
static int __init initializer(void);
static void __exit cleaner(void);

	// The following definitions have been looked up on elixir.bootlin.com. Search for "file_operations"
	// under fs.h for the prototypes. These are the functions of the device that we would be implementing.
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
	.open = dev_open,			// provide the address of each of our functions in an instance
	.release = dev_release,		// of file_operations structure. We will use this struct 
	.read = dev_read,			// while registering our device.
	.write = dev_write
};

static int major;/*, minor = 0;
static char msg[BUF_LEN], *msg_ptr;*/


static int __init initializer(void)
{
	major = register_chrdev(0, DEV_NAME, &fops);		// This function has been defined in fs.h.  0 means that the kernel will assign
														// the next available major number to our device; which is returned to us.
	if (major < 0)
	{
		printk(KERN_ALERT "Error while registering character device. Error code: %d", major);
		printk(KERN_INFO);								// Used to flush the printk output buffer
		return major;
	}
	else
	{		
		char major_str[8] = "";
		char *exec_cmd = "mknod", *exec_argv[]={PATH_TO_DEV, "c", major_str, "0", NULL}, *exec_envp[] = {"HOME=/", NULL };
		int ret_val;

		snprintf(major_str, 8, "%d", major);
		ret_val = call_usermodehelper(exec_cmd, exec_argv, exec_envp, UMH_WAIT_PROC);

		if(ret_val < 0)
			printk(KERN_ALERT "Error while creating device file: %s.\nThis is not an error as such. Error code: %d\
				\nJust run sudo mknod %s c %d 0\nMajor number: %d", PATH_TO_DEV, ret_val, PATH_TO_DEV, major, major);
		else
			printk(KERN_INFO "Successfully registered character device and created file: %s.\nMajor number: %d", PATH_TO_DEV, major);

		printk(KERN_INFO);								// Used to flush the printk output buffer
		return SUCCESS;
	}
}

static void __exit cleaner(void)
{
	char *exec_cmd = "rm", *exec_argv[]={PATH_TO_DEV, NULL}, *exec_envp[] = {"HOME=/", NULL };
	int ret_val;

	unregister_chrdev(major, DEV_NAME);				// This function has been defined in fs.h
	ret_val = call_usermodehelper(exec_cmd, exec_argv, exec_envp, UMH_WAIT_PROC);

	if(ret_val < 0)
		printk(KERN_ALERT "The char dev has been unregistered, but failed to remove the device file: %s\
			\nThis is not an error as such. Error code: %d. Just run sudo rm %s", PATH_TO_DEV, ret_val, PATH_TO_DEV);
	else
		printk(KERN_INFO "The character device %s has now been removed completely.", DEV_NAME);

	printk(KERN_INFO);								// Used to flush the printk output buffer
}

static int dev_open (struct inode *inodep, struct file *filp)
{
	return 0;
}

static int dev_release (struct inode *inodep, struct file *filp)
{
	return 0;
}

static ssize_t dev_read (struct file *filp, char __user *buf, size_t len, loff_t * offset)
{
	return 0;
}

static ssize_t dev_write (struct file *filp, const char __user *buf, size_t len, loff_t *offset)
{
	return 0;
}

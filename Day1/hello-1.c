#include <linux/kernel.h>		// For KERN_INFO
#include <linux/module.h>		// Required by all kernel modules

int init_module()
{
	printk(KERN_INFO "Hello world 1\n");

	return 0;		// Always needs to return an integer which would indicate a successful/unsuccessful load
}

void cleanup_module()
{
	printk(KERN_INFO "Goodbye world\n");
}
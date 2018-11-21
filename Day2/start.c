#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init custom_init(void)
{
	printk(KERN_INFO "Hello world 6!\n");
	return 0;
}

module_init(custom_init);
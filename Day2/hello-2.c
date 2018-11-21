#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init custom_init(void)
{
	printk(KERN_INFO "Hello world 2\n");

	return 0;
}

static void __exit custom_cleanup(void)
{
	printk(KERN_INFO "Goodby world 2\n");
}

module_init(custom_init);
module_exit(custom_cleanup);
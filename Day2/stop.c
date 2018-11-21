#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static void __exit custom_cleanup(void)
{
	printk(KERN_INFO "Goodbye World 6\n");
}

module_exit(custom_cleanup);
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __initdata count= 5;

static int __init custom_init(void)
{
	printk(KERN_INFO "Hello world 3: %d!\n", count);

	return 0;
}

static void __exit custom_cleanup(void)
{
	printk(KERN_INFO "Goodbye world 3!\n");
}

module_init(custom_init)
module_exit(custom_cleanup)

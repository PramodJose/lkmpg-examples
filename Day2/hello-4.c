#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init custom_init(void)
{
	printk(KERN_INFO "Hello world 4\n");
	return 0;
}

static void __exit custom_cleanup(void)
{
	printk(KERN_INFO "Goodbye world 4\n");
}

module_init(custom_init);
module_exit(custom_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Algorhythm");
MODULE_DESCRIPTION("A test module");
MODULE_SUPPORTED_DEVICE("Any test device");
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fdtable.h>
#include <linux/sched.h>

static int __init custom_init(void)
{
	printk(KERN_INFO "sizeof: %ld\n", sizeof(struct task_struct));
	return 0;
}

static void __exit custom_cleanup(void)
{
	printk(KERN_INFO "Exiting sizeof() test..\n");
}

module_init(custom_init);
module_exit(custom_cleanup);
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#define MAX_STR 101
#define MAX_INT_ARR 5

MODULE_LICENSE("GPL");

int integer = 10;
char cmdLineMsg[MAX_STR] = "ABCD";
int arr[MAX_INT_ARR] = {-6, 7}, count_int = MAX_INT_ARR;

module_param(integer, int, 0);
module_param_string(charp, cmdLineMsg, MAX_STR, 0);
module_param_array(arr, int, &count_int, 0);

static int __init custom_init(void)
{
	int i;
	printk(KERN_INFO "Hello world 5!\n");
	printk(KERN_INFO "Int: %d, String: %s\nThe array is:-\n", integer, cmdLineMsg);

	for(i = 0; i < count_int; ++i)
		printk(KERN_INFO "%d ", arr[i]);
	printk(KERN_INFO);

	return 0;
}

static void __exit custom_exit(void)
{
	printk(KERN_INFO "Goodbye world 5\n");
}

module_init(custom_init);
module_exit(custom_exit);


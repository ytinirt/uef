/*
 *
 *
 * ZHAO Yao soarsky@foxmail.com
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZHAO Yao");

int
temp(void)
{

	return 0;
}

static int
temp_init(void)
{
	int ret = 0;
	printk(KERN_ALERT "temp.ko has insmod\n");
	ret = temp();
	return ret;
}

static void
temp_exit(void)
{
	printk(KERN_ALERT "temp.ko has rmmod\n");
}

module_init(temp_init);
module_exit(temp_exit);

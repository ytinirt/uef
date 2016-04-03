/*
 *
 *
 * ZHAO Yao ytinirt@qq.com
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/string.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZHAO Yao");

#define DEVICE_NAME "rx_pool"

static void *buffer = NULL;

static int uef_mod_open(struct inode *n, struct file *f)
{
    return 0;
}

static int uef_mod_map(struct file *f, struct vm_area_struct *vma)
{
    unsigned long page;
    unsigned long start = vma->vm_start;
    unsigned long size = vma->vm_end - vma->vm_start;

    /* get physic address */
    page = virt_to_phys(buffer);
    if (remap_pfn_range(vma, start, page >> PAGE_SHIFT, size, PAGE_SHARED) != 0) {
        return -1;
    }

    strcpy(buffer, "Hello World, this is skb speaking.");

    return 0;
}

static struct file_operations dev_fops = {
    .owner = THIS_MODULE,
    .open = uef_mod_open,
    .mmap = uef_mod_map,
};

static struct miscdevice misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &dev_fops,
};

static int __init uef_mod_init(void)
{
    int ret = -1, ret2 = -1;

    /* reg. misc device */
    ret = misc_register(&misc);
    if (ret != 0) {
        printk(KERN_WARNING "misc_register failed: %d\n", ret);
        goto err_out;
    }

    /* alloc memory */
    buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);
    if (buffer == NULL) {
        printk(KERN_WARNING "kmalloc %lx bytes failed\n", PAGE_SIZE);
        goto err_out1;
    }

    return ret;

err_out1:
    ret2 = misc_deregister(&misc);
    if (ret2 != 0) {
        printk(KERN_WARNING "misc_deregister failed: %d\n", ret2);
    }
err_out:
    return ret;
}

static void __exit uef_mod_exit(void)
{
    int ret = -1;

    ret = misc_deregister(&misc);
    if (ret != 0) {
        printk(KERN_WARNING "misc_deregister failed: %d\n", ret);
    }

    kfree(buffer);
}

module_init(uef_mod_init);
module_exit(uef_mod_exit);


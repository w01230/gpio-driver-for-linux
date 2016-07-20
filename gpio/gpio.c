/**
 * drviers/gpio/gpio.c
 *
 * History:
 *   2011/6/29  - [W.J] created file
 *   2011/7/14  - [W.J] add GPIO read
 *   2011/8/13  - [W.J] add GPIO interrupt
 *   2011/10/12 - [W.J] add SIGNAL notice
 *   2011/11/05 - [W.J] add POLL,remove SIGNAL notice 
 *   2012/7/16  - [W.J] move irq request to device open.
 *   2014/6/11  - [W.J] remove interrrupt poll.
 *   2016/7/20  - [W.J] change header file including
 * Copyright (C) 2009-201666666, WJ@SHANGHAI, Inc.
 *
 * GPIO driver
 *
 */
 
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/interrupt.h> 
#include <linux/device.h>
#include <linux/seq_file.h>
#include <linux/delay.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/gpio.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/poll.h>

#include "gpio.h"

struct gpio_dev {
	struct cdev cdev;
};

struct gpio_dev *devp;

/*OPEN*/
static int gpio_open(struct inode *inode, struct file *filp)
{	
	int ret = 0;
	
	filp->private_data = devp; 
	
	return ret;
}

/*RELEASE*/
static int gpio_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/*READ*/
static ssize_t gpio_read(struct file *filp, char __user *buff, 
							size_t count, loff_t *offp)
{
	return 0;
}

/*IOCTL*/
static long gpio_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned int ret = 0;
		
	if (_IOC_TYPE(cmd) != IOCTL_MAGIC) 
		return -EINVAL;

	if (arg > 95)
		return -EINVAL;
		
	switch(cmd) {
	case GPIO_OUT_LOW:
		gpio_direction_output(arg,0);
		break;

	case GPIO_OUT_HIG:
		gpio_direction_output(arg,1);
		break;

	case GPIO_INPUT:
		gpio_direction_input(arg);
		ret = gpio_get_value(arg);
		break;
		
	default:
		ret = -EINVAL;
		break;
	}
		
	return ret;
}

static struct file_operations gpio_fops = {
	.owner = THIS_MODULE,
	.open = gpio_open,
	.release = gpio_release,
	.read = gpio_read,
	.unlocked_ioctl = gpio_ioctl,

}; 

/*DEV SETUP*/
static void gpio_setup(struct gpio_dev *dev,int index)
{
	int err = 0;
	int devno = MKDEV(GPIO_MAJOR, index);
	
	cdev_init(&dev->cdev, &gpio_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &gpio_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk("add gpio setup failed!\n"); 
}


/*DEV INIT*/
struct class *gpio_class;

static int __init gpio_init(void)
{
	int ret;
	unsigned int gpio_major;
	dev_t devno = MKDEV(GPIO_MAJOR, 0);			//申请次设备号
	
	printk("init gpio driver module...\n");
		
	if (devno) {
		ret = register_chrdev_region(devno, 1, DEVICE_NAME);		//申请设备注册 
	} else {
		ret = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME); 
		gpio_major = MAJOR(devno); 
		printk(KERN_INFO "Todo: mknod /dev/%s c %d 0\n", DEVICE_NAME, 
				gpio_major);
	}
	
	if (ret < 0) {
		printk("err: failed in registering dev.\n");
		return ret;
	}
			
	devp = kmalloc(sizeof(struct gpio_dev), GFP_KERNEL);		//申请内存
	memset(devp, 0, sizeof(struct gpio_dev));
	gpio_setup(devp, 0);
	
	gpio_class = class_create(THIS_MODULE, DEVICE_NAME);
	if (IS_ERR(gpio_class)) {
		printk("err: failed in creating class.\n");
		return -1;
	}
	
	device_create(gpio_class, NULL, MKDEV(GPIO_MAJOR, 0), 
					NULL, DEVICE_NAME "%d", 0);			//创建设备节点

	return ret;
}

/*DEV EXIT*/
static void __exit gpio_exit(void)
{
	cdev_del(&devp->cdev);
	kfree(devp);
	unregister_chrdev_region(MKDEV(GPIO_MAJOR, 0), 1);
	device_destroy(gpio_class,MKDEV(GPIO_MAJOR, 0));
	class_destroy(gpio_class);
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WJ@SHANGHAI");
MODULE_DESCRIPTION("GPIO driver for test");


/*****************************************************************************************
*@Filename          ultrasonic.c
*@Author            zulongp
*@Des
*@History
*                Original vrsion, 16-Jul, 2013
*                program modify,  16-Jul, 2013
****************************************************************************************/
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/ioctl.h>

#include <asm/io.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("zlpan");
MODULE_DESCRIPTION("Ultrasonic driver of Smart car");
MODULE_VERSION("V1.0");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "ultrasonic"
#define ULTRASONIC_PHY_ADDR 0x6E000000

#define ULTRASONIC_STATUS_OFFSET 0
#define ULTRASONIC_ECHO1_OFFSET  0x04
#define ULTRASONIC_ECHO2_OFFSET  0x08
#define ULTRASONIC_ECHO3_OFFSET  0x0C
#define ULTRASONIC_MOSI_OFFSET   0x10
#define ULTRASONIC_MISO_OFFSET   0x14

#define ULTRASONIC_IOC_MAGIC    'Z' 

#define ULTRASONIC_STATUS_WRITE _IOW(ULTRASONIC_IOC_MAGIC, 1, int)
#define ULTRASONIC_STATUS_READ  _IOR(ULTRASONIC_IOC_MAGIC, 2, int)
#define ULTRASONIC_ECHO1_READ   _IOR(ULTRASONIC_IOC_MAGIC, 3, int)
#define ULTRASONIC_ECHO2_READ   _IOR(ULTRASONIC_IOC_MAGIC, 4, int)
#define ULTRASONIC_ECHO3_READ   _IOR(ULTRASONIC_IOC_MAGIC, 5, int)
#define ULTRASONIC_MOSI_READ    _IOR(ULTRASONIC_IOC_MAGIC, 6, int)
#define ULTRASONIC_MOSI_WRITE   _IOW(ULTRASONIC_IOC_MAGIC, 7, int)

#define ULTRASONIC_IOC_MAXNR     10

static int ultrasonic_major = 0;
static unsigned long base_addr = 0;
static struct class* ultrasonic_class = NULL;
static struct device* ultrasonic_device = NULL;

static ssize_t ultrasonic_open(struct inode *inode, struct file *file)
{
	printk("open success\n");
	return 0;
}
static ssize_t ultrasonic_release(struct inode *inode, struct file *file)
{
	return 0;
}
//static ssize_t ultrasonic_ioctl(struct inode *inode, struct file *file, 
static ssize_t ultrasonic_ioctl(struct file *file, 
								unsigned int cmd,
								unsigned long arg)
{
	u32 data = 0;
	int err = 0,ret = 0;
	if(_IOC_TYPE(cmd) != ULTRASONIC_IOC_MAGIC)return -ENOTTY;
	if(_IOC_NR(cmd) > ULTRASONIC_IOC_MAXNR) return -ENOTTY;

	if(_IOC_DIR(cmd) &_IOC_READ)
		err = !access_ok(VERIFY_WRITE,(void __user*)arg, _IOC_SIZE(cmd));
	else if(_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_READ, (void __user *)arg,_IOC_SIZE(cmd));
	if(err) return -EFAULT;
	switch(cmd)
	{
	case ULTRASONIC_STATUS_WRITE:
		ret = __get_user(data, (u32 *)arg);
		iowrite32(data, base_addr + ULTRASONIC_STATUS_OFFSET);
		break;
	case ULTRASONIC_STATUS_READ:
		//printk("data = %d\n",data);
		data = ioread32(base_addr + ULTRASONIC_STATUS_OFFSET);
		ret = __put_user(data, (u32 *)arg);
		printk("statuse = 0x%x\n",data);
		break;
	case ULTRASONIC_ECHO1_READ:
		data = ioread32(base_addr + ULTRASONIC_ECHO1_OFFSET);
		ret = __put_user(data, (u32 *)arg);
		iowrite32(0, base_addr + ULTRASONIC_ECHO1_OFFSET);
		printk("echo1 data = 0x%x\n",data);
		break;
	case ULTRASONIC_ECHO2_READ:
		data = ioread32(base_addr + ULTRASONIC_ECHO2_OFFSET);
		ret = __put_user(data, (u32 *)arg);
		iowrite32(0, base_addr + ULTRASONIC_ECHO2_OFFSET);
		printk("echo2 data = %d\n",data);
		break;
	case ULTRASONIC_ECHO3_READ:
		data = ioread32(base_addr + ULTRASONIC_ECHO3_OFFSET);
		ret = __put_user(data, (u32 *)arg);
		iowrite32(0, base_addr + ULTRASONIC_ECHO3_OFFSET);
		printk("echo3 data = %d\n",data);
		break;
	case ULTRASONIC_MOSI_WRITE:
		ret = __get_user(data, (u32 *)arg);
		//printk("ret = %d data = %d\n",ret,data);
		iowrite32(data, base_addr + ULTRASONIC_MOSI_OFFSET);
		break;
	case ULTRASONIC_MOSI_READ:
		data = ioread32(base_addr +  ULTRASONIC_MOSI_OFFSET);
		ret = __put_user(data, (u32 *)arg);
		break;
	default:
		break;
	}
	return 0;
}
static struct file_operations ultrasonic_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = ultrasonic_ioctl,
	.open = ultrasonic_open,
	.release = ultrasonic_release,
};
static int __init ultrasonic_init(void) 
{
	int ret;
	ret = register_chrdev(0,DEVICE_NAME, &ultrasonic_fops);
	if(ret < 0)
	{
		printk("ultrasonic: can't get major number\n");
		return ret;
	}
	ultrasonic_major = ret;
	ultrasonic_class = class_create(THIS_MODULE, "ultrasonic_class");
	if(IS_ERR(ultrasonic_class))
	{
		printk("ultrasonic: failed in creating class\n");
		unregister_chrdev(ultrasonic_major, DEVICE_NAME);
		return -1;
	}
	ultrasonic_device = device_create(ultrasonic_class,\
									  NULL, \
									  MKDEV(ultrasonic_major, 0), \
									  NULL,\
									  DEVICE_NAME);
	if(IS_ERR(ultrasonic_device))
	{
		printk("ultrasonic: failed in creating device!\n");
		unregister_chrdev(ultrasonic_major, DEVICE_NAME);
		class_unregister(ultrasonic_class);
		class_destroy(ultrasonic_class);
		return -1;
	}
	base_addr = (unsigned long) ioremap(ULTRASONIC_PHY_ADDR, sizeof(u32));
	printk("Ultrasonic initail successfully\n");
	return 0;
}
static void __exit ultrasonic_exit(void)
{
  device_destroy(ultrasonic_class, MKDEV(ultrasonic_major, 0));
  class_unregister(ultrasonic_class);
  class_destroy(ultrasonic_class);
  unregister_chrdev(ultrasonic_major, DEVICE_NAME);
  printk("ultrasonic module exit.\n");
}
module_init(ultrasonic_init);
module_exit(ultrasonic_exit);

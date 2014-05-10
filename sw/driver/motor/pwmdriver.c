#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/io.h>

#define DEVICE_NAME "device"
#define MYPWM_PHY_ADDR 0x43c00000
#define MYGPIO_PHY_ADDR 0x41200000

MODULE_AUTHOR("zlpan");
MODULE_DESCRIPTION("pwm dirver");
MODULE_VERSION("v1.0");
MODULE_LICENSE("GPL");

static int pwm_major;
static struct class* pwm_class = NULL;
static struct device* pwm_device = NULL;

unsigned long mypwm_addr = 0;
unsigned long mygpio_addr = 0;

static struct file_operations pwm_fops = {
    .owner = THIS_MODULE,
};

static ssize_t sys_direction_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	//set the direction of gpio
    printk("gpio must be output\n");
    return count;
}

/**
  *value:set the direction of pwm1-4
  *bit[7-4]: set the direction of pwm4~1
  *          if eq 1 back else front
  *bit[3-0]: set the light
  **/
static ssize_t sys_value_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    unsigned char num = 0;
	sscanf(buf,"%x",&num);
	outb(num,mygpio_addr);
    return count;
}
/**
 *set the speed of pwn+x
 *if bit[31]=0 stop
 *else go
 */
static ssize_t sys_pwm1_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    outl(num == 0 ? 0 : (num | 0x80000000), mypwm_addr);
    return count;
}
static ssize_t sys_pwm2_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    outl(num == 0 ? 0 : (num | 0x80000000), mypwm_addr + 4);
    return count;
}
static ssize_t sys_pwm3_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    outl(num == 0 ? 0 : (num | 0x80000000), mypwm_addr + 8);
    return count;
}
static ssize_t sys_pwm4_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    outl(num == 0 ? 0 : (num | 0x80000000), mypwm_addr + 12);
    return count;
}
static DEVICE_ATTR(direction, S_IWUSR, NULL, sys_direction_set);             //GPIO input or output, we set output as default
static DEVICE_ATTR(value, S_IWUSR, NULL, sys_value_set);             //GPIO output
static DEVICE_ATTR(pwm1_speed, S_IWUSR, NULL, sys_pwm1_speed_set);
static DEVICE_ATTR(pwm2_speed, S_IWUSR, NULL, sys_pwm2_speed_set);
static DEVICE_ATTR(pwm3_speed, S_IWUSR, NULL, sys_pwm3_speed_set);
static DEVICE_ATTR(pwm4_speed, S_IWUSR, NULL, sys_pwm4_speed_set);

static int __init mydriver_module_init(void)
{
    int ret;

    pwm_major=register_chrdev(0, DEVICE_NAME, &pwm_fops);
    if (pwm_major < 0){
        printk("failed to register device.\n");
        return -1;
    }

    pwm_class = class_create(THIS_MODULE, "pwm_class");
    if (IS_ERR(pwm_class)){
        printk("failed to create device class.\n");
        unregister_chrdev(pwm_major, DEVICE_NAME);
        return -1;
    }


    pwm_device = device_create(pwm_class, NULL, MKDEV(pwm_major, 0), NULL, "pwm_device");
    if (IS_ERR(pwm_device)){
        printk("failed to create device .\n");
        unregister_chrdev(pwm_major, DEVICE_NAME);
        return -1;
    }

    ret = device_create_file(pwm_device, &dev_attr_direction);
    if (ret < 0)
        printk("failed to create /sys endpoint");
    
    ret = device_create_file(pwm_device, &dev_attr_value);
    if (ret < 0)
        printk("failed to create /sys endpoint");
    
    ret = device_create_file(pwm_device, &dev_attr_pwm1_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    ret = device_create_file(pwm_device, &dev_attr_pwm2_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");
    
    ret = device_create_file(pwm_device, &dev_attr_pwm3_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");
    
    ret = device_create_file(pwm_device, &dev_attr_pwm4_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    mypwm_addr = (unsigned long)ioremap(MYPWM_PHY_ADDR, sizeof(u32));
    mygpio_addr = (unsigned long)ioremap(MYGPIO_PHY_ADDR, sizeof(u32));
    outb(0x00, mygpio_addr+4);
    outb(0x55, mygpio_addr);

    printk("my pwm driver initial successfully!\n");
    return 0;
}

static void __exit mydriver_module_exit(void)
{
    device_remove_file(pwm_device, &dev_attr_direction);
    device_remove_file(pwm_device, &dev_attr_value);
    device_remove_file(pwm_device, &dev_attr_pwm1_speed);
    device_remove_file(pwm_device, &dev_attr_pwm2_speed);
    device_remove_file(pwm_device, &dev_attr_pwm3_speed);
    device_remove_file(pwm_device, &dev_attr_pwm4_speed);
    device_destroy(pwm_class, MKDEV(pwm_major, 0));
    class_unregister(pwm_class);
    class_destroy(pwm_class);
    unregister_chrdev(pwm_major, DEVICE_NAME);
    printk("pwm module exit.\n");
}

module_init(mydriver_module_init);
module_exit(mydriver_module_exit);

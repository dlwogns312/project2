#include <linux/init.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/ioctl.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/timer.h>

//define major number and device driver name
#define DEVICE_MAJOR 242
#define DEVICE_NAME "dev_driver"

//unsigned char array for name and student id
unsigned char id[8]="20171670";
unsigned char user_name[10]="LEEJAEHOON";

//physical address
#define FND_ADDRESS 0x08000004 
#define LED_ADDRESS 0x08000016
#define DOT_ADDRESS 0x08000210
#define LCD_ADDRESS 0x08000090

//fpga_dot_header
unsigned char fpga_number[10][10] = {
	{0x3e,0x7f,0x63,0x73,0x73,0x6f,0x67,0x63,0x7f,0x3e}, // 0
	{0x0c,0x1c,0x1c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x1e}, // 1
	{0x7e,0x7f,0x03,0x03,0x3f,0x7e,0x60,0x60,0x7f,0x7f}, // 2
	{0xfe,0x7f,0x03,0x03,0x7f,0x7f,0x03,0x03,0x7f,0x7e}, // 3
	{0x66,0x66,0x66,0x66,0x66,0x66,0x7f,0x7f,0x06,0x06}, // 4
	{0x7f,0x7f,0x60,0x60,0x7e,0x7f,0x03,0x03,0x7f,0x7e}, // 5
	{0x60,0x60,0x60,0x60,0x7e,0x7f,0x63,0x63,0x7f,0x3e}, // 6
	{0x7f,0x7f,0x63,0x63,0x03,0x03,0x03,0x03,0x03,0x03}, // 7
	{0x3e,0x7f,0x63,0x63,0x7f,0x7f,0x63,0x63,0x7f,0x3e}, // 8
	{0x3e,0x7f,0x63,0x63,0x7f,0x3f,0x03,0x03,0x03,0x03} // 9
};

//structure for data
struct group_data{
	unsigned short int time_interval;
	unsigned short int timer_cnt;
	unsigned char timer_init[4];
};

//Set the message of the device driver
#define IOCTL_SET_MSG _IOW(DEVICE_MAJOR,0,struct group_data)
#define IOCTL_COMMAND _IO(DEVICE_MAJOR,0)

int dev_driver_release(struct inode *minode,struct file *mfile);
int dev_driver_open(struct inode *minode, struct file *mfile);
long dev_driver_ioctl(struct file *file,unsigned int ioctl_num,unsigned long ioctl_param);

void display();



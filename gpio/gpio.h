/* *
 * GPIO headfile
 * History:
 * 2011/8/13 - [W.J] create file
 * 2012/7/16 - [W.J] modify
 * 2014/6/11 - [W.j] modify 
 * Copyright (C) 2009-2014, WJ@SHANGHAI, Inc.
 */

#ifndef _GPIO_H
#define _GPIO_H

#define DEVICE_NAME			"gpiodrv"
#define GPIO_MAJOR			0
#define IOCTL_MAGIC			'g'
#define GPIO_OUT_LOW		_IOW(IOCTL_MAGIC, 0x00, unsigned long)
#define GPIO_OUT_HIG		_IOW(IOCTL_MAGIC, 0x01, unsigned long)
#define GPIO_INPUT			_IOR(IOCTL_MAGIC, 0x02, unsigned long)
	


#endif   /*GPIO*/

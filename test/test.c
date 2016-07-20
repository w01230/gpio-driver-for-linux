/**
 *  test.c
 *
 *  Copyright (C) 2014 W.J, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "gpio_drv.h"

int main(int argc, char **argv)
{
	int gpiofd = 0;
	int gpio_state = 0;
	
	if ((gpiofd = open("/dev/samsung_gpio0", O_RDWR)) < 0) {
		perror("open");
		return -1;
	}
	
	if ((gpio_state = ioctl(gpiofd, GPIO_IOC_OUTPUT_HIG	, GPIO(20))) < 0) {
		perror("ioctl");
		return -1;
	}
		
	printf("GPIO state:%d\n", gpio_state);
	
	return 0;
}

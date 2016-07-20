/**
 * gpio_drv.h
 *
 * History:
 *	2011/10/24 - [W.J] created file
 *
 * Copyright (C) 2010-2014, DATAIO, Inc.
 *
 * All rights reserved. No Part of this file may be reproduced, stored
 * in a retrieval system, or transmitted, in any form, or by any means,
 * electronic, mechanical, photocopying, recording, or otherwise,
 * without the prior consent of DATAIO, Inc.
 *
 */
#ifndef _GPIO_DRV_H
#define _GPIO_DRV_H

#define GPIO(X)   X
#define GPIO_IOC_MAGIC 'g'

/* general APIs - GPIO_IOC_MAGIC */
enum {
	IOC_OUTPUT_CLR,
	IOC_OUTPUT_SET,
	IOC_SET_INPUT,
};
	
#define GPIO_IOC_OUTPUT_LOW		_IOW(GPIO_IOC_MAGIC, IOC_OUTPUT_CLR, unsigned int)
#define GPIO_IOC_OUTPUT_HIG		_IOW(GPIO_IOC_MAGIC, IOC_OUTPUT_SET, unsigned int)
#define GPIO_IOC_INPUT			_IOR(GPIO_IOC_MAGIC, IOC_SET_INPUT, unsigned int)


#endif   /*end of GPIO_DRV_APIS*/
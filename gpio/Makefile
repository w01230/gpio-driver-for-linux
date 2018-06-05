#
# Makefile for test
#
# 2014.04.25 W.J@Shanghai
#

ifneq ($(KERNELRELEASE),)
	obj-m:=gpio.o
else
	PWD:=$(shell pwd)
	KVER:=$(shell uname -r)
	KDIR:=/lib/modules/$(KVER)/build/
all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	@rm -rf *.d *.o *.ko *.mod.c *.order *.symvers .gpio* .gpio*.*

endif


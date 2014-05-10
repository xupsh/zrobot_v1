ifneq ($(KERNELRELEASE),)
obj-m := ultrasonic.o
else
KERNEL_DIR := /home/zlpan/Build/Digilent-linux/
#KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules ARCH=arm
#	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c modules.* Module.*
endif

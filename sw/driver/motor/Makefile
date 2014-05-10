ifneq ($(KERNELRELEASE),)
obj-m := pwmdriver.o
else
#KERNEL_DIR := /home/zlpan/Digilent-linux
KERNEL_DIR := /home/zulongp/build/linux-xlnx/
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules ARCH=arm
clean:
	rm *.o *.ko *.mod.c Module* module*
endif

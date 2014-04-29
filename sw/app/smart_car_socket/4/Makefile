#CROSS_COMPILE_PATH=/opt/toolschain/arm-xilinxA9/bin/
#CROSS_COMPILE=arm-xilinx-linux-gnueabi-
PLATFORM=PC
ifeq ($(PLATFORM),)
PLATFORM=ZYNQ
endif

ifeq ($(PLATFORM), ZYNQ)
ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE=arm-xilinx-linux-gnueabi-
endif
CC=$(CROSS_COMPILE)gcc
else
CC=gcc
endif

TARGET       := zynq_server_arm
SOURCE       := ./*.c
$(TARGET):$(SOURCE)
	$(CC) $^ -o $@ -lpthread
clean:
	rm -rf ./*.o
install:
	cp ./*.o $(INSTALL_PATH)


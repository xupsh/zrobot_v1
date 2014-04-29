#CROSS_COMPILE_PATH=/opt/toolschain/arm-xilinxA9/bin/
CROSS_COMPILE=arm-xilinx-linux-gnueabi-
TARGET       := zynq_server_arm.o
SOURCE       := ./*.c
$(TARGET):$(SOURCE)
	$(CROSS_COMPILE)gcc $^ -o $@ -lpthread
clean:
	rm -rf ./*.o
install:
	cp ./*.o $(INSTALL_PATH)


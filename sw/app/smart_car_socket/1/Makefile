#CROSS_COMPILE_PATH=/opt/toolschain/arm-xilinxA9/bin/
CROSS_COMPILE=arm-xilinx-linux-gnueabi-
SOURCE=../err*.c ../dae*.c ../ultrasonic.c ../zynq_server.c smart_car_move.c
zynq_server_arm.o:$(SOURCE)
	$(CROSS_COMPILE)gcc $^ -o $@ -lpthread
clean:
	rm -rf ./*.o
install:
	cp ./*.o $(INSTALL_PATH)


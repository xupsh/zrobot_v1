CROSS_COMPILE_PATH= /opt/toolschain/arm-xilinxA9/bin/
CROSS_COMPILE=$(CROSS_COMPILE_PATH)arm-xilinx-linux-gnueabi-

INSTALL_PATH= /media/EXT/var/www/cgi-bin/
all:
	$(CROSS_COMPILE)gcc -c ./smart_car_move.c 
	$(CROSS_COMPILE)gcc -c ./smart_car_front.c
	$(CROSS_COMPILE)gcc -c ./smart_car_back.c
	$(CROSS_COMPILE)gcc -c ./smart_car_left.c 
	$(CROSS_COMPILE)gcc -c ./smart_car_right.c 
	$(CROSS_COMPILE)gcc -c ./smart_car_stop.c 
	$(CROSS_COMPILE)gcc -c ./smart_car_clockwise.c
	$(CROSS_COMPILE)gcc -c ./smart_car_counterclockwise.c 
	$(CROSS_COMPILE)gcc -o ./smart_car_front.cgi ./smart_car_move.o ./smart_car_front.o 
	$(CROSS_COMPILE)gcc -o ./smart_car_back.cgi ./smart_car_move.o ./smart_car_back.o 
	$(CROSS_COMPILE)gcc -o ./smart_car_left.cgi ./smart_car_move.o ./smart_car_left.o 
	$(CROSS_COMPILE)gcc  -o ./smart_car_right.cgi ./smart_car_move.o ./smart_car_right.o 
	$(CROSS_COMPILE)gcc  -o ./smart_car_stop.cgi ./smart_car_move.o ./smart_car_stop.o 
	$(CROSS_COMPILE)gcc  -o ./smart_car_clockwise.cgi ./smart_car_move.o ./smart_car_clockwise.o 
	$(CROSS_COMPILE)gcc  -o ./smart_car_counterclockwise.cgi ./smart_car_move.o ./smart_car_counterclockwise.o 

install:
	cp -a ./*.cgi $(INSTALL_PATH) 
clean:
	rm ./*.cgi ./*.o

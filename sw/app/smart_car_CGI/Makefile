CROSS_COMPILE=arm-xilinx-linux-gnueabi-
all:
	$(CROSS_COMPILE)gcc -c error.c
	$(CROSS_COMPILE)gcc -c smart_car_move.c error.o
	$(CROSS_COMPILE)gcc -o ./smart_car_front.cgi ./smart_car_move.o ./smart_car_front.c error.o
	$(CROSS_COMPILE)gcc -o ./smart_car_back.cgi ./smart_car_move.o ./smart_car_back.c error.o 
	$(CROSS_COMPILE)gcc -o ./smart_car_left.cgi ./smart_car_move.o ./smart_car_left.c error.o  
	$(CROSS_COMPILE)gcc  -o ./smart_car_right.cgi ./smart_car_move.o ./smart_car_right.c error.o  
	$(CROSS_COMPILE)gcc  -o ./smart_car_stop.cgi ./smart_car_move.o ./smart_car_stop.c error.o 
install:
	cp -a ./*.cgi $(INSTALL_PATH) 
clean:
	rm ./*.cgi ./*.o

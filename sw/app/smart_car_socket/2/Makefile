CROSS_COMPILE=arm-xilinx-linux-gnueabi-
SOURCE=../move.c ../err*.c test.c
test:$(SOURCE)
	$(CROSS_COMPILE)gcc $^ -o $@
clean:
	rm -rf ./*.o
install:
	cp ./*.o $(INSTALL_PATH)


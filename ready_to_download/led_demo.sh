#!/bin/sh
echo ///////////////////////////////////////////
echo ///                                     ///
echo ///  XILINX LED Demo Based On ZedBoard  ///
echo ///                                     ///
echo ///////////////////////////////////////////

echo contorl expamle:  ./led_demo.sh para1 para2
echo para1:  61 to 68
echo para2:  1 to on, 0 to off 
#for i in {61..68}
#do
#	if [ ! -d /sys/class/gpio$i ]; then
			echo $1 > /sys/class/gpio/export
#	fi
#done

echo out > /sys/class/gpio/gpio$1/direction
echo $2 > /sys/class/gpio/gpio$1/value



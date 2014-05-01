#########################################################################
# Copyright (c) 2013~2014 
# 
# This source code is released for free distribution under the terms of the
# GNU General Public License
# 
# Author:    zlpan
# File Name: init.sh
# Description: 
#########################################################################
#!/bin/bash
echo "++config ps eth0"
ifconfig eth0 192.168.1.100 up

#echo "++install pwm driver"
#/sbin/insmod /mnt/pwmdriver.ko

echo "++set hostname = zedboard"
cp /mnt/host* /etc/
hostname zedboard

echo "++config boa server and run it"
if [  ! -d /etc/boa ];then
	mkdir -p /etc/boa
fi
cp /mnt/boa/boa.conf /etc/boa/
cp /mnt/boa/log /mnt/boa/www -rf /var
cp /mnt/boa/mime.types /etc
/mnt/boa/boa &

echo "++add mjpg libraries"
if [ ! -d /mjpg/ ];then
	mkdir -p /mjpg/
fi
mount -o loop /mnt/mjpg.img /mjpg/
export LD_LIBRARY_PATH=/mjpg/lib/

echo "++start mjeg demo"
/mjpg/mjpg_streamer -i "input_uvc.so -y -d /dev/video0 -r 640*480" -o "output_http.so -p 8080 -w /var/www" &

echo "++start zynq socket server"
/mnt/zynq_server_arm.o &
echo "++end"
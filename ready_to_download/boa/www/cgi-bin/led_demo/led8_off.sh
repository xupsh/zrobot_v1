#!/bin/bash

	echo 68 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio68/direction
#	echo 1 > /sys/class/gpio/gpio68/value
	echo 0 > /sys/class/gpio/gpio68/value


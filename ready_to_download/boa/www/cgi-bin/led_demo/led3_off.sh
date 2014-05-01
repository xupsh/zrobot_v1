#!/bin/bash

	echo 63 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio63/direction
#	echo 1 > /sys/class/gpio/gpio63/value
	echo 0 > /sys/class/gpio/gpio63/value


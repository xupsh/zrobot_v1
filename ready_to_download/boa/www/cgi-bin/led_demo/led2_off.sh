#!/bin/bash

	echo 62 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio62/direction
#	echo 1 > /sys/class/gpio/gpio62/value
	echo 0 > /sys/class/gpio/gpio62/value


#!/bin/bash

	echo 64 > /sys/class/gpio/export

	echo out > /sys/class/gpio/gpio64/direction
	echo 1 > /sys/class/gpio/gpio64/value
#	echo 0 > /sys/class/gpio/gpio64/value


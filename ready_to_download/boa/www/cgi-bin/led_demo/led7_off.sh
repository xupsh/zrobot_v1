#!/bin/bash

	echo 67 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio67/direction
#	echo 1 > /sys/class/gpio/gpio67/value
	echo 0 > /sys/class/gpio/gpio67/value


#!/bin/bash

	echo 61 > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio61/direction
#	echo 1 > /sys/class/gpio/gpio61/value
	echo 0 > /sys/class/gpio/gpio61/value


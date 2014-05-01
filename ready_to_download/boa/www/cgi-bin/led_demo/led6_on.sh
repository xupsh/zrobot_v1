#!/bin/bash

	echo 66 > /sys/class/gpio/export

	echo out > /sys/class/gpio/gpio66/direction
	echo 1 > /sys/class/gpio/gpio66/value
#	echo 0 > /sys/class/gpio/gpio66/value


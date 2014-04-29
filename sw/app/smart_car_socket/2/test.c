#include <stdio.h>
#include "../move.h"
#include <stdlib.h>
#include <unistd.h>

int main()
{
	smart_car_set(0,40);
	sleep(2);
	smart_car_set(0,0);
	sleep(2);
	smart_car_set(0,-30);
	sleep(2);
	smart_car_set(80,30);
	sleep(2);
	smart_car_set(80,-30);
	sleep(2);
	smart_car_set(30,-30);
	sleep(2);
	smart_car_set(-30,-30);
	sleep(2);
	smart_car_set(-80,-30);
	sleep(2);
	smart_car_set(-80,30);
	sleep(2);
	smart_car_set(-30,30);
	sleep(2);
	smart_car_set(0,0);
	return 0;
}

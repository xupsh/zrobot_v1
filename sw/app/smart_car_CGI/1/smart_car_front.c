#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "smart_car_move.h"

int main(void)
{
   
    smart_car_set(30, 0); //speed=30 Angel=0
    
    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "smart_car_move.h"
static int fd;

int main(void)
{
    smart_car_set(-30, 0);
    
    return 0;
}

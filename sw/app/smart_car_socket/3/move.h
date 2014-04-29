#ifndef SMARTCARMOVE_H
#define SMARTCARMOVE_H

extern void init_LED();
extern void set_direction();
extern void set_car_go(int pwmnum, char *speed);
extern void set_car_front(char *speed);
extern void set_car_back(char *speed);
extern void set_car_right(int fast, int slow, char *value);
extern void set_car_left(int fast,  int slow, char *value);
extern void smart_car_set(int angle, int speed);

#endif

#ifndef SMARTCARMOVE_H
#define SMARTCARMOVE_H
extern void set_go();
extern void set_back();
extern void set_clockwise();
extern void set_counterclockwise();
extern void set_left(unsigned long speed);
extern void set_right(unsigned long speed);
extern void set_car(unsigned int FB, unsigned int LR, unsigned long fast, unsigned long slow);

extern void init_LED();
extern void smart_car_set(int speed, int angle);

#endif

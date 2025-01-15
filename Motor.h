#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor(int pinEnable, int pinDirection);
    void init();
    void setSpeed(int speed, bool direction);
    void stop();

private:
    int pinEnable;
    int pinDirection;
};

#endif
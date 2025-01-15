#include "Motor.h"

Motor::Motor(int pinEnable, int pinDirection) 
    : pinEnable(pinEnable), pinDirection(pinDirection) {}

void Motor::init() {
    pinMode(pinEnable, OUTPUT);
    pinMode(pinDirection, OUTPUT);
}

void Motor::setSpeed(int speed, bool direction) {
    digitalWrite(pinDirection, direction ? HIGH : LOW);
    analogWrite(pinEnable, speed);
}

void Motor::stop() {
    analogWrite(pinEnable, 0);
}
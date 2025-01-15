#ifndef CONTROL_H
#define CONTROL_H

#include "Motor.h"
#include "SpeedSensor.h"

class Control {
public:
    Control(Motor& leftMotor, Motor& rightMotor, SpeedSensor& leftSensor, SpeedSensor& rightSensor, bool moveForwardLeft = false, bool moveForwardRight = true);
    void init();
    void calibration();
    void setSpeed(double newSpeed);
    void setTilt(float newTilt);
    void setAcceleration(double newAcceleration);
    void lineFollow(int leftSensorValue, int rightSensorValue);


private:
    Motor& leftMotor;
    Motor& rightMotor;
    SpeedSensor& leftSensor;
    SpeedSensor& rightSensor;
    
    bool moveForwardLeft;
    bool moveForwardRight;

    float tilt;
    double speed;

    float acceleration;
    float braking;

    float integralLeftError = 0;
    float integralRightError = 0;
    float kp = 0.5;
    float ki = 0.1;

    float maxAdjustment = 255;
};

#endif
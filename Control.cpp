#include "Control.h"

Control::Control(Motor& leftMotor, Motor& rightMotor, SpeedSensor& leftSensor, SpeedSensor& rightSensor, bool moveForwardLeft, bool moveForwardRight) 
    : leftMotor(leftMotor),
      rightMotor(rightMotor),
      leftSensor(leftSensor),
      rightSensor(rightSensor),
      moveForwardLeft(moveForwardLeft),
      moveForwardRight(moveForwardRight),
      tilt(1),
      speed(0),
      acceleration(1),
      braking(1) {}


void Control::init() {
    leftMotor.init();
    rightMotor.init();
    leftSensor.init();
    rightSensor.init();
}

void Control::setSpeed(double newSpeed) {
    speed = newSpeed;
}

void Control::setAcceleration(double newAcceleration) {
    acceleration = newAcceleration;
}

void Control::setTilt(float newTilt) {
    tilt = newTilt;
}

void Control::calibration() {
    if (speed == 0) {
        leftMotor.stop();
        rightMotor.stop();
        return;
    }

    double leftSpeed = leftSensor.getSpeed();
    double rightSpeed = rightSensor.getSpeed();

    float leftError = (speed * (1 + tilt)) - leftSpeed;
    float rightError = (speed * (1 - tilt)) - rightSpeed;

    integralLeftError += leftError > 0 ? leftError * acceleration : leftError * braking;
    integralRightError += rightError > 0 ? rightError * acceleration : rightError * braking;

    integralLeftError = constrain(integralLeftError, -maxAdjustment, maxAdjustment);
    integralRightError = constrain(integralRightError, -maxAdjustment, maxAdjustment);

    float leftAdjustment = (kp * leftError) + (ki * integralLeftError);
    float rightAdjustment = (kp * rightError) + (ki * integralRightError);

    leftMotor.setSpeed(abs(leftAdjustment), moveForwardLeft);
    rightMotor.setSpeed(abs(rightAdjustment), moveForwardRight);
}


void Control::lineFollow(int leftSensorValue, int rightSensorValue) {
    float baseSpeed = speed;
    float kpLine = 0.2;

    int error = leftSensorValue - rightSensorValue;

    float leftSpeedAdjustment = baseSpeed - (kpLine * error);
    float rightSpeedAdjustment = baseSpeed + (kpLine * error);

    leftSpeedAdjustment = constrain(leftSpeedAdjustment, 0, maxAdjustment);
    rightSpeedAdjustment = constrain(rightSpeedAdjustment, 0, maxAdjustment);

    leftMotor.setSpeed(leftSpeedAdjustment, moveForwardLeft);
    rightMotor.setSpeed(rightSpeedAdjustment, moveForwardRight);
}
#include "main.h"

using namespace ports;

DriveControl::DriveControl(pros::Motor backLeftDrive, pros::Motor frontLeftDrive, pros::Motor frontRightDrive, pros::Motor backRightDrive)
{
  addLeftMotor(backLeftDrive);
  addLeftMotor(frontLeftDrive);
  addRightMotor(frontRightDrive);
  addRightMotor(backRightDrive);
}

void DriveControl::addLeftMotor(pros::Motor motor)
{
  DriveControl::leftMotors.push_back(motor);
}

void DriveControl::addRightMotor(pros::Motor motor)
{
  DriveControl::rightMotors.push_back(motor);
}

void DriveControl::setBrakeMode()
{
  for(auto & motor : leftMotors)
  {
    motor.set_brake_mode(BRAKE_BRAKE);
  }

  for(auto & motor : rightMotors)
  {
    motor.set_brake_mode(BRAKE_BRAKE);
  }
}

void DriveControl::opDrive()
{
  for(auto & motor : leftMotors)
  {
    motor.move(ports::controllerMain->get_analog(STICK_LEFT_Y) + ports::controllerMain->get_analog(STICK_LEFT_X));
  }

  for(auto & motor : rightMotors)
  {
    motor.move(ports::controllerMain->get_analog(STICK_LEFT_Y) - ports::controllerMain->get_analog(STICK_LEFT_X));
  }
}

void DriveControl::autoDrive(int powerLeft, int powerRight, int time)
{
  for(auto & motor : leftMotors)
  {
    motor.move(powerLeft);
  }
  for(auto & motor : rightMotors)
  {
    motor.move(powerRight);
  }
  if(time > 0)
  {
    pros::delay(time);

    autoDrive(0, 0, 0);
  }
}

int DriveControl::checkIfPowerInConstraints(int power, int maxPower)
{
  power = (power > maxPower && power > 0) ? maxPower : power;
  power = (power < -maxPower && power < 0) ? -maxPower : power;
  return power;
}

void DriveControl::moveRel(int targetDistance, int maxPower)
{
  double kp = 0;
  double kd = 0;

  int currentDistance = 0;
  int error = 1;
  int derivative = 0;
  int lastError = 0;

  int power = 0;

  while(error != 0)
  {
    currentDistance = leftMotors[0].get_position();
    error = targetDistance - currentDistance;
    derivative = error - lastError;
    lastError = error;

    power = (error * kp) + (derivative * kd);

    autoDrive(power, power, 0);
  }
}

void DriveControl::pivotRel(int targetDegree, int maxPower)
{
  double kp = 0;
  double kd = 0;

  int currentDegree = 0;
  int error = 1;
  int derivative = 0;
  int lastError = 0;

  int power = 0;

  while(error != 0)
  {
    currentDegree = gyro->get_value();
    error = targetDegree - currentDegree;
    derivative = error - lastError;
    lastError = error;

    power = (error * kp) + (derivative * kd);
    power = (power > maxPower && power > 0) ? maxPower : power;
    power = (power < -maxPower && power < 0) ? -maxPower : power;

    autoDrive(power, -power, 0);
  }
}

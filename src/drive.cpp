#include "main.h"

using namespace ports;

DriveControl::DriveControl(pros::Motor backLeftDrive, pros::Motor frontLeftDrive, pros::Motor frontRightDrive, pros::Motor backRightDrive)
{
  addLeftMotor(backLeftDrive);
  addLeftMotor(frontLeftDrive);
  addRightMotor(frontRightDrive);
  addRightMotor(backRightDrive);

  setBrakeMode();
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

void DriveControl::setControllers(pros::Controller * main, pros::Controller * partner)
{
  controllerMain = main;
  controllerPartner = partner;
}

void DriveControl::resetEncoders()
{
  for(auto & motor : leftMotors)
  {
    motor.tare_position();
  }

  for(auto & motor : rightMotors)
  {
    motor.tare_position();
  }
}

void DriveControl::opDrive()
{
  for(auto & motor : leftMotors)
  {
    motor.move(controllerMain->get_analog(STICK_LEFT_Y) - controllerMain->get_analog(STICK_LEFT_X));
  }

  for(auto & motor : rightMotors)
  {
    motor.move(controllerMain->get_analog(STICK_LEFT_Y) + controllerMain->get_analog(STICK_LEFT_X));
  }
}

void DriveControl::powerDrive(int powerLeft, int powerRight, int time)
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

    powerDrive(0, 0, 0);
  }
}

int DriveControl::checkIfPowerInConstraints(int power, int maxPower)
{
  power = (power > maxPower) ? maxPower : power;
  power = (power < -maxPower) ? -maxPower : power;
  return power;
}

void DriveControl::driveStraight(int power)
{
  double kp = 0;

  int masterSide = 0;
  int partnerSide = 0;
  int error  = 1;
  int lastError = 0;

  int powerLeft = 0;
  int powerRight = 0;

  masterSide = abs(leftMotors[0].get_position());
  partnerSide = abs(rightMotors[0].get_position());

  error = masterSide - partnerSide;

  powerLeft = (error > 0) ? power - (error * kp) : power;
  powerRight = (error > 0) ? power : power - (error * kp);

  powerDrive(powerLeft, powerRight, 0);

}
// targetDistance: -∞ to ∞; maxPower: 0 to 127
void DriveControl::movePid(int targetDistance, int maxPower)
{
  targetDistance = targetDistance / wheelCircumference * 360;
  double kp = 0;
  double kd = 0;

  int currentDistance = 0;
  int error = 1;
  int derivative = 0;
  int lastError = 0;

  int power = 0;

  resetEncoders();

  while(error != 0)
  {
    currentDistance = leftMotors[0].get_position();
    error = targetDistance - currentDistance;
    derivative = error - lastError;
    lastError = error;

    power = (error * kp) + (derivative * kd);
    power = checkIfPowerInConstraints(power, maxPower);
    driveStraight(power);
  }
}

//both parameters must be -ve when going backwards
void DriveControl::moveRel(int target, int power)
{
  target = target / wheelCircumference * 360;

  for(auto & motor : leftMotors)
  {
    motor.move_relative(target, power);
  }

  for(auto & motor : rightMotors)
  {
    motor.move_relative(target, power);
  }
}

//power: 0 to 127
void DriveControl::turn90(bool turnCW, int power)
{
  int threshold = 0;

  while(leftMotors[0].get_position() < threshold)
  {
    int powerLeft = (turnCW) ? power : -power;
    int powerRight = (turnCW) ? -power : power;

    powerDrive(powerLeft, powerRight, 0);
  }

  powerDrive(0, 0, 0);
}

std::vector<pros::Motor> DriveControl::getLeftMotors()
{
  return leftMotors;
}

std::vector<pros::Motor> DriveControl::getRightMotors()
{
  return rightMotors;
}

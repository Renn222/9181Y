#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"
#include <vector>

class DriveControl
{
  std::vector<pros::Motor> leftMotors;
  std::vector<pros::Motor> rightMotors;

  double wheelDiameter = 4; //in inches
  double wheelCircumference = PI * wheelDiameter;

  pros::Controller * controllerMain;
  pros::Controller * controllerPartner;

public:

  explicit DriveControl(pros::Motor backLeftDrive, pros::Motor frontLeftDrive, pros::Motor frontRightDrive, pros::Motor backRightDrive);
  void addLeftMotor(pros::Motor motor);
  void addRightMotor(pros::Motor motor);
  void setBrakeMode();
  void setControllers(pros::Controller * main, pros::Controller * partner);
  void resetEncoders();
  void opDrive();
  void powerDrive(int powerLeft, int powerRight, int time);
  int checkIfPowerInConstraints(int power, int maxPower);
  void driveStraight(int power);
  void movePid(int targetDistance, int maxPower);
  void moveRel(int target, int power);
  void turn90(bool turnCW, int power);
  std::vector<pros::Motor> getLeftMotors();
  std::vector<pros::Motor> getRightMotors();
};
#endif

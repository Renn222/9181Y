#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

#include "main.h"
#include <vector>

class DriveControl
{
  std::vector<pros::Motor> leftMotors;
  std::vector<pros::Motor> rightMotors;
public:
  explicit DriveControl(pros::Motor backLeftDrive, pros::Motor frontLeftDrive, pros::Motor frontRightDrive, pros::Motor backRightDrive);
  void addLeftMotor(pros::Motor motor);
  void addRightMotor(pros::Motor motor);
  void setBrakeMode();
  void opDrive();
  void autoDrive(int powerLeft, int powerRight, int time);
  int checkIfPowerInConstraints(int power, int maxPower);
  void moveRel(int targetDistance, int maxPower);
  void pivotRel(int targetDegree, int maxPower);

};
#endif

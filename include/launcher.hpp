#ifndef _LAUNCHER_HPP_
#define _LAUNCHER_HPP_

#include "main.h"

class LauncherControl
{
  std::vector<pros::Motor> switcherMotors;
  std::vector<pros::Motor> launcherMotors;

public:
  explicit LauncherControl(pros::Motor launcherMotor, pros::Motor switcherMotor);
  void addSwitcherMotors(pros::Motor motor);
  void addLauncherMotors(pros::Motor motor);
  void setLauncherBrakeMode();
  void setSwitcherPos();
  void powerLauncherRel(int target, int power);
};

#endif

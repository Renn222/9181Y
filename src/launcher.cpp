#include "main.h"

using namespace ports;

LauncherControl::LauncherControl(pros::Motor launcherMotor, pros::Motor switcherMotor)
{
  addLauncherMotors(launcherMotor);
  addSwitcherMotors(switcherMotor);
}

void LauncherControl::addSwitcherMotors(pros::Motor motor)
{
  switcherMotors.push_back(motor);
}

void LauncherControl::addLauncherMotors(pros::Motor motor)
{
  launcherMotors.push_back(motor);
}

void LauncherControl::setBrakeMode()
{
  for(auto & motor : switcherMotors)
  {
    motor.set_brake_mode(BRAKE_HOLD);
  }
}

/*MAKE IS SO THAT THIS WORKS FOR SWITCHING TO CERTAIN VALUES AND THEN
MAKE SURE THAT EVERYTHING IS MOVE REL WHEN IT NEEDS TO BE AND MOVE
ABSOLUTE WHEN IT NEEDS TO BE*/
void LauncherControl::setSwitcherPos(int pos)
{
  int target;
  int power;

  if(pos == 0)
  {
    target = 0;
    power = 127;
  }
  else
  {
    target = -66;
    power = -127;
  }

  for(auto & motor : switcherMotors)
  {
    motor.move_absolute(target, power);
  }
}

void LauncherControl::shoot(int power)
{
  for(auto & motor : launcherMotors)
  {
    motor.move_relative(1800, power);
  }
}

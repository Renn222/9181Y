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

void LauncherControl::setLauncherBrakeMode()
{
  for(auto & motor : launcherMotors)
  {
    motor.set_brake_mode(BRAKE_COAST);
  }
}

/*MAKE IS SO THAT THIS WORKS FOR SWITCHING TO CERTAIN VALUES AND THEN
MAKE SURE THAT EVERYTHING IS MOVE REL WHEN IT NEEDS TO BE AND MOVE
ABSOLUTE WHEN IT NEEDS TO BE*/
void LauncherControl::setSwitcherPos()
{
  int target;
  int power;

  if(switcherMotors[0].get_position() < 0)
  {
    target = 0;
    power = 127;
  }
  else
  {
    target = -450;
    power = -127;
  }

  for(auto & motor : switcherMotors)
  {
    motor.move_relative(target, power);
  }
}

void LauncherControl::powerLauncherRel(int target, int power)
{
  for(auto & motor : launcherMotors)
  {
    motor.move_relative(target, power);
  }
}

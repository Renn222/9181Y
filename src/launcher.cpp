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
    motor.set_brake_mode(BRAKE_COAST);
  }
}

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

void LauncherControl::moveTime(int power, int time)
{
  for(auto & motor : launcherMotors)
  {
    motor.move(power);
  }

  if(time > 0)
  {
    pros::delay(time);

    moveTime(0, 0);
  }
}

void LauncherControl::shoot(int power)
{
  for(auto & motor : launcherMotors)
  {
    motor.move_relative(720, power);
  }
}

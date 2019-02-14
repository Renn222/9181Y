#include "main.h"

using namespace ports;

IntakeControl::IntakeControl(pros::Motor intakeMotor, pros::Motor switcherMotors, pros::Motor frontLauncherMotor, pros::Motor backLauncherMotor, pros::Motor liftMotor)
{
  addIntakeMotors(intakeMotor);
  addSwitcherMotors(switcherMotors);
  addLauncherMotors(frontLauncherMotor);
  addLauncherMotors(backLauncherMotor);
}

void IntakeControl::setBrakeForLauncher()
{
  for(auto & motor : launcherMotors)
  {
    motor.set_brake_mode(BRAKE_COAST);
  }
}

void IntakeControl::addIntakeMotors(pros::Motor motor)
{
  intakeMotors.push_back(motor);
}

void IntakeControl::addSwitcherMotors(pros::Motor motor)
{
  switcherMotors.push_back(motor);
}

void IntakeControl::addLauncherMotors(pros::Motor motor)
{
  launcherMotors.push_back(motor);
}

void IntakeControl::powerIntake(int power)
{
  for(auto & motor : intakeMotors)
  {
    motor.move(power);
  }
}

void IntakeControl::powerLauncher(int power)
{
  for(auto & motor : launcherMotors)
  {
    motor.move(power);
  }
}

void IntakeControl::powerIntakeRel(int target, int power)
{
  for(auto & motor : intakeMotors)
  {
    motor.move_relative(target, power);
  }
}

/*MAKE IS SO THAT THIS WORKS FOR SWITCHING TO CERTAIN VALUES AND THEN
MAKE SURE THAT EVERYTHING IS MOVE REL WHEN IT NEEDS TO BE AND MOVE
ABSOLUTE WHEN IT NEEDS TO BE*/
void IntakeControl::powerSwitcherRel(bool moveToTop)
{
  int target;
  int power;
  if(moveToTop && switcherMotors[0].get_position() < 0)
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

void IntakeControl::powerLauncherRel(int target, int power)
{
  for(auto & motor : launcherMotors)
  {
    motor.move_relative(target, power);
  }
}

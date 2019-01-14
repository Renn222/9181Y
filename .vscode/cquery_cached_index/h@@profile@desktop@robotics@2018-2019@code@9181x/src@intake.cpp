#include "main.h"

using namespace ports;

IntakeControl::IntakeControl(pros::Motor intakeMotor, pros::Motor frontLauncherMotor, pros::Motor backLauncherMotor, pros::Motor liftMotor)
{
  addIntakeMotors(intakeMotor);
  addLauncherMotors(frontLauncherMotor);
  addLauncherMotors(backLauncherMotor);
  addLiftMotors(liftMotor);
}

void IntakeControl::addIntakeMotors(pros::Motor motor)
{
  intakeMotors.push_back(motor);
}

void IntakeControl::addLauncherMotors(pros::Motor motor)
{
  launcherMotors.push_back(motor);
}

void IntakeControl::addLiftMotors(pros::Motor motor)
{
  liftMotors.push_back(motor);
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

void IntakeControl::powerLauncherAndIntake(int power)
{
  if (controllerMain->get_digital(BUTTON_R2))
  {
    powerLauncher(-power);
    powerIntake(-power);
  }
  else if(controllerMain->get_digital(BUTTON_R1))
    powerIntake(power);
  else
    powerIntake(0);

  if (controllerMain->get_digital(BUTTON_L2))
  {
    powerLauncher(power);
  }
  else
  {
    powerLauncher(0);
  }
}

void IntakeControl::powerLift(int power)
{
  for(auto & motor : liftMotors)
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

void IntakeControl::powerLauncherRel(int target, int power)
{
  for(auto & motor : launcherMotors)
  {
    motor.move_relative(target, power);
  }
}

void IntakeControl::powerLiftRel(int target, int power)
{
  for(auto & motor : liftMotors)
  {
    motor.move_relative(target, power);
  }
}

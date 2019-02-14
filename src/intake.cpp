#include "main.h"

using namespace ports;

IntakeControl::IntakeControl(pros::Motor intakeMotor, pros::Motor indexerMotor, pros::Motor frontLauncherMotor, pros::Motor backLauncherMotor, pros::Motor liftMotor)
{
  addIntakeMotors(intakeMotor);
  addIndexerMotors(indexerMotor);
  addLauncherMotors(frontLauncherMotor);
  addLauncherMotors(backLauncherMotor);
}

void IntakeControl::setBrakeForLauncher()
{
  for(auto & motor : launcherMotors)
  {
    motor.set_brake_mode(BRAKE_BRAKE);
  }
}

void IntakeControl::addIntakeMotors(pros::Motor motor)
{
  intakeMotors.push_back(motor);
}

void IntakeControl::addIndexerMotors(pros::Motor motor)
{
  indexerMotors.push_back(motor);
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

void IntakeControl::powerIndexer(int power)
{
  for(auto & motor : indexerMotors)
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

void IntakeControl::powerLauncherAndIndexer(int power)
{
  if (controllerMain->get_digital(BUTTON_R2))
  {
    powerLauncher(-power);
    powerIndexer(-power);
  }
  else if(controllerMain->get_digital(BUTTON_R1))
    powerIndexer(power);
  else
    powerIndexer(0);

  if (controllerMain->get_digital(BUTTON_L2))
  {
    powerLauncher(power);
  }
  else
  {
    powerLauncher(0);
  }
}

void IntakeControl::powerIntakeRel(int target, int power)
{
  for(auto & motor : intakeMotors)
  {
    motor.move_relative(target, power);
  }
}

void IntakeControl::powerIndexerRel(int target, int power)
{
  for(auto & motor : indexerMotors)
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

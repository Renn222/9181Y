#include "main.h"

using namespace ports;

IntakeControl::IntakeControl(pros::Motor intakeMotor)
{
  addIntakeMotors(intakeMotor);
}

void IntakeControl::addIntakeMotors(pros::Motor motor)
{
  intakeMotors.push_back(motor);
}

void IntakeControl::setBrakeMode()
{
  for(auto & motor : intakeMotors)
  {
    motor.set_brake_mode(BRAKE_COAST);
  }
}

void IntakeControl::powerIntake(int power)
{
  for(auto & motor : intakeMotors)
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

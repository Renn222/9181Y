#include "main.h"

LiftControl::LiftControl(pros::Motor liftMotor)
{
  addLiftMotors(liftMotor);
}

void LiftControl::addLiftMotors(pros::Motor motor)
{
  liftMotors.push_back(motor);
}

void LiftControl::setBrakeMode()
{
  for(auto & motor : liftMotors)
  {
    motor.set_brake_mode(BRAKE_BRAKE);
  }
}

void LiftControl::setControllers(pros::Controller * main, pros::Controller * partner)
{
  controllerMain  = main;
  controllerPartner = partner;
}

void LiftControl::opLift()
{
  for(auto & motor : liftMotors)
  {
    motor.move(controllerMain->get_analog(STICK_RIGHT_Y));
  }
}

void LiftControl::powerLiftTime(int power, int time)
{
  for(auto & motor : liftMotors)
  {
    motor.move(power);
  }

  if(time > 0)
  {
    pros::delay(time);

    powerLiftTime(0, 0);
  }
}

void LiftControl::powerLiftRel(int target, int power)
{
  for(auto & motor : liftMotors)
  {
    motor.move_relative(target, power);
  }
}

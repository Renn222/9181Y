#ifndef _LIFT_HPP_
#define _LIFT_HPP_

#include "main.h"

class LiftControl
{
  std::vector<pros::Motor> liftMotors;

  pros::Controller * controllerMain;
  pros::Controller * controllerPartner;

public:

  explicit LiftControl(pros::Motor liftMotor);
  void addLiftMotors(pros::Motor motor);
  void setBrakeMode();
  void setControllers(pros::Controller * main, pros::Controller * partner);
  void opLift();
  void moveTime(int power, int time);
  void moveRel(int target, int power);
  void moveAbs(int target, int power);
};
#endif

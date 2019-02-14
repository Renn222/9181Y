#ifndef _LIFT_HPP_
#define _LIFT_HPP_

#include "main.h"

class LiftControl
{
  std::vector<pros::Motor> liftMotors;

public:

  explicit LiftControl(pros::Motor liftMotor);
  void addLiftMotors(pros::Motor motor);
  void powerLift(int power);
  void powerLiftRel(int target, int power);
};
#endif

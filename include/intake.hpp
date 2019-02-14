#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

#include "main.h"

class IntakeControl
{
  std::vector<pros::Motor> intakeMotors;

  public:
    explicit IntakeControl(pros::Motor intakeMotor);
    void addIntakeMotors(pros::Motor motor);
    void powerIntake(int power);
    void powerIntakeRel(int target, int power);
};
#endif

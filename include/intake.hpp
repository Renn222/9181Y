#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

#include "main.h"

class IntakeControl
{
  std::vector<pros::Motor> intakeMotors;
  std::vector<pros::Motor> launcherMotors;
  std::vector<pros::Motor> liftMotors;

  public:
    explicit IntakeControl(pros::Motor intakeMotor, pros::Motor frontLauncherMotor, pros::Motor backLauncherMotor, pros::Motor liftMotor);
    void addIntakeMotors(pros::Motor motor);
    void addLauncherMotors(pros::Motor motor);
    void powerIntake(int power);
    void powerLauncher(int power);
    void powerLauncherAndIntake(int power);
    void powerLift(int power);
    void powerIntakeRel(int target, int power);
    void powerLauncherRel(int target, int power);
    void powerLiftRel(int target, int power);
};
#endif

#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

#include "main.h"

class IntakeControl
{
  std::vector<pros::Motor> intakeMotors;
  std::vector<pros::Motor> switcherMotors;
  std::vector<pros::Motor> launcherMotors;

  public:
    explicit IntakeControl(pros::Motor intakeMotor, pros::Motor indexerMotor, pros::Motor frontLauncherMotor, pros::Motor backLauncherMotor, pros::Motor liftMotor);
    void setBrakeForLauncher();
    void addIntakeMotors(pros::Motor motor);
    void addSwitcherMotors(pros::Motor motor);
    void addLauncherMotors(pros::Motor motor);
    void powerIntake(int power);
    void powerLauncher(int power);
    void powerIntakeRel(int target, int power);
    void powerSwitcherRel(bool moveToTop);
    void powerLauncherRel(int target, int power);
};
#endif

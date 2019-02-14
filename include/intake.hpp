#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

#include "main.h"

class IntakeControl
{
  std::vector<pros::Motor> intakeMotors;
  std::vector<pros::Motor> indexerMotors;
  std::vector<pros::Motor> launcherMotors;

  public:
    explicit IntakeControl(pros::Motor intakeMotor, pros::Motor indexerMotor, pros::Motor frontLauncherMotor, pros::Motor backLauncherMotor, pros::Motor liftMotor);
    void setBrakeForLauncher();
    void addIntakeMotors(pros::Motor motor);
    void addIndexerMotors(pros::Motor motor);
    void addLauncherMotors(pros::Motor motor);
    void powerIntake(int power);
    void powerIndexer(int power);
    void powerLauncher(int power);
    void powerLauncherAndIndexer(int power);
    void powerIntakeRel(int target, int power);
    void powerIndexerRel(int target, int power);
    void powerLauncherRel(int target, int power);
};
#endif

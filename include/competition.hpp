#ifndef _COMPETITION_HPP_
#define _COMPETITION_HPP_

#include "main.h"

namespace ports
{
  // Controllers
  static pros::Controller * controllerMain;
  static pros::Controller * controllerPartner;

  // Ports
  static pros::Motor * backLeftDrive;
  static pros::Motor * frontLeftDrive;
  static pros::Motor * intakeMotor;
  static pros::Motor * frontLauncherMotor;
  static pros::Motor * backLauncherMotor;
  static pros::Motor * liftMotor;
  static pros::Motor * frontRightDrive;
  static pros::Motor * backRightDrive;
  static pros::ADIGyro * gyro;

  static DriveControl * driver;
  static IntakeControl * intakeControl;
  static LiftControl * liftControl;

  static int autoCounter;

  static std::vector<pros::Motor> leftMotors;
  static std::vector<pros::Motor> rightMotors;

  static void init();

}

#endif

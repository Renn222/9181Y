#include "main.h"

namespace ports {


  // Ports
  static pros::Motor * backLeftDrive;
  static pros::Motor * frontLeftDrive;
  static pros::Motor * intakeMotor;
  static pros::Motor * frontLauncherMotor;
  static pros::Motor * backLauncherMotor;
  static pros::Motor * liftMotor;
  static pros::Motor * frontRightDrive;
  static pros::Motor * backRightDrive;

  static pros::Mutex * driveLock;
  static pros::Mutex * launcherLock;
  static pros::Mutex * intakeLock;
  static pros::Mutex * liftLock;

};

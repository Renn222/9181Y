#include "main.h"

namespace ports {


  // Ports
  static Unused * port10;
  static pros::Motor * backLeftDrive;
  static pros::Motor * frontLeftDrive;
  static pros::Motor * intakeMotor;
  static Unused * port14;
  static Unused * port15;
  static pros::Motor * frontLauncherMotor;
  static pros::Motor * backLauncherMotor;
  static pros::Motor * liftMotor;
  static pros::Motor * frontRightDrive;
  static pros::Motor * backRightDrive;
  static Unused * port21;

  static pros::Mutex * driveLock;
  static pros::Mutex * launcherLock;
  static pros::Mutex * intakeLock;
  static pros::Mutex * liftLock;

  static DriveControl * driveControl;
  static DriveFunction * drive;

  static void init();

};

#include "main.h"
#include <cmath>

void init() {
  controllerMain = new pros::Controller(CONTROLLER_MAIN);
  controllerPartner = new pros::Controller(CONTROLLER_PARTNER);

  brainBattery = new BrainBattery();
  controllerMainBattery = new ControllerBattery(*(controllerMain));
  // controllerPartnerBattery = new ControllerBattery(*(controllerPartner));

  backLeftDrive = new pros::Motor(11, GEARSET_200, FWD, ENCODER_DEGREES);
  frontLeftDrive = new pros::Motor(12, GEARSET_200, FWD, ENCODER_DEGREES);
  intakeMotor = new pros::Motor(13, GEARSET_200, REV, ENCODER_DEGREES);
  frontLauncherMotor = new pros::Motor(14, GEARSET_200, REV, ENCODER_DEGREES);
  backLauncherMotor = new pros::Motor(15, GEARSET_200, FWD, ENCODER_DEGREES);
  port16 = new Unused();
  port17 = new Unused();
  liftMotor = new pros::Motor(18, GEARSET_200, FWD, ENCODER_DEGREES);
  frontRightDrive = new pros::Motor(19, GEARSET_200, REV, ENCODER_DEGREES);
  backRightDrive = new pros::Motor(20, GEARSET_200, REV, ENCODER_DEGREES);
  port21 = new Unused();

  driveLock = new pros::Mutex();
  launcherLock = new pros::Mutex();
  intakeLock = new pros::Mutex();
  liftLock = new pros::Mutex();

  driveControl = new DriveControl(*driveLock, *frontLeftDrive, *backLeftDrive, *frontRightDrive, *backRightDrive);
}

using namespace ports;

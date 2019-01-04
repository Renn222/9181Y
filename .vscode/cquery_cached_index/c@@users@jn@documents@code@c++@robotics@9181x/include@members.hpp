#ifndef _MEMBERS_HPP
#define _MEMBERS_HPP

#include "main.h"

// Ports
static pros::Motor * backLeftDrive = new pros::Motor(11, GEARSET_200, FWD, ENCODER_DEGREES);
static pros::Motor * frontLeftDrive;
static pros::Motor * intakeMotor;
static pros::Motor * frontLauncherMotor;
static pros::Motor * backLauncherMotor;
static pros::Motor * liftMotor;
static pros::Motor * frontRightDrive;
static pros::Motor * backRightDrive;

static pros::Controller * controllerMain;

#endif

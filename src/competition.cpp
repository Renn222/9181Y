#include "main.h"


namespace ports
{
  void init()
  {
    controllerMain = new pros::Controller(CONTROLLER_MAIN);
    controllerPartner = new pros::Controller(CONTROLLER_PARTNER);

    backLeftDrive = new pros::Motor(11, GEARSET_200, FWD, ENCODER_DEGREES);
    frontLeftDrive = new pros::Motor(12, GEARSET_200, FWD, ENCODER_DEGREES);
    intakeMotor = new pros::Motor(13, GEARSET_200, REV, ENCODER_DEGREES);
    frontLauncherMotor = new pros::Motor(14, GEARSET_200, REV, ENCODER_DEGREES);
    backLauncherMotor = new pros::Motor(15, GEARSET_200, FWD, ENCODER_DEGREES);

    liftMotor = new pros::Motor(18, GEARSET_200, FWD, ENCODER_DEGREES);
    frontRightDrive = new pros::Motor(19, GEARSET_200, REV, ENCODER_DEGREES);
    backRightDrive = new pros::Motor(20, GEARSET_200, REV, ENCODER_DEGREES);

    gyro = new pros::ADIGyro(21);

    driver = new DriveControl(*backLeftDrive, *frontLeftDrive, *frontRightDrive, *backRightDrive);
    driver->setBrakeMode();

    autoCounter = 0;
  }
}

using namespace ports;

void checkAutoSelected()
{
  std::string selectedAuto = "";
  switch(autoCounter)
  {
    case -1:
      selectedAuto = "RED LEFT";
      break;
    case 1:
      selectedAuto = "BLUE RIGHT";
      break;
    default:
      selectedAuto = "NONE. \nThe Current Number is: " + std::to_string(autoCounter);
      break;
  }

  pros::lcd::set_text(3, "Current Selection: " + selectedAuto);
}

void on_left_button()
{
  autoCounter--;

  checkAutoSelected();

}

void on_centre_button()
{
  static bool pressed = false;
	pressed = !pressed;
	if (pressed)
  {
    autoRunner = new AutoControl(autoCounter);
	}
}

void on_right_button()
{
  autoCounter++;
  checkAutoSelected();
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
  pros::lcd::initialize();
  init();

  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn1_cb(on_centre_button);
  pros::lcd::register_btn2_cb(on_right_button);

  pros::lcd::set_text(3, "Current Selection: " + autoCounter);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	while (true)
  {
    //driver->opDrive();

    if (controllerMain->get_digital(BUTTON_R2))
    {
      frontLauncherMotor->move(-127);
      backLauncherMotor->move(-127);
      intakeMotor->move(-127);
    }
    else if(controllerMain->get_digital(BUTTON_R1))
        intakeMotor->move(127);
    else
        intakeMotor->move(0);

    if (controllerMain->get_digital(BUTTON_L2))
    {
      frontLauncherMotor->move(127);
      backLauncherMotor->move(127);
    }
    else
    {
      frontLauncherMotor->move(0);
      backLauncherMotor->move(0);
    }

    liftMotor->move(controllerMain->get_analog(ANALOG_RIGHT_Y));

		pros::delay(20);
  }
}

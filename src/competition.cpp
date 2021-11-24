#include "main.h"

int top = 0;
int bot = 1;

namespace ports
{
  void init()
  {
    controllerMain = new pros::Controller(CONTROLLER_MAIN);
    controllerPartner = new pros::Controller(CONTROLLER_PARTNER);

    static pros::Motor * backLeftDrive = new pros::Motor(10, GEARSET_200, FWD, ENCODER_DEGREES);
  	static pros::Motor * frontLeftDrive = new pros::Motor(2, GEARSET_200, FWD, ENCODER_DEGREES);
  	static pros::Motor * intakeMotor = new pros::Motor(1, GEARSET_200, FWD, ENCODER_DEGREES);
  	static pros::Motor * launcherMotor = new pros::Motor(7, GEARSET_200, FWD, ENCODER_DEGREES);

  	static pros::Motor * switcher = new pros::Motor(8, GEARSET_100, REV, ENCODER_DEGREES);
  	static pros::Motor * liftMotor = new pros::Motor(4, GEARSET_100, FWD, ENCODER_DEGREES);
  	static pros::Motor * frontRightDrive = new pros::Motor(3, GEARSET_200, REV, ENCODER_DEGREES);
  	static pros::Motor * backRightDrive = new pros::Motor(9, GEARSET_200, REV, ENCODER_DEGREES);

    driver = new DriveControl(*backLeftDrive, *frontLeftDrive, *frontRightDrive, *backRightDrive);
    intakeControl = new IntakeControl(*intakeMotor);
    liftControl = new LiftControl(*liftMotor);
    launcherControl = new LauncherControl(*launcherMotor, *switcher);

    driver->setControllers(controllerMain, controllerPartner);
    liftControl->setControllers(controllerMain, controllerPartner);

    driver->setBrakeMode();
    liftControl->setBrakeMode();
    intakeControl->setBrakeMode();
    launcherControl->setBrakeMode();

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
      selectedAuto = "NONE";
      break;
  }

  pros::lcd::set_text(3, "Current Selection: " + selectedAuto);
  pros::lcd::set_text(5, "The Current Number is: " + std::to_string(autoCounter));
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
    pros::lcd::set_text(1, "AUTO SELECTED");
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

 void blueFarSide()
 {
   driver->turnRel(90, 80);
   pros::delay(500);
   driver->turnRel(-90, 80);
   /*liftControl->powerLiftRel(1200, 127);
   launcherControl->setSwitcherPos(top);
   driver->movePid(35, 100);
   intakeControl->powerIntakeRel(1200, 127);

   driver->movePid(-10, 100);
   driver->turnRel(90, 100);
   launcherControl->shoot(127);*/
 }

 void redFarSide()
 {

 }

void autonomous()
{
  switch(autoCounter)
  {
    case -1:
      redFarSide();
      break;
    case 1:
      blueFarSide();
      break;
    default:
      pros::lcd::set_text(6, "Autonomous was not run");
  }
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
  int speed = 0;

  while (true)
  {
    driver->opDrive();

    liftControl->opLift();

    if(controllerMain->get_digital(BUTTON_L1))
    {
      launcherControl->setSwitcherPos(top);
      launcherControl->shoot(127);
    }

    else if(controllerMain->get_digital(BUTTON_L2))
    {
      launcherControl->setSwitcherPos(bot);
      launcherControl->shoot(127);

    }
    else if(controllerMain->get_digital(BUTTON_B))
    {
      launcherControl->moveTime(0, 0);
    }
    else if(controllerMain->get_digital(BUTTON_A))
    {
      liftControl->moveTime(127, 200);
    }

    if(controllerMain->get_digital(BUTTON_R1))
		{
			intakeControl->powerIntake(127);
		}
		else if(controllerMain->get_digital(BUTTON_R2))
		{
      intakeControl->powerIntake(-127);
		}

		else
		{
      intakeControl->powerIntake(0);
		}

		if(controllerMain->get_digital(BUTTON_X))
		{
			autonomous();
		}

    if (launcherControl->getSwitcherMotors()[0].get_position() - 715 > 0)
    {
      launcherControl->stop();
    }

    pros::delay(20);
	}
}

#include "main.h"

using namespace ports;

InitControl::InitControl()
{
	pros::lcd::initialize();
}

void InitControl::startAutoSelector()
{
  pros::lcd::set_text(1, "SELECT AUTONOMOUS PROGRAM");

  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn2_cb(on_right_button);
}

void InitControl::checkAutoSelected()
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

void InitControl::on_left_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
  {
    autoCounter--;

    checkAutoSelected();
	}
}

void InitControl::on_right_button()
{
  static bool pressed = false;
	pressed = !pressed;
	if (pressed)
  {
    autoCounter++;

    checkAutoSelected();
	}
}

int getSelectedAuto()
{
  return autoCounter;
}

#include "main.h"

using namespace ports;

void AutoControl::setSelectedAuto(int autoSelected)
{
  selectedAuto = autoSelected;
}

void AutoControl::startAuto()
{
  switch(selectedAuto)
  {
    case -1:
      autoFlagSide(false);
      break;
    case 1:
      autoFlagSide(true);
      break;
    default:
      pros::lcd::set_text(6, "Autonomous was not run");
  }
}

void AutoControl::autoFlagSide(bool turnCW)
{
  driver->moveRel(1000, 127);
  intakeController->powerIntakeRel(150, 127);
}

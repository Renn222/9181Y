#ifndef _AUTO_HPP_
#define _AUTO_HPP_

#include "main.h"

class AutoControl
{
  int selectedAuto;
public:
  void setSelectedAuto(int autoSelected);
  void startAuto();
  void autoFlagSide(bool turnCW);
};
#endif

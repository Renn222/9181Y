#ifndef _AUTO_HPP_
#define _AUTO_HPP_

#include "main.h"

class AutoControl
{
  int selectedAuto;
public:
  explicit AutoControl();
  void setSelectedAuto(int autoSelected);
  void startAuto();
};
#endif

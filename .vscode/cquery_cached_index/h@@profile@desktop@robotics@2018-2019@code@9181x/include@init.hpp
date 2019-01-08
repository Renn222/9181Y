#ifndef _INIT_HPP_
#define _INIT_HPP_

#include "main.h"

class InitControl
{
  int autoCounter = 0;
  
public:
  explicit InitControl();
  void startAutoSelector();
  void checkAutoSelected();
  void on_left_button();
  void on_right_button();
  int getSelectedAuto();
};
#endif

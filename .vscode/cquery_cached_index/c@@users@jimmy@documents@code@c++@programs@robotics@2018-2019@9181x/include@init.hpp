#ifndef _INIT_HPP_
#define _INIT_HPP_

#include "main.h"

class InitControl
{
public:
  explicit InitControl();
  void startAutoSelector();
  static void checkAutoSelected();
  static void on_left_button();
  static void on_right_button();
  void getSelectedAuto();
};
#endif

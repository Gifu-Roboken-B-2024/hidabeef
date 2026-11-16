#pragma once

#include <cstdint>

#include "./../types.hpp"
#include "tim.h"

namespace hidabeef {

class PWM {
public:
  PWM(TIM_HandleTypeDef *htim, std::uint32_t channel, std::uint32_t default_compare)
      : htim_(htim), channel_(channel), default_compare_(default_compare) {
  }

  PWM_Status init();
  PWM_Status start();

  PWM_Status setCompare(std::uint32_t compare);
  void setAutoReload(std::uint32_t arr);
  void setPrescaler(std::uint32_t psc);
  void enablePreload();
  void disablePreload();

private:
  TIM_HandleTypeDef *htim_;
  std::uint32_t channel_;
  std::uint32_t default_compare_;

  bool initialized_ = false;
};

} // namespace hidabeef

#pragma once

#include "./../types.hpp"
#include "tim.h"
#include <cstdint>

namespace hidabeef {

class PWM {
public:
  PWM(TIM_HandleTypeDef *htim, std::uint32_t channel, std::uint32_t default_compare);

  PWM_Status init();
  PWM_Status start();

  PWM_Status setCompare(std::uint32_t compare);
  void setAutoReload(std::uint32_t arr);
  void setPrescaler(std::uint32_t psc);
  void enablePreload();
  void disablePreload();

private:
  TIM_HandleTypeDef *HTIM_;
  std::uint32_t CHANNEL_;
  std::uint32_t DEFAULT_COMPARE_;

  bool initialized_ = false;
};

} // namespace hidabeef

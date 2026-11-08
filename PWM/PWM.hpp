#pragma once

#include "tim.h"
#include <cstdint>

namespace hidabeef {

enum class PWM_Status : std::uint8_t {
  Ok,
  Error,
  Busy,
  Timeout,
  NotInitialized,
  InvalidArgument,
};

class PWM {
public:
  PWM(TIM_HandleTypeDef *htim, std::uint32_t channel, std::uint32_t default_compare);

  PWM_Status init();
  PWM_Status start();

  PWM_Status setCompare(std::uint32_t compare);
private:
  TIM_HandleTypeDef *HTIM_;
  std::uint32_t CHANNEL_;
  std::uint32_t DEFAULT_COMPARE_;

  bool initialized_ = false;
};

} // namespace hidabeef

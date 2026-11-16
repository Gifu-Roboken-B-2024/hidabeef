#pragma once

#include <cstdint>

#include "./../types.hpp"
#include "can.h"

namespace hidabeef {

class CAN {
public:
  CAN(CAN_HandleTypeDef *hcan, can_config_t conf)
      : hcan_(hcan), irqn_(conf.IRQn), priority_(conf.priority), notification_(conf.notification) {};

  CAN_InitStatus start();
  HAL_StatusTypeDef send(can_frame_t data);

private:
  CAN_HandleTypeDef *hcan_;
  IRQn_Type irqn_;
  std::uint32_t priority_;
  std::uint32_t notification_;
};

} // namespace hidabeef

#pragma once

#include "./PWM/PWM.hpp"

namespace hidabeef {

struct MotorPort {
  PWM *forward = nullptr;
  PWM *backward = nullptr;
  float multiplier;
};

} // namespace hidabeef

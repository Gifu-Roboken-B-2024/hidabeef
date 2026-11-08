#pragma once

#include "./../PWM/PWM.hpp"
#include <cstdint>

namespace hidabeef {

class PiezoSpeaker {
public:
  explicit PiezoSpeaker(PWM &pwm, std::uint32_t tim_clock)
      : pwm_(pwm), tim_clock_(tim_clock) {}

  PWM_Status begin();

  void tone(std::uint32_t freq, std::uint32_t length);
  void tone(std::uint32_t freq);

private:
  PWM pwm_;
  std::uint32_t tim_clock_;
};

} // namespace hidabeef

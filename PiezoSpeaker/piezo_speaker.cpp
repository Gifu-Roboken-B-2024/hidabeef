#include "piezo_speaker.hpp"

#include "./../PWM/PWM.hpp"
#include <cstdint>

namespace hidabeef {

PWM_Status PiezoSpeaker::begin() {
  if (tim_clock_ < 1000000) {
    return PWM_Status::Error;
  }

  std::uint32_t psc = tim_clock_ / 1000000 - 1;
  pwm_.setPrescaler(psc);
  pwm_.enablePreload();

  pwm_.init();
  return pwm_.start();
}

void PiezoSpeaker::tone(std::uint32_t freq) {
  if (freq != 0) {
    std::uint32_t sound = (1000000 / freq) - 1;
    pwm_.setAutoReload(sound);
    pwm_.setCompare(sound / 2);
  } else {
    pwm_.setCompare(0);
  }
}

void PiezoSpeaker::tone(std::uint32_t freq, std::uint32_t length) {
  tone(freq);
  HAL_Delay(length);
  tone(0);
}

} // namespace hidabeef

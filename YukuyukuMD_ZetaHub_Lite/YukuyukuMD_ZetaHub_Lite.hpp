#pragma once

#include "./../PWM/PWM.hpp"
#include "./../motor_types.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace hidabeef {

struct YukuyukuMD_ZetaHub_LiteInitResult {
  // 0 -> Success, 1 -> PWM1, 2 -> PWM2
  std::uint8_t pwm_num = 0;
  PWM_Status status = PWM_Status::Ok;
};

class YukuyukuMD_ZetaHub_Lite {
public:
  static constexpr std::size_t kPortCount = 4;

  PWM_Status attach(std::uint8_t port, PWM &forward, PWM &backward, float multiplier);

  YukuyukuMD_ZetaHub_LiteInitResult init();
  YukuyukuMD_ZetaHub_LiteInitResult start();

  PWM_Status set(std::uint8_t port, std::int32_t value);

  struct StatusTypeDef {};

private:
  std::array<MotorPort, kPortCount> ports_{};
};

} // namespace hidabeef

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "./../motor_types.hpp"
#include "./../types.hpp"

namespace hidabeef {

class YukuyukuMD_ZetaHub_Lite {
public:
  static constexpr std::size_t kPortCount = 4;

  PWM_Status attach(std::uint8_t port, PWM &forward, PWM &backward, float multiplier);

  YukuyukuMD_ZetaHub_LiteResult init();
  YukuyukuMD_ZetaHub_LiteResult start();

  PWM_Status set(std::uint8_t port, std::int32_t value);

  struct StatusTypeDef {};

private:
  std::array<MotorPort, kPortCount> ports_{};
};

} // namespace hidabeef

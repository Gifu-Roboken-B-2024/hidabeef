#pragma once

#include <cstdint>

namespace hidabeef {

class PWM;
class PiezoSpeaker;
class YukuyukuMD_ZetaHub_Lite;

struct MotorPort {
  PWM *forward = nullptr;
  PWM *backward = nullptr;
  float multiplier;
};

enum class PWM_Status : std::uint8_t {
  Ok,
  Error,
  Busy,
  Timeout,
  NotInitialized,
  InvalidArgument,
};

struct YukuyukuMD_ZetaHub_LiteResult {
  // 0 -> Success, 1 -> PWM1, 2 -> PWM2
  std::uint8_t pwm_num = 0;
  PWM_Status status = PWM_Status::Ok;
};

} // namespace hidabeef

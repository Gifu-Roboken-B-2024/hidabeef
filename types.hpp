#pragma once

#include <cstdint>

#include "can.h"

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

enum class CAN_InitStatus : std::uint8_t {
  Ok,
  ConfigFilterFailed,
  InitFailed,
  StartFailed,
  ActivateNotificationFailed,
};

struct can_config_t {
  IRQn_Type IRQn;
  std::uint32_t priority;
  std::uint32_t notification;
};

struct can_frame_t {
  std::uint32_t id;
  std::uint32_t dlc;
  std::uint8_t data[8];
};

} // namespace hidabeef

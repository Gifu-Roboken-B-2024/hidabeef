#include "YukuyukuMD_ZetaHub_Lite.hpp"

#include "./../motor_types.hpp"
#include <cstddef>
#include <cstdint>

namespace hidabeef {

PWM_Status YukuyukuMD_ZetaHub_Lite::attach(std::uint8_t port, PWM &forward, PWM &backward, float multiplier) {
  if (port < 1 || port > kPortCount) {
    return PWM_Status::InvalidArgument;
  }

  ports_[port - 1] = {&forward, &backward, multiplier};
  return PWM_Status::Ok;
}

YukuyukuMD_ZetaHub_LiteInitResult YukuyukuMD_ZetaHub_Lite::init() {
  YukuyukuMD_ZetaHub_LiteInitResult result{};

  // PWM1
  for (std::size_t i = 0; i < kPortCount; i++) {
    const MotorPort &p = ports_[i];
    if (p.forward == nullptr && p.backward == nullptr) {
      continue;
    }

    if (p.forward == nullptr || p.backward == nullptr) {
      return {
          static_cast<uint8_t>(i + 1),
          PWM_Status::InvalidArgument,
      };
    }

    PWM_Status s = p.forward->init();
    if (s == PWM_Status::Ok) {
      s = p.backward->init();
    }

    if (s != PWM_Status::Ok) {
      return {
          static_cast<std::uint8_t>(i + 1),
          s,
      };
    }
  }

  return result;
}

YukuyukuMD_ZetaHub_LiteInitResult YukuyukuMD_ZetaHub_Lite::start() {
  YukuyukuMD_ZetaHub_LiteInitResult result{};

  // PWM1
  for (std::size_t i = 0; i < kPortCount; i++) {
    const MotorPort &p = ports_[i];
    if (p.forward == nullptr && p.backward == nullptr) {
      continue;
    }

    if (p.forward == nullptr || p.backward == nullptr) {
      return {
          static_cast<uint8_t>(i + 1),
          PWM_Status::InvalidArgument,
      };
    }

    PWM_Status s = p.forward->start();
    if (s == PWM_Status::Ok) {
      s = p.backward->start();
    }

    if (s != PWM_Status::Ok) {
      return {
          static_cast<std::uint8_t>(i + 1),
          s,
      };
    }
  }

  return result;
}

PWM_Status YukuyukuMD_ZetaHub_Lite::set(std::uint8_t port, std::int32_t value) {
  if (port < 1 || port > kPortCount) {
    return PWM_Status::InvalidArgument;
  }
  const MotorPort &p = ports_[port - 1];
  if (p.forward == nullptr || p.backward == nullptr) {
    return PWM_Status::InvalidArgument;
  }

  value *= p.multiplier;

  const std::uint32_t mag = static_cast<std::uint32_t>(value < 0 ? -value : value);
  PWM *off = value >= 0 ? p.backward : p.forward;
  PWM *on = value >= 0 ? p.forward : p.backward;

  PWM_Status s = off->set(0);
  if (s != PWM_Status::Ok) {
    return s;
  }

  return on->set(mag);
}

} // namespace hidabeef

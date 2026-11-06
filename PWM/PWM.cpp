#include "PWM.hpp"

#include "tim.h"
#include <cstdint>

namespace {

hidabeef::PWM_Status from_hal(HAL_StatusTypeDef s) {
  switch (s) {
  case HAL_OK:
    return hidabeef::PWM_Status::Ok;
  case HAL_BUSY:
    return hidabeef::PWM_Status::Busy;
  case HAL_ERROR:
    return hidabeef::PWM_Status::Error;
  case HAL_TIMEOUT:
    return hidabeef::PWM_Status::Timeout;
  default:
    return hidabeef::PWM_Status::Error;
  }
}

} // namespace

namespace hidabeef {

PWM::PWM(TIM_HandleTypeDef *htim, std::uint32_t channel,
         std::uint32_t default_compare)
    : HTIM_(htim), CHANNEL_(channel), DEFAULT_COMPARE_(default_compare) {}

PWM_Status PWM::init() {
  if (HTIM_ == nullptr) {
    return PWM_Status::Error;
  }

  HAL_StatusTypeDef hal_status = HAL_OK;
  if (HTIM_->State == HAL_TIM_STATE_RESET) {
    hal_status = HAL_TIM_PWM_Init(HTIM_);
  }

  PWM_Status status = from_hal(hal_status);
  if (status == PWM_Status::Ok) {
    initialized_ = true;
  }

  return status;
}

PWM_Status PWM::start() {
  if (!initialized_) {
    return PWM_Status::NotInitialized;
  }

  __HAL_TIM_SET_COMPARE(HTIM_, CHANNEL_, DEFAULT_COMPARE_);
  return from_hal(HAL_TIM_PWM_Start(HTIM_, CHANNEL_));
}

PWM_Status PWM::set(std::uint32_t compare) {
  if (!initialized_) {
    return PWM_Status::NotInitialized;
  }

  if (compare > __HAL_TIM_GET_AUTORELOAD(HTIM_)) {
    return PWM_Status::InvalidArgument;
  }

  __HAL_TIM_SET_COMPARE(HTIM_, CHANNEL_, compare);
  return PWM_Status::Ok;
}

} // namespace hidabeef

#include "PWM.hpp"

#include <cstdint>

#include "./../types.hpp"
#include "tim.h"

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

PWM_Status PWM::init() {
  if (htim_ == nullptr) {
    return PWM_Status::Error;
  }

  HAL_StatusTypeDef hal_status = HAL_OK;
  if (htim_->State == HAL_TIM_STATE_RESET) {
    hal_status = HAL_TIM_PWM_Init(htim_);
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

  __HAL_TIM_SET_COMPARE(htim_, channel_, default_compare_);
  return from_hal(HAL_TIM_PWM_Start(htim_, channel_));
}

PWM_Status PWM::setCompare(std::uint32_t compare) {
  if (!initialized_) {
    return PWM_Status::NotInitialized;
  }

  if (compare > __HAL_TIM_GET_AUTORELOAD(htim_)) {
    return PWM_Status::InvalidArgument;
  }

  __HAL_TIM_SET_COMPARE(htim_, channel_, compare);
  return PWM_Status::Ok;
}

void PWM::setAutoReload(std::uint32_t arr) {
  __HAL_TIM_SET_AUTORELOAD(htim_, arr);
}

void PWM::setPrescaler(std::uint32_t psc) {
  __HAL_TIM_SET_PRESCALER(htim_, psc);
}

void PWM::enablePreload() {
  __HAL_TIM_ENABLE_OCxPRELOAD(htim_, channel_);
}

void PWM::disablePreload() {
  __HAL_TIM_DISABLE_OCxPRELOAD(htim_, channel_);
}

} // namespace hidabeef

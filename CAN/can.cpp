#include "can.hpp"

#include <cstdint>

#include "can.h"

namespace hidabeef {

CAN_InitStatus CAN::start() {
  HAL_StatusTypeDef result;

  CAN_FilterTypeDef filter;
  filter.FilterIdHigh = 0;
  filter.FilterIdLow = 0;
  filter.FilterMaskIdHigh = 0;
  filter.FilterMaskIdLow = 0;
  filter.FilterScale = CAN_FILTERSCALE_32BIT;
  filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  filter.FilterBank = 0;
  filter.FilterMode = CAN_FILTERMODE_IDMASK;
  filter.SlaveStartFilterBank = 14;
  filter.FilterActivation = ENABLE;
  result = HAL_CAN_ConfigFilter(hcan_, &filter);
  if (result != HAL_OK) {
    return CAN_InitStatus::ConfigFilterFailed;
  }

  result = HAL_CAN_Init(hcan_);
  if (result != HAL_OK) {
    return CAN_InitStatus::InitFailed;
  }

  HAL_NVIC_SetPriority(irqn_, priority_, 0);
  HAL_NVIC_EnableIRQ(irqn_);

  result = HAL_CAN_Start(hcan_);
  if (result != HAL_OK) {
    return CAN_InitStatus::StartFailed;
  }

  result = HAL_CAN_ActivateNotification(hcan_, notification_);
  if (result != HAL_OK) {
    return CAN_InitStatus::ActivateNotificationFailed;
  }

  return CAN_InitStatus::Ok;
}

HAL_StatusTypeDef CAN::send(can_frame_t data) {
  CAN_TxHeaderTypeDef TxHeader;
  std::uint32_t TxMailbox;

  while (0 == HAL_CAN_GetTxMailboxesFreeLevel(hcan_)) {
    ;
  }

  TxHeader.StdId = data.id;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = data.dlc;
  TxHeader.TransmitGlobalTime = DISABLE;

  return HAL_CAN_AddTxMessage(hcan_, &TxHeader, data.data, &TxMailbox);
}

} // namespace hidabeef

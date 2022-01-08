/*
 * Gps_Sensor.c
 *
 *  Created on: Jan 6, 2022
 *      Author: yg
 */

#include "main.h"
#include "FreeRTOSConfig.h"


extern UART_HandleTypeDef huart3;

extern uint8_t gpx_rxdata; //this variable is defined at main.c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

  if (huart->Instance == USART3)
  {
	  configPRINT_STRING((&gpx_rxdata));
	  HAL_UART_Receive_IT(&huart3, &gpx_rxdata, 1);
  }

}

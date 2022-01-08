/*
 * Gps_Sensor.c
 *
 *  Created on: Jan 6, 2022
 *      Author: yg
 */

#include "main.h"
#include "FreeRTOSConfig.h"
#include "tm_stm32f4_gps.h"

extern UART_HandleTypeDef huart3;

extern uint8_t gpx_rxdata; //this variable is defined at main.c
extern TM_GPS_Data_t GPS_Data; //this variable is defined at main.c
TM_GPS_Result_t gps_result, gps_current;
TM_GPS_Float_t GPS_Floa_la;
TM_GPS_Float_t GPS_Floa_lon;
TM_GPS_Float_t GPS_Floa_al;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

  if (huart->Instance == USART3)
  {
   // our project, USART3 is connected to gps Module NEO-6M
#if 1
	  gps_result=TM_GPS_Update(&GPS_Data,gpx_rxdata); //after perform this function, parsing result is saved at GPS_Data

	  if (gps_result == TM_GPS_Result_NewData) {
	              /* We received new packet of useful data from GPS */
	              gps_current = TM_GPS_Result_NewData;

	              /* Is GPS signal valid? */
	              if (GPS_Data.Validity) {
	                  /* If you want to make a GPS tracker, now is the time to save your data on SD card */

	  #ifndef GPS_DISABLE_GPGGA
	                  /* GPGGA data */

	                  /* Latitude */
	                  /* Convert float to integer and decimal part, with 6 decimal places */
	                  TM_GPS_ConvertFloat(GPS_Data.Latitude, &GPS_Floa_la, 6);

	                  /* Longitude */
	                  /* Convert float to integer and decimal part, with 6 decimal places */
	                  TM_GPS_ConvertFloat(GPS_Data.Longitude, &GPS_Floa_lon, 6);

	                  /* Altitude */
	                  /* Convert float to integer and decimal part, with 6 decimal places */
	                  TM_GPS_ConvertFloat(GPS_Data.Altitude, &GPS_Floa_al, 6);

				#if 0
	                  /* Current time */
	                  sprintf(buffer, " - UTC Time: %02d.%02d.%02d:%02d\n", GPS_Data.Time.Hours, GPS_Data.Time.Minutes, GPS_Data.Time.Seconds, GPS_Data.Time.Hundredths);
	                  TM_USART_Puts(USART3, buffer);

	                  /* Fix: 0 = invalid, 1 = GPS, 2 = DGPS */
	                  sprintf(buffer, " - Fix: %d\n", GPS_Data.Fix);
	                  TM_USART_Puts(USART3, buffer);

	                  /* Satellites in use */
	                  sprintf(buffer, " - Sats in use: %02d\n", GPS_Data.Satellites);
	                  TM_USART_Puts(USART3, buffer);
				#endif

#endif
	              } else {
	                  /* GPS signal is not valid */
	            	  configPRINT_STRING("New received data haven't valid GPS signal!\n");
	              }
	          } else if (gps_result == TM_GPS_Result_FirstDataWaiting && gps_current != TM_GPS_Result_FirstDataWaiting) {
	              gps_current = TM_GPS_Result_FirstDataWaiting;
	              configPRINT_STRING( "Waiting first data from GPS!\n");
	          } else if (gps_result == TM_GPS_Result_OldData && gps_current != TM_GPS_Result_OldData) {
	              gps_current = TM_GPS_Result_OldData;
	              /* We already read data, nothing new was received from GPS */
	          }

#endif

  }




	  //configPRINT_STRING((&gpx_rxdata));//test purpose. print all GPS output sentence.
	  HAL_UART_Receive_IT(&huart3, &gpx_rxdata, 1);
  }


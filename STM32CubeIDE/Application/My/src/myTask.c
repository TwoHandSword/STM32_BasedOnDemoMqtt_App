/*
 * myTask.c
 *
 *  Created on: 2021. 12. 26.
 *      Author: yg
 */

#include "platform/iot_threads.h"
#include "aws_demo_config.h"
#include "FreeRTOSConfig.h"
#include "Warmer.h"
#include "main.h"
#include "tm_stm32f4_gps.h"
#include "AdcHal.h"
#include <stdio.h>
#include "aws_customdemo_runner.h"
#include "st_sensordata_collector.h"


extern float onboard_TEMPERATURE_Value;
extern float onboard_HUMIDITY_Value;
extern int16_t onboard_ACC_Value[3];


void myTask_1ms(void);
void myTask_100ms(void);
void myTask_1sec(void);
void myTask_2sec(void);

/*
 * bool Iot_CreateDetachedThread( IotThreadRoutine_t threadRoutine,
                               void * pArgument,
                               int32_t priority,
                               size_t stackSize );
 * */

void my_task_init(void)
{

#if 0
	Iot_CreateDetachedThread(myTask_1ms,
							 NULL,
							 democonfigDEMO_PRIORITY,
							 democonfigDEMO_STACKSIZE
						   );
#endif

#if 0
	Iot_CreateDetachedThread(myTask_100ms,
								 NULL,
								 democonfigDEMO_PRIORITY,
								 democonfigDEMO_STACKSIZE
							   );
#endif

		Iot_CreateDetachedThread(myTask_1sec,
									 NULL,
									 democonfigDEMO_PRIORITY,
									 democonfigDEMO_STACKSIZE
								   );


		Iot_CreateDetachedThread(myTask_2sec,
											 NULL,
											 democonfigDEMO_PRIORITY,
											 democonfigDEMO_STACKSIZE
										   );

}





void myTask_1ms(void)
{
		static int cnt =0;
		portTickType xLastWakeTime;
		portTickType xFrequency = 1;

		xLastWakeTime = xTaskGetTickCount();

	configPRINTF( ( "MyTask 1ms start \r\n" ) );


	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		cnt++;
		configPRINTF( ( "MyTask periodic run : %d\r\n" ,cnt) );

	}


}


void myTask_100ms(void)
{
	static int cnt =0;
	portTickType xLastWakeTime;
	portTickType xFrequency = 100;

	xLastWakeTime = xTaskGetTickCount();

	configPRINTF( ( "MyTask 100ms start .\r\n" ) );


	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, xFrequency);



	}


}


extern TM_GPS_Float_t GPS_Floa_la;
extern TM_GPS_Float_t GPS_Floa_lon;
extern TM_GPS_Float_t GPS_Floa_al;
extern TM_GPS_Data_t GPS_Data;

void myTask_1sec(void)
{
	static int cnt =0;
	portTickType xLastWakeTime;
	portTickType xFrequency = 1000;

	uint32_t adcVal[2];

	xLastWakeTime = xTaskGetTickCount();

	configPRINTF( ( "MyTask 1sec start .\r\n" ) );


		while(1)
		{
			vTaskDelayUntil(&xLastWakeTime, xFrequency);


			#if 0
			cnt++;
			configPRINTF(("1sec task is running : %d\n",cnt));

			#endif

			adc_start_conversion();

			#if 0
			adcVal[0] = get_adc_value(1);
			adcVal[1] = get_adc_value(2);

			configPRINTF( ("adc value 1 : %d\n",adcVal[0]) );
			configPRINTF( ("adc value 2 : %d\n",adcVal[1]) );

			#endif


			Warmer_Control();
			

			#if 0
			configPRINT_STRING("GPGGA statement:\n");
			configPRINTF( ("-Latitude: %d.%d\n", GPS_Floa_la.Integer, GPS_Floa_la.Decimal) );

			configPRINTF( ("-Longitude: %d.%d\n", GPS_Floa_lon.Integer, GPS_Floa_lon.Decimal) );
			configPRINTF( ("-Altitude: %3d.%06d\n", GPS_Floa_al.Integer, GPS_Floa_al.Decimal)		);
//			configPRINTF( ("-Time: %02d.%02d.%02d\n", GPS_Data.Time.Hours, GPS_Data.Time.Minutes, GPS_Data.Time.Seconds) );
			#endif

		}


}

extern float onboard_TEMPERATURE_Value;
extern float onboard_HUMIDITY_Value;
extern int16_t onboard_ACC_Value[3];

unsigned char Topic_SenSor_Temp[]="stm/temperature";
unsigned char Topic_SenSor_Humid[]="stm/hum";
unsigned char Topic_SenSor_Acc[]="stm/accel";
unsigned char Topic_SenSor_gps[]="stm/gps";
unsigned char Topic_SenSor_warmertemp[]="stm/heat";
extern int mqtt_conection_done;
extern int service_start_command;

void myTask_2sec(void)
{

	char *pSensorPayload;
	int publishStatus=0;
	int snprintfreturn;

	static int cnt =0;
	portTickType xLastWakeTime;
	portTickType xFrequency = 2000;


	xLastWakeTime = xTaskGetTickCount();

	configPRINTF( ( "MyTask 2sec start .\r\n" ) );

	prvSensorsInit();


	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, xFrequency);

		OnBoardSensorRead();

		configPRINTF( ( "Temp : %d \r\n", (int)onboard_TEMPERATURE_Value) );


#if 1
		if(service_start_command==1)
		{
			if(mqtt_conection_done==1)
				{
						pSensorPayload = pvPortMalloc(sizeof(char) * 100);

						/* Format data for transmission to AWS */

						// out temperature
						snprintfreturn = snprintf(pSensorPayload, 100,
								"{\"data\":%d}",(int)onboard_TEMPERATURE_Value);

						publishStatus = _publishSensorData(Topic_SenSor_Temp, pSensorPayload,snprintfreturn);


						// out humid
						snprintfreturn = snprintf(pSensorPayload, 100,
								"{\"data\":%d}",(int)onboard_HUMIDITY_Value);

						publishStatus = _publishSensorData(Topic_SenSor_Humid, pSensorPayload,snprintfreturn);

						// out acc [x]
						snprintfreturn = snprintf(pSensorPayload, 100,
								"{\n\"x\":%d,\n\"y\":%d,\n\"z\":%d\n}",(int)onboard_ACC_Value[0],(int)onboard_ACC_Value[1],(int)onboard_ACC_Value[2]);

						publishStatus = _publishSensorData(Topic_SenSor_Acc, pSensorPayload,snprintfreturn);


						//gps x y z
						snprintfreturn = snprintf(pSensorPayload, 100,
									"{\n\"lat\":%d.%d,\n\"lan\":%d.%d\n}",(int)GPS_Floa_la.Integer,(int)GPS_Floa_la.Decimal,(int)GPS_Floa_lon.Integer,(int)GPS_Floa_lon.Decimal);
						publishStatus = _publishSensorData(Topic_SenSor_gps, pSensorPayload,snprintfreturn);


						// Warmer Temp
						int warmer_temp=(int)Warmer_GetTemp();

						snprintfreturn = snprintf(pSensorPayload, 100,
														"{\"data\":%d}",(int)warmer_temp);
						publishStatus = _publishSensorData(Topic_SenSor_warmertemp, pSensorPayload,snprintfreturn);

						configPRINTF( ( "warmer Temp : %d \r\n", (int)warmer_temp) );

						vPortFree(pSensorPayload);
				}
		}
#endif

	}


}





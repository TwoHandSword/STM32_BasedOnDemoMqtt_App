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



void myTask_1ms(void);
void myTask_100ms(void);
void myTask_1sec(void);

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

			#if 1
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

/*
 * myTask.c
 *
 *  Created on: 2021. 12. 26.
 *      Author: yg
 */

#include "platform/iot_threads.h"
#include "aws_demo_config.h"
#include "FreeRTOSConfig.h"


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


void myTask_1sec(void)
{
	static int cnt =0;
	portTickType xLastWakeTime;
	portTickType xFrequency = 1000;

	xLastWakeTime = xTaskGetTickCount();

	configPRINTF( ( "MyTask 1sec start .\r\n" ) );


		while(1)
		{
			vTaskDelayUntil(&xLastWakeTime, xFrequency);


			#if 0
			cnt++;
			configPRINTF(("1sec task is running : %d\n",cnt));

			#endif


		}


}

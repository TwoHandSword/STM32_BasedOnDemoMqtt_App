/*
 * aws_RxParser.c
 *
 *  Created on: 2022. 1. 5.
 *      Author: yg
 */

#define SERVICE_START "{\"OnOff\":1}"
#define SERVICE_STOP  "{\"OnOff\":0}"


#define WARMER_OFF   "{\"warmer\":0}"
#define WARMER_ON_1  "{\"warmer\":1}"
#define WARMER_ON_2  "{\"warmer\":2}"

#include "FreeRTOSConfig.h"
#include "string.h"
#include "Warmer.h"
#include "main.h"

int service_start_command;


void aws_RxMqttParse(const char * pPayload , int payloadlen, const char *pTopicName, int topicnamelen)
{

	if(strncmp(pPayload,SERVICE_START,payloadlen)==0)
				{
		    		configPRINTF( ( "\nServi Start \n\n" ) );
		    		Warmer_SetOper(warmer_off);
		    		service_start_command=1;
		    		HAL_GPIO_WritePin(START_LED_GPIO_Port, START_LED_Pin, GPIO_PIN_SET);
				}
	else if(strncmp(pPayload,SERVICE_STOP,payloadlen)==0)
				{
					configPRINTF( ( "\nServi Stop \n\n" ) );
					service_start_command=0;
					Warmer_SetOper(warmer_off);
		    		HAL_GPIO_WritePin(START_LED_GPIO_Port, START_LED_Pin, GPIO_PIN_RESET);
				}




	if(strncmp(pPayload,WARMER_OFF,payloadlen)==0)
			{
	    		configPRINTF( ( "Heater Off \n" ) );
	    		Warmer_SetOper(warmer_off);
			}
	    else if(strncmp(pPayload,WARMER_ON_1,payloadlen)==0)
			{
				configPRINTF( ( "Heater On . grade:1\n" ) );
				Warmer_SetOper(warmer_on_1);
			}
	    else if(strncmp(pPayload,WARMER_ON_2,payloadlen)==0)
			{
				configPRINTF( ( "Heater On . grade:2\n" ) );
				Warmer_SetOper(warmer_on_2);
			}

}

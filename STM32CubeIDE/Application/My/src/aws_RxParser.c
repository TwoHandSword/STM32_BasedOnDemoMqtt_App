/*
 * aws_RxParser.c
 *
 *  Created on: 2022. 1. 5.
 *      Author: yg
 */

#define WARMER_OFF   "01_1_0"
#define WARMER_ON_1  "01_1_1"
#define WARMER_ON_2  "01_1_2"

#include "FreeRTOSConfig.h"
#include "string.h"
#include "Warmer.h"

void aws_RxMqttParse(const char * pPayload , int payloadlen, const char *pTopicName, int topicnamelen)
{

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

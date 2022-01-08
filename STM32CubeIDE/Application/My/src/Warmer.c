/*
 * Warmer.c
 *
 *  Created on: Jan 5, 2022
 *      Author: yg
 */

#include "AdcHal.h"
#include "Warmer.h"


#define REF_DEGREE_1		(35)
#define REF_DEGREE_2		(50)


static warmer_oper g_operation;


float Warmer_GetTemp()
{
	float temperature = 0;
	float temp_sen_volt=0;


	/*temp function will be implemented    */

	#if 1
	temp_sen_volt = get_adc_volt(1);
	temperature = (temp_sen_volt - 0.5) * 100;
	#endif

	return temperature;

}

void Warmer_SetOper(warmer_oper operation)
{
	g_operation = operation;
}


void Warmer_Control()
{
	float temp=0;

	temp=Warmer_GetTemp();

	if( g_operation == warmer_off)
	{

		//pin off

	}
	else if(g_operation == warmer_on_1)
	{

		if(temp>warmer_on_1)
		{
			//pin off
		}
		else
		{
			//pin on
		}

	}
	else if(g_operation == warmer_on_2)
	{

		if(temp>warmer_on_2)
		{
			//pin off
		}
		else
		{
			//pin on
		}

	}
	else
	{
		//pin off

	}


}

/*
 * AdcHal.c
 *
 *  Created on: Jan 8, 2022
 *      Author: yg
 */

#define ADC_RESULT_MAX		(4095)
#define ADC_REF_VOL 		(3.3f)

#include "main.h"
#include "AdcHal.h"

extern ADC_HandleTypeDef hadc1;


uint32_t adc_result_arr[NUM_OF_ADC_CH];
float adc_volt_offset = 0.05f;


void adc_start_conversion()
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc_result_arr, 2);

}


uint32_t get_adc_value(uint32_t ch_num)
{
	uint32_t adc_result = 0;
	uint32_t arr_index = ch_num -1; //the reason is that ch number of adc start with 1 not 0

	if ( (ch_num > NUM_OF_ADC_CH) && (ch_num < 1) )
	{
			adc_result = -1; //-1 means error
	}
	else
	{
		adc_result = adc_result_arr[arr_index];
	}

	return adc_result;

}

float get_adc_volt(uint32_t ch_num)
{
	uint32_t adc_result = 0;
	float adc_vol_result = 0;

	adc_result=get_adc_value(ch_num);

	adc_vol_result = (adc_result*ADC_REF_VOL/ADC_RESULT_MAX) + adc_volt_offset;

	return adc_vol_result;

}


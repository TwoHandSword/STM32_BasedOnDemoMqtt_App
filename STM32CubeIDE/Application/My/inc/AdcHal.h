/*
 * AdcHal.h
 *
 *  Created on: Jan 8, 2022
 *      Author: yg
 */

#ifndef APPLICATION_MY_INC_ADCHAL_H_
#define APPLICATION_MY_INC_ADCHAL_H_

#include <stdint.h>

#define NUM_OF_ADC_CH		(16)

extern uint32_t adc_result_arr[NUM_OF_ADC_CH];

void adc_start_conversion(void);
uint32_t get_adc_value(uint32_t ch_num);
float get_adc_volt(uint32_t ch_num);

#endif /* APPLICATION_MY_INC_ADCHAL_H_ */

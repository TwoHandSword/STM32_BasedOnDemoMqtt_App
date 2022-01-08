/*
 * Warmer.h
 *
 *  Created on: Jan 5, 2022
 *      Author: yg
 */

#ifndef APPLICATION_MY_INC_WARMER_H_
#define APPLICATION_MY_INC_WARMER_H_

typedef enum warmer_oper{
	warmer_off,
	warmer_on_1,
	warmer_on_2
}warmer_oper;

void Warmer_SetOper(warmer_oper operation);
void Warmer_Control(void);


#endif /* APPLICATION_MY_INC_WARMER_H_ */

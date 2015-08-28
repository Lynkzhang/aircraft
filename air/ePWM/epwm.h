/*
 * PWM.h
 *
 *  Created on: 2015Äê7ÔÂ10ÈÕ
 *      Author: szy
 */

#ifndef PWM_H_
#define PWM_H_

#include "..\common.h"

#define MPU6050_ADDR        0x68
#define I2C_NUMBYTES          1

void HRPWM1_Config(Uint16);
void HRPWM2_Config(Uint16);
void HRPWM3_Config(Uint16);
void HRPWM4_Config(Uint16);
void HRPWM1_SetDuty(Uint16,Uint16 ,Uint16);
void HRPWM2_SetDuty(Uint16,Uint16 ,Uint16);
void HRPWM3_SetDuty(Uint16,Uint16 ,Uint16);
void HRPWM4_SetDuty(Uint16,Uint16 ,Uint16);



#endif /* PWM_H_ */

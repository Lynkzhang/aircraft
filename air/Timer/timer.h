/*
 * timer.h
 *
 *  Created on: 2015��7��10��
 *      Author: szy
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "..\common.h"

void Timer_init();
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

#endif /* TIMER_H_ */

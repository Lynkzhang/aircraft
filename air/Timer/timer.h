/*
 * timer.h
 *
 *  Created on: 2015Äê7ÔÂ10ÈÕ
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

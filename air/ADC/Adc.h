/*
 * Adc.h
 *
 *  Created on: 2015��7��16��
 *      Author: szy
 */

#ifndef ADC_H_
#define ADC_H_

#include "..\common.h"
void Adc_init();
__interrupt void adc_isr();

#endif /* ADC_H_ */

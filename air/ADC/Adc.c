/*
 * Adc.c
 *
 *  Created on: 2015Äê7ÔÂ16ÈÕ
 *      Author: szy
 */
#include "Adc.h"
int temp=0;
int temp2=0;
void Adc_init(){
	EALLOW;  // This is needed to write to EALLOW protected register
	PieVectTable.ADCINT1 = &adc_isr;
	EDIS;
	InitAdc();
	AdcOffsetSelfCal();
	EALLOW;
	//GpioCtrlRegs.AIOMUX1.bit.AIO6 = 0;    // Configure AIO2 for A2 (analog input) operation
	//GpioCtrlRegs.AIOMUX1.bit.AIO4 = 0;    // Configure AIO4 for A4 (analog input) operation
	//GpioCtrlRegs.AIOMUX1.bit.AIO6 = 2;    // Configure AIO6 for A6 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;   // Configure AIO10 for B2 (analog input) operation
	GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;   // Configure AIO12 for B4 (analog input) operation
	//GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;   // Configure AIO14 for B6 (analog input) operation
	EDIS;

	EALLOW;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	//ADCINT1 trips after AdcResults latch
	AdcRegs.INTSEL1N2.bit.INT1E     = 1;	//Enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;	//Disable ADCINT1 Continuous mode
	AdcRegs.INTSEL1N2.bit.INT1SEL	= 2;	//setup EOC2 to trigger ADCINT1 to fire
	AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 10;	//set SOC0 channel select to ADCINA0
	AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 12;	//set SOC1 channel select to ADCINA1
	//AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 2;	//set SOC1 channel select to ADCINA2
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 1;	//set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 1;	//set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	//AdcRegs.ADCSOC2CTL.bit.TRIGSEL 	= 5;	//set SOC2 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1, then SOC2
	AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 13;	//set SOC0 S/H Window to 14 ADC Clock Cycles, (13 ACQPS plus 1)
	AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 13;	//set SOC1 S/H Window to 14 ADC Clock Cycles, (13 ACQPS plus 1)
	//AdcRegs.ADCSOC2CTL.bit.ACQPS 	= 13;	//set SOC2 S/H Window to 14 ADC Clock Cycles, (13 ACQPS plus 1)
	AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

	AdcRegs.INTSEL1N2.bit.INT1SEL = 1;
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;
	AdcRegs.INTSEL1N2.bit.INT1E  = 1;
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
	EDIS;

//	AdcRegs.INTSEL1N2.bit.INT1SEL = 0; 		//Connect ADCINT1 to EOC0
//	   AdcRegs.INTSEL1N2.bit.INT1E  =  1; 		//Enable ADCINT1

}
__interrupt void adc_isr(){
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

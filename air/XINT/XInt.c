/*
 * XInt.c
 *
 *  Created on: 2015Äê7ÔÂ12ÈÕ
 *      Author: szy
 */
#include "XInt.h"

extern int16 xint3_count;
extern int32 signal;

void XInt_init(){

	EALLOW;
	PieVectTable.XINT3 = &xint3_isr;
	EDIS;

	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO12=0x00;
	GpioCtrlRegs.GPAMUX2.bit.GPIO19=0x00;

	GpioCtrlRegs.GPADIR.bit.GPIO12=0; //GPIO12 is input
	GpioCtrlRegs.GPADIR.bit.GPIO19=1; //GPIO19 is output

	GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL=12;
	EDIS;

	XIntruptRegs.XINT3CR.bit.POLARITY=3;
	XIntruptRegs.XINT3CR.bit.ENABLE=1;

	PieCtrlRegs.PIEIER12.bit.INTx1=1;

	IER|=M_INT12;

	EINT;
	ERTM;
}

__interrupt void xint3_isr(void){
	PieCtrlRegs.PIEACK.all=PIEACK_GROUP12;
	xint3_count++;
	if (xint3_count>200) xint3_count=0;
	if (GpioDataRegs.GPADAT.bit.GPIO12==1) 	CpuTimer1Regs.TCR.bit.TSS = 0;
	else if (GpioDataRegs.GPADAT.bit.GPIO12==0){
		CpuTimer1Regs.TCR.bit.TSS = 1;
		signal=(60000000-CpuTimer1Regs.TIM.all)*340/2/600000;
		CpuTimer1Regs.TCR.bit.TRB = 1;
	}

}


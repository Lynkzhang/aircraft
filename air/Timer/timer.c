/*
 * timer.c
 *
 *  Created on: 2015Äê7ÔÂ10ÈÕ
 *      Author: szy
 */

#include "timer.h"

extern int16 TimerIntcount_Mpu6050;
int count=0,i=0;
int16 adc_ccd_result[120];
int16 adc_ccd_result2[120];
int16 pic[120];
int16 pic2[120];

void Timer_init(){
	 EALLOW;  // This is needed to write to EALLOW protected registers
	 PieVectTable.TINT0 = &cpu_timer0_isr;
	 PieVectTable.TINT1 = &cpu_timer1_isr;
	 PieVectTable.TINT2 = &cpu_timer2_isr;
	 EDIS;

	 InitCpuTimers();   // For this example, only initialize the Cpu Timers

	 ConfigCpuTimer(&CpuTimer0, 60, 100);
	 ConfigCpuTimer(&CpuTimer1, 60, 1000000);
	 ConfigCpuTimer(&CpuTimer2, 60, 1000000);

	 CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	 CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	 CpuTimer2Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0

	 IER |= M_INT1;
	 IER |= M_INT13;
	 IER |= M_INT14;

	 PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

	 EINT; // Enable Global interrupt INTM
	 ERTM; // Enable Global realtime interrupt DBGM
}
__interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;

   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
   //TimerIntcount_Mpu6050=1;
   //GpioDataRegs.GPATOGGLE.bit.GPIO19=1;
   switch (count){
   case 0:{GpioDataRegs.GPATOGGLE.bit.GPIO6=1;		//si
	   	   GpioDataRegs.GPATOGGLE.bit.GPIO7=1;		//clock
	   	   ++count;
	   	   break;
   }
   case 1:{
	   GpioDataRegs.GPATOGGLE.bit.GPIO6=1;		//si
	   GpioDataRegs.GPATOGGLE.bit.GPIO7=1;		//clock
	   ++count;
	   	GpioDataRegs.GPATOGGLE.bit.GPIO19=1;
	   	TimerIntcount_Mpu6050+=1;
	   break;
   }
   case 255:{
	   GpioDataRegs.GPATOGGLE.bit.GPIO7=1;
	   count=0;
	   i=0;
	   break;
   }
   default :{
	   GpioDataRegs.GPATOGGLE.bit.GPIO7=1;
	   ++count;
	   if((GpioDataRegs.GPADAT.bit.GPIO7==1)&&(i<120)) {pic[i]=AdcResult.ADCRESULT0;pic2[i]=AdcResult.ADCRESULT1;++i;}
	   break;
   }
   }
}

__interrupt void cpu_timer1_isr(void)
{
   CpuTimer1.InterruptCount++;
   // The CPU acknowledges the interrupt.
   EDIS;
}

__interrupt void cpu_timer2_isr(void)
{  EALLOW;
   CpuTimer2.InterruptCount++;
   // The CPU acknowledges the interrupt.
   EDIS;
}

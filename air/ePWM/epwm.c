/*
 * epwm.c
 *
 *  Created on: 2015Äê7ÔÂ10ÈÕ
 *      Author: szy
 */
#include "epwm.h"

void HRPWM1_Config(Uint16 period)
{
// ePWM1 register configuration with HRPWM
// ePWM1A toggle low/high with MEP control on Rising edge

	EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm1Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm1Regs.CMPA.half.CMPA = period / 2;              // set duty 50% initially
    EPwm1Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm1Regs.CMPB = period / 2;	                    // set duty 50% initially
	EPwm1Regs.TBPHS.all = 0;
	EPwm1Regs.TBCTR = 0;

	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;		       // EPwm1 is the Master
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;               // PWM toggle low/high
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;

	EALLOW;
	EPwm1Regs.HRCNFG.all = 0x0;
	EPwm1Regs.HRCNFG.bit.EDGMODE = HR_REP;				//MEP control on Rising edge
	EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;
	EPwm1Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
	EDIS;
}

void HRPWM2_Config(Uint16 period)
{
// ePWM2 register configuration with HRPWM
// ePWM2A toggle low/high with MEP control on Rising edge

	EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm2Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm2Regs.CMPA.half.CMPA = period / 2;              // set duty 50% initially
    EPwm1Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm2Regs.CMPB = period / 2;	                    // set duty 50% initially
	EPwm2Regs.TBPHS.all = 0;
	EPwm2Regs.TBCTR = 0;

	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;		         // EPwm2 is the Master
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;

	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;                  // PWM toggle low/high
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;

	EALLOW;
	EPwm2Regs.HRCNFG.all = 0x0;
	EPwm2Regs.HRCNFG.bit.EDGMODE = HR_REP;                //MEP control on Rising edge
	EPwm2Regs.HRCNFG.bit.CTLMODE = HR_CMP;
	EPwm2Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

	EDIS;

}
void HRPWM3_Config(Uint16 period)
{
// ePWM3 register configuration with HRPWM
// ePWM3A toggle high/low with MEP control on falling edge

	EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm3Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm3Regs.CMPA.half.CMPA = period / 2;              // set duty 50% initially
	EPwm3Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm3Regs.TBPHS.all = 0;
	EPwm3Regs.TBCTR = 0;

	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;		        // EPwm3 is the Master
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;                  // PWM toggle high/low
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;

	EALLOW;
	EPwm3Regs.HRCNFG.all = 0x0;
	EPwm3Regs.HRCNFG.bit.EDGMODE = HR_FEP;               //MEP control on falling edge
	EPwm3Regs.HRCNFG.bit.CTLMODE = HR_CMP;
	EPwm3Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
	EDIS;
}

void HRPWM4_Config(Uint16 period)
{
// ePWM4 register configuration with HRPWM
// ePWM4A toggle high/low with MEP control on falling edge

	EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm4Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm4Regs.CMPA.half.CMPA = period / 2;              // set duty 50% initially
	EPwm4Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm4Regs.CMPB = period / 2;	                    // set duty 50% initially
	EPwm4Regs.TBPHS.all = 0;
	EPwm4Regs.TBCTR = 0;

	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;		        // EPwm4 is the Master
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;                  // PWM toggle high/low
	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm4Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;

	EALLOW;
	EPwm4Regs.HRCNFG.all = 0x0;
	EPwm4Regs.HRCNFG.bit.EDGMODE = HR_FEP;              //MEP control on falling edge
	EPwm4Regs.HRCNFG.bit.CTLMODE = HR_CMP;
	EPwm4Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
	EDIS;
}

void HRPWM1_SetDuty(Uint16 dutyA,Uint16 dutyB,Uint16 period){
	EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm1Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm1Regs.CMPA.half.CMPA = dutyA;              // set duty
	EPwm1Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm1Regs.CMPB = dutyB;	                    // set duty 		EPwm1Regs.TBPHS.all = 0;
//	EPwm1Regs.TBCTR = 0;
}
void HRPWM2_SetDuty(Uint16 dutyA,Uint16 dutyB,Uint16 period){
	EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm2Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm2Regs.CMPA.half.CMPA = dutyA;              // set duty
	EPwm2Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm2Regs.CMPB = dutyB;	                    // set duty 		EPwm1Regs.TBPHS.all = 0;
//	EPwm2Regs.TBCTR = 0;
}
void HRPWM3_SetDuty(Uint16 dutyA,Uint16 dutyB,Uint16 period){
	EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm3Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm3Regs.CMPA.half.CMPA = dutyA;              // set duty
	EPwm3Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm3Regs.CMPB = dutyB;	                    // set duty 		EPwm1Regs.TBPHS.all = 0;
//	EPwm3Regs.TBCTR = 0;
}
void HRPWM4_SetDuty(Uint16 dutyA,Uint16 dutyB,Uint16 period){
	EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	        // set Immediate load
	EPwm4Regs.TBPRD = period-1;		                    // PWM frequency = 1 / period
	EPwm4Regs.CMPA.half.CMPA = dutyA;              // set duty
	EPwm4Regs.CMPA.half.CMPAHR = (1 << 8);              // initialize HRPWM extension
	EPwm4Regs.CMPB = dutyB;	                    // set duty		EPwm1Regs.TBPHS.all = 0;
//	EPwm4Regs.TBCTR = 0;
}


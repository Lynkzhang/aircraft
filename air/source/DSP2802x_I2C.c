// TI File $Revision: /main/2 $
// Checkin $Date: December 16, 2010   11:15:00 $
//###########################################################################
//
// FILE:	DSP2802x_I2C.c
//
// TITLE:	DSP2802x I2C Initialization & Support Functions.
//
//###########################################################################
// $TI Release: 2802x C/C++ Header Files and Peripheral Examples V1.29 $
// $Release Date: January 11, 2011 $
//###########################################################################

#include "DSP2802x_Device.h"     // DSP2802x Headerfile Include File
#include "DSP2802x_Examples.h"   // DSP2802x Examples Include File

//---------------------------------------------------------------------------
// InitI2C:
//---------------------------------------------------------------------------
// This function initializes the I2C to a known state.
//
void InitI2C(void)
{
	// Initialize I2C-A:

	//tbd...
}

//---------------------------------------------------------------------------
// Example: InitI2CGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as I2C pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for SDAA operation.
// Only one GPIO pin shoudl be enabled for SCLA operation.
// Comment out other unwanted lines.

void InitI2CGpio()
{
	EALLOW;

	/* Enable internal pull-up for the selected pins */
	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up for GPIO32 (SDAA)
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;	   // Enable pull-up for GPIO33 (SCLA)

	/* Set qualification for selected pins to asynch only */
	GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // Asynch input GPIO32 (SDAA)
	GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // Asynch input GPIO33 (SCLA)

	/* Configure I2C pins using GPIO regs*/
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   // Configure GPIO32 for SDAA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   // Configure GPIO33 for SCLA operation

	EDIS;
}

//===========================================================================
// End of file.
//===========================================================================

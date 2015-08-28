# include "i2c.h"

void I2CA_Init(void)
{
   // Initialize I2C
   I2caRegs.I2CMDR.all = 0x0000;
   I2caRegs.I2CSAR = 0;		// Slave address

   I2caRegs.I2CPSC.all = 6;		    		// Prescaler - need 7-12 Mhz on module clk
   I2caRegs.I2CCLKL = 10;					// NOTE: must be non zero
   I2caRegs.I2CCLKH = 5;					// NOTE: must be non zero

   //I2caRegs.I2CIER.all = 0x24;			// Enable SCD & ARDY interrupts  0010 0100
   I2caRegs.I2CIER.bit.AAS = 0;				// Addressed as slave interrupt enable bit
   I2caRegs.I2CIER.bit.SCD = 1;				// Stop condition detected interrupt enable bit
   I2caRegs.I2CIER.bit.XRDY = 0;			// Transmit-data-ready interrupt enable bit
   I2caRegs.I2CIER.bit.XRDY = 0;			// Receive-data-ready interrupt enable bit
   I2caRegs.I2CIER.bit.ARDY = 1;			// Register-access-ready interrupt enable bit
   I2caRegs.I2CIER.bit.NACK = 0;			// No-acknowledgment interrupt enable bit
   I2caRegs.I2CIER.bit.ARBL = 0;			// Arbitration-lost interrupt enable bit

   //I2caRegs.I2CMDR.all = 0x0020;			// Take I2C out of reset,Stop I2C when suspended
   I2caRegs.I2CMDR.bit.NACKMOD = 0;			// NACK mode bit
   I2caRegs.I2CMDR.bit.FREE = 0;			// Stop I2C when suspended
   I2caRegs.I2CMDR.bit.STT = 0;				// START condition bit
   I2caRegs.I2CMDR.bit.STP = 0;				// STOP condition bit
   I2caRegs.I2CMDR.bit.MST = 0;				// Slave mode
   I2caRegs.I2CMDR.bit.TRX = 0;				// Receiver mode
   I2caRegs.I2CMDR.bit.XA = 0;				// 7-bit addressing mode
   I2caRegs.I2CMDR.bit.RM = 0;				// Nonrepeat mode
   I2caRegs.I2CMDR.bit.DLB = 0;				// Digital loopback mode is disabled
   I2caRegs.I2CMDR.bit.IRS = 1;				// The I2C module is enabled
   I2caRegs.I2CMDR.bit.STB = 0;				// The I2C module is not in the START byte mode
   I2caRegs.I2CMDR.bit.FDF = 0;				// Free data format mode is disabled
   I2caRegs.I2CMDR.bit.BC = 0;				// 8 bits per data byte

   //I2caRegs.I2CFFTX.all = 0x6000;			// Enable FIFO mode and TXFIFO
   I2caRegs.I2CFFTX.bit.I2CFFEN = 1;		// Enable the I2C FIFO mode
   I2caRegs.I2CFFTX.bit.TXFFRST = 1;		// Enable the transmit FIFO operation
   I2caRegs.I2CFFTX.bit.TXFFINTCLR = 0;		// Clear the TXFFINT flag
   I2caRegs.I2CFFTX.bit.TXFFIENA = 0;		// TXFFINT flag does not generate an interrupt when set
   I2caRegs.I2CFFTX.bit.TXFFIL = 0;			// Transmit FIFO interrupt level

   I2caRegs.I2CFFRX.all = 0x2040;			// Enable RXFIFO, clear RXFFINT
   I2caRegs.I2CFFRX.bit.RXFFRST = 1;		// Enable the receive FIFO operation
   I2caRegs.I2CFFRX.bit.RXFFINTCLR = 1;		// Clear the RXFFINT flag
   I2caRegs.I2CFFRX.bit.RXFFIENA = 0;		// RXFFINT flag does generate an interrupt when set
   I2caRegs.I2CFFRX.bit.RXFFIL = 0;			// Receive FIFO interrupt level

   return;
}

uint16 I2CA_WriteData(uint16 addr, uint16 reg, uint16 data)
{
	I2caRegs.I2CMDR.bit.IRS = 1; 				// reset I2C

	// Make sure I2C is not busy and has stopped
	while (I2caRegs.I2CSTR.bit.BB == 1);		// busy loop
	I2caRegs.I2CSTR.bit.SCD = 1;				// Clear the SCD bit (stop condition bit)
	while(I2caRegs.I2CMDR.bit.STP == 1);		// stop bit loop

	I2caRegs.I2CSAR = addr;           			// I2C slave address
	while (I2caRegs.I2CSTR.bit.BB == 1);		// still busy?

    I2caRegs.I2CCNT = 2;						// assume register address = 1 byte, and data is 1 byte

	I2caRegs.I2CMDR.all = 0x6E20; 				// start, stop, no rm, reset i2c  01101110 00100000
//	I2caRegs.I2CMDR.bit.NACKMOD = 0;			// NACK mode bit
//	I2caRegs.I2CMDR.bit.FREE = 1;				// Run free I2C when suspended
//	I2caRegs.I2CMDR.bit.STT = 1;				// START condition bit
//	I2caRegs.I2CMDR.bit.STP = 1;				// STOP condition bit
//	I2caRegs.I2CMDR.bit.MST = 1;				// Master mode
//	I2caRegs.I2CMDR.bit.TRX = 1;				// Transmitter mode
//	I2caRegs.I2CMDR.bit.XA = 0;					// 7-bit addressing mode
//	I2caRegs.I2CMDR.bit.RM = 0;					// Nonrepeat mode
//	I2caRegs.I2CMDR.bit.DLB = 0;				// Digital loopback mode is disabled
//	I2caRegs.I2CMDR.bit.IRS = 1;				// The I2C module is enabled
//	I2caRegs.I2CMDR.bit.STB = 0;				// The I2C module is not in the START byte mode
//	I2caRegs.I2CMDR.bit.FDF = 0;				// Free data format mode is disabled
//	I2caRegs.I2CMDR.bit.BC = 0;					// 8 bits per data byte
    I2caRegs.I2CDXR = reg;						// register address of the sensor (1 byte)
    I2caRegs.I2CDXR = data;						// data to be sent (1 byte)

	I2caRegs.I2CMDR.bit.STP = 1;  				// stop bit when CNT=0

    while(!I2caRegs.I2CSTR.bit.SCD);       	// wait for STOP condition

	return I2C_SUCCESS;
}


uint16 I2CA_ReadData(uint16 addr, uint16 reg)
{
	Uint16 tempdata;

	I2caRegs.I2CMDR.bit.IRS = 1; 				// reset I2C

	// Make sure I2C is not busy and has stopped
	while (I2caRegs.I2CSTR.bit.BB == 1);		// busy loop
	I2caRegs.I2CSTR.bit.SCD = 1;				// Clear the SCD bit (stop condition bit)
	while(I2caRegs.I2CMDR.bit.STP == 1);		// stop bit loop

	I2caRegs.I2CSAR = addr;				// I2C slave address

	while (I2caRegs.I2CSTR.bit.BB == 1);		// still busy?

	I2caRegs.I2CMDR.all = 0x2620;				// start, no stop bit, master, tx, reset I2C 00100110
//	I2caRegs.I2CMDR.bit.NACKMOD = 0;			// NACK mode bit
//	I2caRegs.I2CMDR.bit.FREE = 0;				// Stop I2C when suspended
//	I2caRegs.I2CMDR.bit.STT = 1;				// START condition bit
//	I2caRegs.I2CMDR.bit.STP = 0;				// STOP condition bit
//	I2caRegs.I2CMDR.bit.MST = 1;				// Master mode
//	I2caRegs.I2CMDR.bit.TRX = 1;				// Transmitter mode
//	I2caRegs.I2CMDR.bit.XA = 0;					// 7-bit addressing mode
//	I2caRegs.I2CMDR.bit.RM = 0;					// Nonrepeat mode
//	I2caRegs.I2CMDR.bit.DLB = 0;				// Digital loopback mode is disabled
//	I2caRegs.I2CMDR.bit.IRS = 1;				// The I2C module is enabled
//	I2caRegs.I2CMDR.bit.STB = 0;				// The I2C module is not in the START byte mode
//	I2caRegs.I2CMDR.bit.FDF = 0;				// Free data format mode is disabled
//	I2caRegs.I2CMDR.bit.BC = 0;					// 8 bits per data byte

	I2caRegs.I2CCNT		= 1;					// assume register address is one byte
	I2caRegs.I2CDXR		= reg;					// register address of the sensor (1 byte)

	while(!I2caRegs.I2CSTR.bit.ARDY);			// all ready?

	I2caRegs.I2CMDR.all = 0x2C20;				// start, stop bit when CNT =0, master, rx, reset I2C 00101100
//	I2caRegs.I2CMDR.bit.NACKMOD = 0;			// NACK mode bit
//	I2caRegs.I2CMDR.bit.FREE = 0;				// Stop I2C when suspended
//	I2caRegs.I2CMDR.bit.STT = 1;				// START condition bit
//	I2caRegs.I2CMDR.bit.STP = 1;				// STOP condition bit
//	I2caRegs.I2CMDR.bit.MST = 1;				// Master mode
//	I2caRegs.I2CMDR.bit.TRX = 0;				// Receiver mode
//	I2caRegs.I2CMDR.bit.XA = 0;					// 7-bit addressing mode
//	I2caRegs.I2CMDR.bit.RM = 0;					// Nonrepeat mode
//	I2caRegs.I2CMDR.bit.DLB = 0;				// Digital loopback mode is disabled
//	I2caRegs.I2CMDR.bit.IRS = 1;				// The I2C module is enabled
//	I2caRegs.I2CMDR.bit.STB = 0;				// The I2C module is not in the START byte mode
//	I2caRegs.I2CMDR.bit.FDF = 0;				// Free data format mode is disabled
//	I2caRegs.I2CMDR.bit.BC = 0;					// 8 bits per data byte
//	I2caRegs.I2CCNT		= 1;					// only read one byte data

	if(I2caRegs.I2CSTR.bit.NACK == 1)
	{
		 I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT; 	// 0x0002
	}
	I2caRegs.I2CMDR.bit.STP = 1;					// stop bit when CNT=0

	while(!I2caRegs.I2CSTR.bit.SCD);				// stop bit detected?

	tempdata	= I2caRegs.I2CDRR;					// read one byte data

	return(tempdata);
}


uint8 i2cWrite(uint8 addr, uint8 reg, uint8 data)
{
	return I2CA_WriteData(addr, reg, data);
}
uint8 i2cRead(uint8 addr, uint8 reg)
{
	return I2CA_ReadData(addr, reg);
}

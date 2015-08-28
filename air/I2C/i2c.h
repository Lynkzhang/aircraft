#ifndef F28069I2C_1_I2C_I2C_H_
#define F28069I2C_1_I2C_I2C_H_

#include "..\common.h"

#define MPU6050_ADDR        0x68
#define I2C_NUMBYTES          1

void I2CA_Init(void);
uint16 I2CA_WriteData(uint16 addr, uint16 reg, uint16 data);
uint16 I2CA_ReadData(uint16 addr, uint16 reg);

uint8 i2cWrite(uint8 addr, uint8 reg, uint8 data);
uint8 i2cRead(uint8 addr, uint8 reg);

#endif /* F28069I2C_1_I2C_I2C_H_ */

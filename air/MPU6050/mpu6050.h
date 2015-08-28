#ifndef F28069I2C_1_MPU6050_MPU6050_H_
#define F28069I2C_1_MPU6050_MPU6050_H_

#include "..\common.h"
#include "..\I2C\i2c.h"

//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19		//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A		//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG	    0x1B		//陀螺仪自检及测量范围，测量范围值：0x10(不自检，1000deg/s)
#define	ACCEL_CONFIG	0x1C		//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define USER_CTRL		0x6A
#define	PWR_MGMT_1		0x6B		//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75		//IIC地址寄存器(默认数值0x68，只读)
#define	MPU6050_ADDR	0x68		//IIC写入时的地址字节数据，+1为读取

#define   GYRO_SCALE_250dps		1
#define   GYRO_SCALE_500dps		2
#define   GYRO_SCALE_1000dps	3
#define   GYRO_SCALE_2000dps	4


#define   GYRO_SCALE   GYRO_SCALE_500dps

void  MPU6050_Init();
int16 MPU6050_GetData(char REG_Address);	//返回高地位合成后的数据


#endif /* F28069I2C_1_MPU6050_MPU6050_H_ */

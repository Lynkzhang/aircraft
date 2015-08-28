#ifndef F28069I2C_1_MPU6050_MPU6050_H_
#define F28069I2C_1_MPU6050_MPU6050_H_

#include "..\common.h"
#include "..\I2C\i2c.h"

//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19		//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A		//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG	    0x1B		//�������Լ켰������Χ��������Χֵ��0x10(���Լ죬1000deg/s)
#define	ACCEL_CONFIG	0x1C		//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define	PWR_MGMT_1		0x6B		//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		0x75		//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	MPU6050_ADDR	0x68		//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

#define   GYRO_SCALE_250dps		1
#define   GYRO_SCALE_500dps		2
#define   GYRO_SCALE_1000dps	3
#define   GYRO_SCALE_2000dps	4


#define   GYRO_SCALE   GYRO_SCALE_500dps

void  MPU6050_Init();
int16 MPU6050_GetData(char REG_Address);	//���ظߵ�λ�ϳɺ������


#endif /* F28069I2C_1_MPU6050_MPU6050_H_ */

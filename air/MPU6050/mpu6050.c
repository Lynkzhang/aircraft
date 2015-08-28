# include "mpu6050.h"

//static float gyro_coeff;


//**************************************
//初始化
//**************************************
void MPU6050_Init()
{
	i2cWrite(MPU6050_ADDR, PWR_MGMT_1, 0x00);	//解除休眠状态
	i2cWrite(MPU6050_ADDR, SMPLRT_DIV, 0x07);
	i2cWrite(MPU6050_ADDR, CONFIG, 0x06);

	//选择量程
	#if GYRO_SCALE == GYRO_SCALE_250dps
	i2cWrite(MPU6050_ADDR, GYRO_CONFIG, 0x00);
	//gyro_coeff = 131.072;
	#endif
	#if GYRO_SCALE == GYRO_SCALE_500dps
	i2cWrite(MPU6050_ADDR, GYRO_CONFIG, 0x08);
	//gyro_coeff = 65.536;
	#endif
	#if GYRO_SCALE == GYRO_SCALE_1000dps
	i2cWrite(MPU6050_ADDR, GYRO_CONFIG, 0x10);
	//gyro_coeff = 32.768;
	#endif
	#if GYRO_SCALE == GYRO_SCALE_2000dps
	i2cWrite(MPU6050_ADDR, GYRO_CONFIG, 0x18);
	//gyro_coeff = 16.384;
	#endif

	i2cWrite(MPU6050_ADDR, ACCEL_CONFIG, 0x00);
}

//**************************************
//读取并合成数据
//**************************************
int16 MPU6050_GetData(char REG_Address)
{
	int8 H,L;
	H = i2cRead(MPU6050_ADDR, REG_Address);
	L = i2cRead(MPU6050_ADDR, REG_Address+1);
	return (H<<8)+L;   //合成数据
}



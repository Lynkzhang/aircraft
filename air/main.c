#include "includes.h"
#define MAX 7570
#define MIN 3940
#define MID1 5585//5745
#define MID2 5575
#define MID4 5600


extern int16 adc_ccd_result[120];
extern int16 adc_ccd_result2[120];
uint16 max=0,min=65535;
uint16 max2=0,min2=65535;
extern int16 pic[120];
extern int16 pic2[120];
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;


// These are defined by the linker (see F2808.cmd)


int16 t,t2; //raw adc reading

uint32 loop_count = 0;
//CCD data
int16 coun = 0;

long adc_ccd_avg;
long adc_ccd_avg2;
int l=0,l2=0;
int r=127,r2=127;
int mid=63,mid2=63;
int center;
int hc;
char control;
int flag=0;
int pp=0,ii=0,dd=0;

int16 ADuty = MID1, BDuty = MID2, CDuty = MIN, DDuty = MID4;//a,dir duty

int16 gyro[3], accel[3], temperature;

int16 who = 0, who1 = 0;

int16 TimerIntcount_Mpu6050 = 0, xint3_count = 0;//control signal

int32 signal;//height temp
int Height[5]={16,16,16,16,16};//height data
double setspeed=0;
double setspeedinc= 0;
double speed[4]={0,0,0,0};

double Velocity=0,Acceleration=0,Velocitytemp=0;//高度运动数据
double SetHeight = 60.0;

int16 X=-296,Y=12,Z=996;//3-D acc


////////////////////////////////////////////////////////


double kp=4,ki=0.02,kd=85;
double sp=0.16,si=0,sd=2;
double cp=2,ci=0,cd=40;
////////////////////////////////////////////////////////
//double err=0,err_next=0,err_last=0;
int16 inc=0;

Uint16 re = 0;//uart recive char.
Uint16 lock_flag = 1 , auto_flag = 0 , down_flag = 0;
int upflag;
int ccdloc=0,ccdlastloc=0;
double ccdinc=0;

void main(void)
 {

	InitSysCtrl();

	DINT;

	InitPieCtrl();

	IER = 0x0000;
	IFR = 0x0000;

	InitPieVectTable();

	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();

	InitEPwm1Gpio();
	InitEPwm2Gpio();

	scia_init();
	printString("\n\nSystem run...\n");
	printString("Sci initialization done...\n");

	InitI2CGpio();
	I2CA_Init();
//	who1 = i2cRead(MPU6050_ADDR, WHO_AM_I);
//	MPU6050_Init();
//	who	= i2cRead(MPU6050_ADDR, WHO_AM_I);					// read one byte data

	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM

	Timer_init();
	CpuTimer1Regs.TCR.bit.TSS = 1;

	XInt_init();

	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0x00;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0x00;

	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;

	EDIS;

	Adc_init();


	EALLOW;



	EDIS;

	EALLOW;

 	EDIS;

	EINT;   // Enable Global interrupt INTM
  	ERTM;   // Enable Global realtime interrupt DBGM



	HRPWM1_Config(65535);
	HRPWM1_SetDuty(ADuty, BDuty, 65535);
	HRPWM2_Config(65535);
	HRPWM2_SetDuty(CDuty, DDuty, 65535);



	ADuty=MID1;
	BDuty=MID1;
	CDuty=MIN;
	DDuty=MAX;
	HRPWM1_SetDuty(ADuty, BDuty, 65535);
	HRPWM2_SetDuty(CDuty, DDuty, 65535);
	printInfo("unlock", 1);
	DELAY_MS(5000);
	ADuty=MID1;
	BDuty=MID2;
	CDuty=MIN;
	DDuty=MID4;
	HRPWM1_SetDuty(MID1, MID2, 65535);
	HRPWM2_SetDuty(MIN, MID4, 65535);
	lock_flag = 0;

	for (;;)
	{
		flag=0;
		loop_count++;
		if(!lock_flag)
		{

			for(hc=0;hc<=3;hc++){
				Height[hc]=Height[hc+1];
			}
			Height[4]=signal;
			if((Height[4] - Height[3]) > 15 || (Height[3] - Height[4]) >15)
				Height[4]=Height[3]+(Height[3]-Height[0])/3;
			for(hc=0;hc<=3;hc++){
					speed[hc]=Height[hc+1]-Height[hc];
			}
			//if(Height[4]>=33)
			//	setspeed=0;
			//else setspeed=6;

			setspeed = (SetHeight - Height[4])/6;

			if(setspeed<=0)
				setspeed=0;
			pp=setspeed-speed[3];
			ii=4*setspeed-speed[0]-speed[1]-speed[2]-speed[3];
			dd=speed[3]-speed[2];
			inc=kp*(pp)+ki*(ii)-kd*(dd);

			CDuty+=inc;
			if(CDuty >= 5600)
				CDuty=5600;
			if(CDuty <= MIN)
				CDuty=MIN;
			if(lock_flag=0)
				loop_count++;


			if(loop_count == 500 || signal > 150)
			{
								ADuty=MID1;
								BDuty=MID1;
								CDuty=MIN;
								DDuty=MIN;
								HRPWM1_SetDuty(ADuty, BDuty, 65535);
								HRPWM2_SetDuty(CDuty, DDuty, 65535);
								printInfo("lock", 1);
								DELAY_MS(5000);
								ADuty=MID1;
								BDuty=MID2;
								CDuty=MIN;
								DDuty=MID4;
								HRPWM1_SetDuty(MID1, MID2, 65535);
								HRPWM2_SetDuty(MIN, MID4, 65535);
								inc=0;
								lock_flag = 1;
			}
				/*
				flag=0;
				loop_count=0;
				adc_ccd_avg=0;
				adc_ccd_avg2=0;
				for (coun = 0; coun < 120; coun ++)
				{

					adc_ccd_result[coun]=pic[coun];
					adc_ccd_result2[coun]=pic2[coun];
					if (max < pic[coun])
						max=pic[coun];
					if (min > pic[coun])
						min=pic[coun];
					if (max2 < pic2[coun])
						max2=pic2[coun];
					if (min2 > pic2[coun])
						min2=pic2[coun];
				}

			}
			adc_ccd_avg=max+min/2;
			adc_ccd_avg2=max2+min2/2;


			if(adc_ccd_result[0]>=adc_ccd_avg)
				adc_ccd_result[0]=250;
			else
				adc_ccd_result[0]=0;


			if(adc_ccd_result2[0]>=adc_ccd_avg2)
				adc_ccd_result2[0]=250;
			else
				adc_ccd_result2[0]=0;


			for (coun = 0; coun < 120; coun ++)
			{
				if(adc_ccd_result[coun]>=adc_ccd_avg)
					adc_ccd_result[coun]=250;
				else
					adc_ccd_result[coun]=0;
				if(adc_ccd_result[coun-1]==250 && adc_ccd_result[coun]==0 )
					l=coun;
				if(adc_ccd_result[coun-1]==0 && adc_ccd_result[coun]==250 )
					r=coun-1;

				if(adc_ccd_result2[coun]>=adc_ccd_avg2)
					adc_ccd_result2[coun]=250;
				else
					adc_ccd_result2[coun]=0;
				if(adc_ccd_result2[coun-1]==250 && adc_ccd_result2[coun]==0 )
					l2=coun;
				if(adc_ccd_result2[coun-1]==0 && adc_ccd_result2[coun]==250 )
					r2=coun-1;
			}



			mid=(l+r)/2;
			mid2=(l2+r2)/2;
			center=(mid+mid2)/2;
			ccdloc=center;

			ccdinc=cp*(63-center)+cd*(ccdloc-ccdlastloc);


			ADuty+=ccdinc;
			ccdlastloc=ccdloc;
			if(ADuty<=MIN)
				ADuty=MIN;
			if(ADuty>=5700)
				ADuty=5700;


			*/
		}
		while (SciaRegs.SCIFFRX.bit.RXFFST != 0 )//手动模式
		{
			re = SciaRegs.SCIRXBUF.all;
			printInfo("set ", re);
			switch (re){
			case '1':{ADuty = MIN; HRPWM1_SetDuty(ADuty, BDuty, 65535); printInfo("\nADuty: ", ADuty); break; }
			case '2':{ADuty = MAX; HRPWM1_SetDuty(ADuty, BDuty, 65535); printInfo("\nADuty: ", ADuty); break; }
			case '3':{BDuty = MIN; HRPWM1_SetDuty(ADuty, BDuty, 65535); printInfo("\nBDuty: ", BDuty); break; }
			case '4':{BDuty = MAX; HRPWM1_SetDuty(ADuty, BDuty, 65535); printInfo("\nBDuty: ", BDuty); break; }
			case '5':{CDuty = MIN; HRPWM2_SetDuty(CDuty, DDuty, 65535); printInfo("\nCDuty: ", CDuty); break; }
			case '6':{CDuty = MAX; HRPWM2_SetDuty(CDuty, DDuty, 65535); printInfo("\nCDuty: ", CDuty); break; }
			case '7':{DDuty = MIN; HRPWM2_SetDuty(CDuty, DDuty, 65535); printInfo("\nDDuty: ", DDuty); break; }
			case '8':{DDuty = MAX; HRPWM2_SetDuty(CDuty, DDuty, 65535); printInfo("\nDDuty: ", DDuty); break; }
			}

			//仿照下面分支编写指令
			if (re == ','){
				ADuty=MID1;
				BDuty=MID1;
				CDuty=MIN;
				DDuty=MAX;
				HRPWM1_SetDuty(ADuty, BDuty, 65535);
				HRPWM2_SetDuty(CDuty, DDuty, 65535);
				printInfo("unlock", 1);
				DELAY_MS(5000);
				ADuty=MID1;
				BDuty=MID2;
				CDuty=MIN;
				DDuty=MID4;
				HRPWM1_SetDuty(MID1, MID2, 65535);
				HRPWM2_SetDuty(MIN, MID4, 65535);
				lock_flag = 0;
			}
			else if (re == '.'){
				ADuty=MID1;
				BDuty=MID1;
				CDuty=MIN;
				DDuty=MIN;
				HRPWM1_SetDuty(ADuty, BDuty, 65535);
				HRPWM2_SetDuty(CDuty, DDuty, 65535);
				printInfo("lock", 1);
				DELAY_MS(5000);
				ADuty=MID1;
				BDuty=MID2;
				CDuty=MIN;
				DDuty=MID4;
				HRPWM1_SetDuty(MID1, MID2, 65535);
				HRPWM2_SetDuty(MIN, MID4, 65535);
				inc=0;
				lock_flag = 1;
			}
			else if (re == 'q'){
				DDuty-=50;
				if(DDuty <= MIN)
				{DDuty=MIN;}
				HRPWM2_SetDuty(CDuty, DDuty, 65535);

			}
			else if (re == 'e'){
				DDuty+=50;
				if(DDuty >= MAX)
				{DDuty=MAX;}
				HRPWM2_SetDuty(CDuty, DDuty, 65535);

			}
			else if (re == '/')
			{
				ADuty=MID1;
				BDuty=MID1;
				CDuty=MIN;
				DDuty=MID1;
				HRPWM1_SetDuty(MID1, MID1, 65535);
				HRPWM2_SetDuty(MIN, MID1, 65535);
				printInfo("common", 1);
			}

			else if(re == '+')
			{
				CDuty+=50;
				if(CDuty>=MAX)
					CDuty=MAX;
				HRPWM2_SetDuty(CDuty, DDuty, 65535);
			}

			else if(re == '-')
			{
				CDuty-=50;
				if(CDuty<=MIN)
					CDuty=MIN;
				HRPWM2_SetDuty(CDuty, DDuty, 65535);
			}
			else if(re == 'w')
			{
				BDuty-=50;
				if(BDuty<=MIN)
					BDuty=MIN;
				HRPWM1_SetDuty(ADuty, BDuty, 65535);
			}
			else if(re == 's')
			{
				BDuty+=50;
				if(BDuty>=MAX)
					BDuty=MAX;
				HRPWM1_SetDuty(ADuty, BDuty, 65535);
			}
			else if(re == 'a')
			{
				ADuty-=50;
				if(ADuty<=MIN)
					ADuty=MIN;
				HRPWM1_SetDuty(ADuty, BDuty, 65535);
			}
			else if(re == 'd')
			{
				ADuty+=50;
				if(ADuty>=MAX)
					ADuty=MAX;
				HRPWM1_SetDuty(ADuty, BDuty, 65535);
			}


		}
		if (TimerIntcount_Mpu6050 >= 2)
		{//传感器数据记录及自动控制

			TimerIntcount_Mpu6050 = 0;
			//get info
//			accel[0] = MPU6050_GetData(ACCEL_XOUT_H)>>4;
//			accel[1] = MPU6050_GetData(ACCEL_YOUT_H)>>4;
//			accel[2] = MPU6050_GetData(ACCEL_ZOUT_H)>>4;
//			gyro[0] = MPU6050_GetData(GYRO_XOUT_H)>>6;
//			gyro[1] = MPU6050_GetData(GYRO_YOUT_H)>>6;
//			gyro[2] = MPU6050_GetData(GYRO_ZOUT_H)>>6;
//			temperature = MPU6050_GetData(TEMP_OUT_H) / 34 + 350;
			//calculate

			//info output
//			printInfo("\nAccel X: ", accel[0]);
//			printInfo("		Accel Y: ", accel[1]);
//			printInfo("		Accel Z: ", accel[2]);
			printInfo("\nSignal:", signal);
			printInfo("\tinc:",inc);
			printInfo("\tP: ", pp);
			printInfo("\tI: ", ii);
			printInfo("\tD: ", dd);
			printInfo("\tADuty: ", ADuty);

		}
		DELAY_MS(50);
		HRPWM1_SetDuty(ADuty, BDuty, 65535);
		HRPWM2_SetDuty(CDuty, DDuty, 65535);
		/*
		if(flag)
		{
			ADuty=MID1;
			BDuty=MID2;
			DDuty=MID4;
			HRPWM1_SetDuty(ADuty, BDuty, 65535);
			HRPWM2_SetDuty(CDuty, DDuty, 65535);
		}


		*/
	}
}


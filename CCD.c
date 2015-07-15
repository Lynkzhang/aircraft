#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>   //中断函数头文件
#define uchar unsigned char
#define uint unsigned int
#define TSL1401_SI_0 PORTB&=~(1<<PB5)
#define TSL1401_SI_1 PORTB|=(1<<PB5)
#define TSL1401_CLK_0 PORTB&=~(1<<PB7)
#define TSL1401_CLK_1 PORTB|=(1<<PB7)

#define F_CPU 11059200
//常量声明
#define BAUD 115200         //波特率设置值

//全局变量声明
unsigned int ADData;          //AD转换获得的数据

//函数声明
void Port_Init(void);  //端口初始化配置
void Usart_Init(void);  //USART寄存器设置
void AD_Init(void);    //AD初始化
void Usart_PutChar(unsigned char cTXData);  //字节发送函数
void Usart_PutString(unsigned char *pcString);  // 字符串发送数据
unsigned int AD_GetData(void);    //AD转换函数
void SendHex(unsigned char hex);
void SendImageData(unsigned char * ImageData);
void StartIntegration(void);
void ImageCapture(unsigned char * ImageData) ;
unsigned char Pixel[128];
/* 曝光时间，单位ms */
unsigned char IntegrationTime = 10;
/*计算曝光时间*/

int main(void)
{
	unsigned char j;
	unsigned char i;
	unsigned char send_data_cnt = 0;
	unsigned char *pixel_pt;
	Port_Init();
	Usart_Init();
	AD_Init();
	pixel_pt = Pixel;
	for(i=0; i<128+10; i++) {
		*pixel_pt++ = 0;
		}
	//Usart_PutString("AD转换测试程序");
	//Usart_PutString("测得ADC0通道的电压值为：");

	sei();          //使能全局中断

	while(1)
	{
		StartIntegration();
		

		_delay_ms(15);
		ImageCapture(Pixel);
		if((++j)==3)
		{
			j=0;
		}
		SendImageData(Pixel);	
	}
}
void ImageCapture(unsigned char * ImageData)
{

	unsigned char i;
	unsigned int  temp_int;

	TSL1401_SI_1;         /* SI  = 1 */
	_delay_ms(1);
	TSL1401_CLK_1;        /* CLK = 1 */
	_delay_ms(1);
	TSL1401_SI_0;         /* SI  = 0 */
	_delay_ms(1);

	//Delay 20us for sample the first pixel
	
	for(i = 0; i < 25; i++)
		{                //更改25，让CCD的图像看上去比较平滑，
			_delay_us(1);                     //把该值改大或者改小达到自己满意的结果。
		}


//Sampling Pixel 1
	temp_int = AD_GetData();
	*ImageData++ = (uchar)(temp_int>>4);
	TSL1401_CLK_0;        /* CLK = 0 */

	for(i=0; i<127; i++) {
		_delay_ms(1);
		_delay_ms(1);
		TSL1401_CLK_1;    /* CLK = 1 */
		_delay_ms(1);
		_delay_ms(1);
		//Sampling Pixel 2~128
		temp_int = AD_GetData();
		*ImageData++ = (uchar)(temp_int>>4);
		TSL1401_CLK_0;    /* CLK = 0 */
	}
	_delay_ms(1);
	_delay_ms(1);
	TSL1401_CLK_1;        /* CLK = 1 */
	_delay_ms(1);
	_delay_ms(1);
	TSL1401_CLK_0;        /* CLK = 0 */
}







void StartIntegration(void) {

	unsigned char i;

	TSL1401_SI_1;         /* SI  = 1 */
	_delay_ms(1);
	TSL1401_CLK_1;        /* CLK = 1 */
	_delay_ms(1);
	TSL1401_SI_0;         /* SI  = 0 */
	_delay_ms(1);
	TSL1401_CLK_0;        /* CLK = 0 */

	for(i=0; i<127; i++) {
		_delay_ms(1);
		_delay_ms(1);
		TSL1401_CLK_1;    /* CLK = 1 */
		_delay_ms(1);
		_delay_ms(1);
		TSL1401_CLK_0;    /* CLK = 0 */
	}
	_delay_ms(1);
	_delay_ms(1);
	TSL1401_CLK_1;        /* CLK = 1 */
	_delay_ms(1);
	_delay_ms(1);
	TSL1401_CLK_0;        /* CLK = 0 */
}
void SendImageData(unsigned char * ImageData)
 {

	unsigned char i;
	unsigned char crc = 0;

	/* Send Data */
	Usart_PutChar('*');
	Usart_PutChar('L');
	Usart_PutChar('D');

	SendHex(0);
	SendHex(0);
	SendHex(0);
	SendHex(0);

	for(i=0; i<128; i++) {
		SendHex(*ImageData++);
	}

	SendHex(crc);
	Usart_PutChar('#');
}



void SendHex(unsigned char hex) {
	unsigned char temp;
	temp = hex >> 4;
	if(temp < 10) {
		Usart_PutChar(temp + '0');
	} else {
		Usart_PutChar(temp - 10 + 'A');
	}
	temp = hex & 0x0F;
	if(temp < 10) {
		Usart_PutChar(temp + '0');
	} else {
		Usart_PutChar(temp - 10 + 'A');
	}
}


//端口状态初始化设置函数
void Port_Init()
{
	PORTA= 0X00;
	DDRA= 0x00;  //ADC通道设置为输入口，高阻态
	PORTB=0x00;
	DDRB=0xff;

}

//USART寄存器配置函数
void Usart_Init()
{
	UCSRA= 0X00;
	UCSRC|= (1<<URSEL) | (1 << UCSZ1) | (1 << UCSZ0);  //异步，数据格式8，N，1
	//UCSRC寄存器与UBRRH寄存器共用相同的I/O地址,写 UCSRC 时， URSEL 应设置为 1。
	UBRRL= (F_CPU/ BAUD/ 16 - 1) % 256;    //波特率设置
	UBRRH= (F_CPU/ BAUD/ 16 - 1) / 256;
	UCSRB|= (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);    //发送使能

}

//字节发送函数
void Usart_PutChar(unsigned char cTXData)
{
	while( !(UCSRA& (1 << UDRE)) );  //只有数据寄存器为空时才能发送数据
	UDR= cTXData;                  //发送数据送USART I/O数据寄存器－UDR
}

//接收中断函数
ISR(USART_RXC_vect)
{
	unsigned char Rev;
	Rev = UDR;              //从USART I/O数据寄存器－UDR中读出数据
	Usart_PutChar(Rev);    //将接收到的数据发送
}



void Usart_PutString(unsigned char *pcString)
{
	while (*pcString)
	{
		Usart_PutChar(*pcString++);
	}
	Usart_PutChar(0x0D);
	Usart_PutChar(0x0A);  //结尾发送回车换行
}

//AD转换初始化函数
void AD_Init()
{
	ADMUX|= (1 << REFS0);    //ADC参考电压为AVcc，ADC结果右对齐，选择通道ADC0
	ADCSRA|= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); //使能AD转换，ADC时钟64分频
}

//AD转换函数
unsigned int AD_GetData()
{uint ccd_v;
	ADCSRA|= (1 << ADSC);    //开始AD转换
	while(!(ADCSRA& (1 << ADIF)));    //等待转换完成
	ADCSRA|= (1 << ADIF);              //清零ADC中断标志位
   ccd_v=ADC*7/2;
	return ccd_v;        //返回ADC值
}

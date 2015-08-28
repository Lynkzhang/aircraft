#ifndef UART_H_
#define UART_H_
#include "..\common.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

void scia_echoback_init(void);
void scia_fifo_init(void);

void scia_init(void);
void scia_xmit(int a);


void printString(char * msg);
void printNumber(unsigned long n, uint8 base);

void printInfo(char * msg, long n);


#endif /* UART_H_ */

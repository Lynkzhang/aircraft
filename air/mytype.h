/*
 * mytype.h
 *
 *  Created on: 2015Äê1ÔÂ27ÈÕ
 *      Author: Di
 */
//Optimizing C C++ User's Guide.pdf
//chapter 6.4 Data Types


#ifndef F28069I2C_1_MYTYPE_H_
#define F28069I2C_1_MYTYPE_H_

typedef      char     int8; //in fact,16 bits.
//typedef unsigned char   Uint8;//in fact,16 bits.
typedef unsigned char   uint8;//in fact,16 bits.

//typedef int             int16;
//typedef unsigned int    Uint16;
typedef unsigned int    uint16;

//typedef long            int32;
//typedef unsigned long   Uint32;
typedef unsigned long   uint32;

//typedef long long            int64;
//typedef unsigned long long   Uint64;
typedef unsigned long long   uint64;

typedef volatile int8     vint8;
typedef volatile uint8    vuint8;

typedef volatile int16    vint16;
typedef volatile uint16   vuint16;

typedef volatile int32    vint32;
typedef volatile uint32   vuint32;

typedef volatile long long            vint64;
typedef volatile unsigned long long   vuint64;

//typedef float           float32;
//typedef long double     float64;



#endif /* F28069I2C_1_MYTYPE_H_ */

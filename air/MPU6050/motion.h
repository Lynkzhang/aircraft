/*
 * motion.h
 *
 *  Created on: 2015Äê6ÔÂ9ÈÕ
 *      Author: Di
 */

#ifndef MPU6050_MOTION_H_
#define MPU6050_MOTION_H_

#include "mpu6050.h"

#define Still			0
#define Hand_Up			1
#define Hand_Down		2

#define msg_Still		"Still\n"
#define msg_Hand_Up		"Hand_Up\n"
#define msg_Hand_Down	"Hand_Down\n"

extern int8 msg[][20];

extern uint16 current_motion;
extern uint16 pre_motion;



#endif /* MPU6050_MOTION_H_ */

/*
 * motion.c
 *
 *  Created on: 2015��6��9��
 *      Author: Di
 */


#include "motion.h"

uint16 current_motion = 0;
uint16 pre_motion = 0;

int8 msg[][20] =
{
		{"Still\n"},
		{"Hand_Up\n"},
		{"Hand_Down\n"}
};

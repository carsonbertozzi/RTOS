/*
 * pwm.h
 *
 *  Created on: Oct 30, 2018
 *      Author: garth
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#include <stdio.h>
#include "platform.h"
//#include "pwm1.h"
#include "xil_io.h"
#include "xparameters.h"

void adjust_duty(UINTPTR address, float period, float duty_cycle);
void set_frequency(UINTPTR address, float period);
void weight_pwm(UINTPTR address, float period, u32 sensoroutput );

#endif /* SRC_PWM_H_ */

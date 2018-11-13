/*
 * pwm.c
 *
 *  Created on: Oct 30, 2018
 *      Author: garth
 */

#include "pwm.h"

#include <stdio.h>
#include "platform.h"
#include "xil_io.h"
#include "xparameters.h"

#define PWMREG 0x206
#define SensorOutputRatio (0xFFFFFF/ 50.0)  //Value will be 335544.3

void adjust_duty(UINTPTR address, float period, float duty_cycle)
{

	float duty_factor = 100.0 / duty_cycle;

	Xil_Out32(address + 0x14, (((period/1e-9) / duty_factor) / 10) - 2 );

    Xil_Out32(address, 0x206);
    Xil_Out32(address + 0x10, 0x606);


}

void set_frequency(UINTPTR address, float period)
{
	Xil_Out32(address + 0x4, ((period/1e-9) / 10) - 2 );
}


void weight_pwm(UINTPTR address, float period, u32 sensoroutput )
{
	float variable_duty = (sensoroutput/SensorOutputRatio) + 50.0;

	adjust_duty(address, period, variable_duty);

}

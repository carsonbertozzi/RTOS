

/***************************** Include Files **********************************/

#include "xparameters.h"
#include "xspips.h"
#include "xil_printf.h"
#include "spi.h"

#include <stdio.h>
#include<stdlib.h>

/************************** Constant Definitions ******************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define SPI_DEVICE_ID		XPAR_XSPIPS_0_DEVICE_ID
#define SENSOR_DATA_LEN 3


/************************** Variable Definitions ******************************/

XSpiPs Spi;			/* The instance of the SPI device */

u8 buff[3] = {1, 2, 3};

/******************************************************************************/
int main(void)
{
	spi_init(SPI_DEVICE_ID, &Spi);
	u32 value;

	spi_read(&Spi, buff, buff, SENSOR_DATA_LEN);
	const u32 tare = buff[0] << 16  | buff[1] << 8 | buff[2];

	while (1)
	{
		spi_read(&Spi, buff, buff, SENSOR_DATA_LEN);
		value = buff[0] << 16  | buff[1] << 8 | buff[2];
		value = abs (tare - value);


	}
	return 0;
}

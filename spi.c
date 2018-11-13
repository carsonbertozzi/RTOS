/*
 * spi.c
 *
 *  Created on: Oct 25, 2018
 *      Author: Carson
 */
#include "spi.h"
#include "math.h"

static u32 tare;

u8 spi_init(u16 SpiDeviceId, XSpiPs *SpiInstancePtr){

	XSpiPs_Config *SpiConfig;
	int Status;

	SpiConfig = XSpiPs_LookupConfig(SpiDeviceId);
	if (NULL == SpiConfig) {
		return 13;
	}

	Status = XSpiPs_CfgInitialize(SpiInstancePtr, SpiConfig,
					SpiConfig->BaseAddress);
	if (Status != XST_SUCCESS) {
		return 14;
	}

	/*
	 * Set the SPI device as a master with manual start and manual
	 * chip select mode options
	 */
	XSpiPs_SetOptions(SpiInstancePtr, XSPIPS_MANUAL_START_OPTION |
			XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION
		   | XSPIPS_CLK_PHASE_1_OPTION);

	XSpiPs_SetClkPrescaler(SpiInstancePtr, XSPIPS_CLK_PRESCALE_256);

	return 0;
}

s32 spi_read(XSpiPs *InstancePtr, u8 *SendBufPtr, u8 *RecvBufPtr, u32 ByteCount)
{
	return XSpiPs_PolledTransfer(InstancePtr, SendBufPtr,
			RecvBufPtr, ByteCount);
}

void set_tare(XSpiPs Spi, u8* buff, int SENSOR_DATA_LEN){

	tare = 0;

	spi_read(&Spi, buff, buff, SENSOR_DATA_LEN);
	tare += buff[0] << 16  | buff[1] << 8 | buff[2];

	spi_read(&Spi, buff, buff, SENSOR_DATA_LEN);
	tare += buff[0] << 16  | buff[1] << 8 | buff[2];

	spi_read(&Spi, buff, buff, SENSOR_DATA_LEN);
	tare += buff[0] << 16  | buff[1] << 8 | buff[2];

	tare /= 3;

}

u32 get_tare(void){
	return tare;
}

u32 sensor_read(XSpiPs Spi, u8* buff, int SENSOR_DATA_LEN){
	spi_read(&Spi, buff, buff, SENSOR_DATA_LEN);
	u32 value = buff[0] << 16  | buff[1] << 8 | buff[2];
	value = abs (tare - value);
	return value;
}





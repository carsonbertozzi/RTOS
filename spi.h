/*
 * spi.h
 *
 *  Created on: Oct 25, 2018
 *      Author: Carson
 */

#ifndef SRC_SPI_H_
#define SRC_SPI_H_

#include "xparameters.h"	/* SDK generated parameters */
#include "xspips.h"		/* SPI device driver */
#include "xil_printf.h"

#define SPI_DEVICE_ID		XPAR_XSPIPS_0_DEVICE_ID


u8 spi_init(u16 SpiDeviceId, XSpiPs *SpiInstancePtr);
s32 spi_read(XSpiPs *InstancePtr, u8 *SendBufPtr, u8 *RecvBufPtr, u32 ByteCount);
void set_tare(XSpiPs Spi, u8* buff, int SENSOR_DATA_LEN);
u32 get_tare(void);
u32 sensor_read(XSpiPs Spi, u8* buff, int SENSOR_DATA_LEN);

#endif /* SRC_SPI_H_ */

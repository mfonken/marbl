/*
 * i2c_universal.c
 *
 *  Created on: Jun 20, 2016
 *      Author: mfonk
 */

#include "i2c_universal.h"
#include "LSM6_i2c.h"
#include "MPR121_i2c.h"

static I2C_TypeDef *i2c;

void initSensors(uint8_t LSM6_addr, uint8_t MPR121_addr)
{
	LSM6init(LSM6_addr);
	MPR121init(MPR121_addr);
}

I2C_TransferReturn_TypeDef I2CDRV_Transfer(I2C_TransferSeq_TypeDef *seq)
{
	I2C_TransferReturn_TypeDef ret;
	/* Do a polled transfer */
	ret = I2C_TransferInit(I2C0, seq);

	while (ret == i2cTransferInProgress)
	{
		//GPIO_PinOutSet(gpioPortD, 13);
		ret = I2C_Transfer(I2C0);
	}
	return(ret);
}

int8_t LSM6RequestFrom(uint8_t reg, uint8_t length, uint8_t *data)
{
	return I2CRequestFrom(DS33_ADDR, reg, length, data);
}

int8_t LSM6Read(uint8_t reg, uint8_t *data)
{
	return I2CRead(DS33_ADDR, reg, data);
}

int8_t LSM6Write(uint8_t reg, uint8_t *data, int16_t length)
{
	return I2CWrite(DS33_ADDR, reg, data, length);
}

int8_t MPR121RequestFrom(uint8_t reg, uint8_t length, uint8_t *data)
{
	return I2CRequestFrom(MPR121_ADDR, reg, length, data);
}

int8_t MPR121Read(uint8_t reg, uint8_t *data)
{
	return I2CRead(MPR121_ADDR, reg, data);
}

int8_t MPR121Write(uint8_t reg, uint8_t *data, int16_t length)
{
	return I2CWrite(MPR121_ADDR, reg, data, length);
}

int8_t I2CRequestFrom(uint8_t addr, uint8_t reg, uint8_t length, uint8_t *data)
{
	uint8_t *read_data;
	for(uint8_t i = 0; i < length; i++)
	{
		if(TEST_REG_ERROR == I2CRead(addr, reg + i, &(read_data[i])))
				return TEST_REG_ERROR;
	}
	data = read_data;
	return TEST_REG_SUCCESS;
}


int8_t I2CRead(uint8_t addr, uint8_t reg, uint8_t *data)
{
	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_read_data[1];

	/* Unused parameter */
	(void) i2c;

	seq.addr  = addr;
	seq.flags = I2C_FLAG_WRITE_READ;
	/* Select command to issue */
	seq.buf[0].data   = &reg;
	seq.buf[0].len    = 1;

	/* Select location/length of data to be read */
	seq.buf[1].data = i2c_read_data;
	seq.buf[1].len  = 1;

	ret = I2CDRV_Transfer(&seq);
	if (ret != i2cTransferDone)
	{
		return TEST_REG_ERROR;
	}
	else
	{
		*data = (uint32_t)i2c_read_data[0]; //((uint32_t) i2c_read_data[0] << 8) + ((uint32_t)i2c_read_data[1] & 0xfc);
		return TEST_REG_SUCCESS;
	}
}


int8_t I2CWrite(uint8_t addr, uint8_t reg, uint8_t *data, int16_t length)
{
	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;

	/* Unused parameter */
	(void) i2c;

	seq.addr  = addr;
	seq.flags = I2C_FLAG_WRITE;
	/* Select command to issue */
	for(int8_t i = length; i >= 0; i--)
	{
		data[i] = data[i-1];
	}
	data[0] = (uint8_t)reg;
	seq.buf[0].data   = data;
	seq.buf[0].len    = length + 1;

	/* Select location/length of data to be read */
	seq.buf[1].data = 0;
	seq.buf[1].len  = 0;

	ret = I2CDRV_Transfer(&seq);
	if (ret != i2cTransferDone)
	{
		return TEST_REG_ERROR;
	}
	else
	{
		return TEST_REG_SUCCESS;
	}
}

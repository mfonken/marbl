/*
 * i2c_universal.h
 *
 *  Created on: Jun 20, 2016
 *      Author: mfonk
 */



#ifndef I2C_UNIVERSAL_H_
#define I2C_UNIVERSAL_H_


#include "em_device.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include <stdbool.h>

#define DS33_ADDR  		0x6A << 1//01101010B
#define MPR121_ADDR		0x5A << 1

#define TEST_REG_ERROR 		-1
#define TEST_REG_SUCCESS 	1

void initSensors(uint8_t LSM6_addr, uint8_t MPR121_addr);

I2C_TransferReturn_TypeDef I2CDRV_Transfer(I2C_TransferSeq_TypeDef *seq);

int8_t LSM6RequestFrom(uint8_t reg, uint8_t length, uint8_t *data);
int8_t LSM6Read(uint8_t reg, uint8_t *data);
int8_t LSM6Write(uint8_t reg, uint8_t *data, int16_t length);

int8_t MPR121RequestFrom(uint8_t reg, uint8_t length, uint8_t *data);
int8_t MPR121Read(uint8_t reg, uint8_t *data);
int8_t MPR121Write(uint8_t reg, uint8_t *data, int16_t length);

int8_t I2CRequestFrom(uint8_t addr, uint8_t reg, uint8_t length, uint8_t *data);
int8_t I2CRead(uint8_t addr, uint8_t reg, uint8_t *data);
int8_t I2CWrite(uint8_t addr, uint8_t reg, uint8_t *data, int16_t length);

#endif /* I2C_UNIVERSAL_H_ */

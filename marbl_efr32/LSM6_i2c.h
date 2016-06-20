/*
 * LSM6_i2c.h
 *
 *  Created on: Jun 14, 2016
 *      Author: mfonk
 */

#ifndef LSM6_I2C_H_
#define LSM6_I2C_H_

#include "em_device.h"
#include "em_i2c.h"
#include "em_gpio.h"
#include <stdbool.h>

typedef struct
{
	int16_t x, y, z;
} vector;

enum deviceType { device_DS33, device_auto };
enum sa0State { sa0_low, sa0_high, sa0_auto };

typedef struct LSM6
{

    // register addresses
    enum regAddr
    {
      FUNC_CFG_ACCESS   = 0x01,

      FIFO_CTRL1        = 0x06,
      FIFO_CTRL2        = 0x07,
      FIFO_CTRL3        = 0x08,
      FIFO_CTRL4        = 0x09,
      FIFO_CTRL5        = 0x0A,
      ORIENT_CFG_G      = 0x0B,

      INT1_CTRL         = 0x0D,
      INT2_CTRL         = 0x0E,
      WHO_AM_I          = 0x0F,
      CTRL1_XL          = 0x10,
      CTRL2_G           = 0x11,
      CTRL3_C           = 0x12,
      CTRL4_C           = 0x13,
      CTRL5_C           = 0x14,
      CTRL6_C           = 0x15,
      CTRL7_G           = 0x16,
      CTRL8_XL          = 0x17,
      CTRL9_XL          = 0x18,
      CTRL10_C          = 0x19,

      WAKE_UP_SRC       = 0x1B,
      TAP_SRC           = 0x1C,
      D6D_SRC           = 0x1D,
      STATUS_REG        = 0x1E,

      OUT_TEMP_L        = 0x20,
      OUT_TEMP_H        = 0x21,
      OUTX_L_G          = 0x22,
      OUTX_H_G          = 0x23,
      OUTY_L_G          = 0x24,
      OUTY_H_G          = 0x25,
      OUTZ_L_G          = 0x26,
      OUTZ_H_G          = 0x27,
      OUTX_L_XL         = 0x28,
      OUTX_H_XL         = 0x29,
      OUTY_L_XL         = 0x2A,
      OUTY_H_XL         = 0x2B,
      OUTZ_L_XL         = 0x2C,
      OUTZ_H_XL         = 0x2D,

      FIFO_STATUS1      = 0x3A,
      FIFO_STATUS2      = 0x3B,
      FIFO_STATUS3      = 0x3C,
      FIFO_STATUS4      = 0x3D,
      FIFO_DATA_OUT_L   = 0x3E,
      FIFO_DATA_OUT_H   = 0x3F,
      TIMESTAMP0_REG    = 0x40,
      TIMESTAMP1_REG    = 0x41,
      TIMESTAMP2_REG    = 0x42,

      STEP_TIMESTAMP_L  = 0x49,
      STEP_TIMESTAMP_H  = 0x4A,
      STEP_COUNTER_L    = 0x4B,
      STEP_COUNTER_H    = 0x4C,

      FUNC_SRC          = 0x53,

      TAP_CFG           = 0x58,
      TAP_THS_6D        = 0x59,
      INT_DUR2          = 0x5A,
      WAKE_UP_THS       = 0x5B,
      WAKE_UP_DUR       = 0x5C,
      FREE_FALL         = 0x5D,
      MD1_CFG           = 0x5E,
      MD2_CFG           = 0x5F,
    };



};
    void LSM6(void);

    bool LSM6init();

    void LSM6enableDefault(void);

    void LSM6enable();
    void LSM6disable();

    void LSM6writeReg(uint8_t reg, uint8_t value);
    uint8_t LSM6readReg(uint8_t reg);

    void LSM6readAcc(void);
    void LSM6readGyro(void);
    void LSM6readAll(void);

    void setTimeout(uint16_t timeout);
    uint16_t getTimeout(void);
    bool timeoutOccurred(void);

    // vector functions
    static void LSM6vector_normalize(vector *a);

    int16_t testReg(uint8_t address, enum regAddr reg);

    double dot_product(vector *u, vector *v);
    vector * cross_product(vector *u, vector *v);
    //int16_t LSM6testReg(enum regAddr reg);
    int8_t LSM6RequestFrom(enum regAddr reg, uint8_t length, uint8_t *data);
    int8_t LSM6Read(uint8_t reg, uint8_t *data);
    int8_t LSM6Write(enum regAddr reg, uint8_t *data, int16_t length);
    I2C_TransferReturn_TypeDef I2CDRV_Transfer(I2C_TransferSeq_TypeDef *seq);

#endif /* LSM6_I2C_H_ */

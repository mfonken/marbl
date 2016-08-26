/*
 * LSM5_i2c.c
 *
 *  Created on: Jun 14, 2016
 *      Author: mfonk
 */

#include "LSM6_i2c.h"
#include "i2c_universal.h"
#include <math.h>

// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes




#define DS33_WHO_ID    	0x69 << 8

#define LSM6_PORT 		gpioPortB
#define LSM6_PIN		13

static vector a; // accelerometer readings
static vector g; // gyro readings

static uint8_t last_status; // status of last I2C transmission

static enum deviceType _device; // chip type
static uint8_t _address;

static uint16_t io_timeout;
static bool did_timeout;

// Public Methods //////////////////////////////////////////////////////////////

bool LSM6init(uint8_t addr)
{
	LSM6enable();
	_address = addr;
	io_timeout = 0;  // 0 = no timeout
	did_timeout = false;
	uint8_t *data = 0;
	if(LSM6Read(WHO_AM_I, data) == DS33_WHO_ID)
	{
		return false;
	}
	LSM6enableDefault();
	return true;
}

// Did a timeout occur in readAcc(), readGyro(), or read() since the last call to timeoutOccurred()?
bool LSM6timeoutOccurred()
{
	bool tmp = did_timeout;
	did_timeout = false;
	return tmp;
}

void LSM6enable()
{
	GPIO_PinOutSet(LSM6_PORT, LSM6_PIN);
}

void LSM6disable()
{
	GPIO_PinOutClear(LSM6_PORT, LSM6_PIN);
}

void LSM6setTimeout(uint16_t timeout)
{
	io_timeout = timeout;
}

uint16_t LSM6getTimeout()
{
	return io_timeout;
}

/*
Enables the LSM6's accelerometer and gyro. Also:
- Sets sensor full scales (gain) to default power-on values, which are
  +/- 2 g for accelerometer and 245 dps for gyro
- Selects 1.66 kHz (high performance) ODR (output data rate) for accelerometer
  and 1.66 kHz (high performance) ODR for gyro. (These are the ODR settings for
  which the electrical characteristics are specified in the datasheet.)
- Enables automatic increment of register address during multiple byte access
Note that this function will also reset other settings controlled by
the registers it writes to.
 */
void LSM6enableDefault(void)
{
	if (_device == device_DS33)
	{
		// Accelerometer

		// 0x80 = 0b10000000
		// ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (+/-2 g full scale)
		uint8_t data = 0x40;
		LSM6Write(CTRL1_XL, &data, 1);

		// Gyro

		// 0x80 = 0b010000000
		// ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (245 dps)
		data = 0x40;
		LSM6Write(CTRL2_G, &data, 1);
		// Common

		// 0x04 = 0b00000100
		// IF_INC = 1 (automatically increment register address)
		data = 0x04;
		LSM6Write(CTRL3_C, &data, 1);
	}
}

// Reads the 3 accelerometer channels and stores them in vector a
void LSM6readAcc(void)
{
	//	Wire.beginTransmission(address);
	//	// automatic increment of register address is enabled by default (IF_INC in CTRL3_C)
	//	Wire.write(OUTX_L_XL);
	//	Wire.endTransmission();
	//	Wire.requestFrom(address, (uint8_t)6);
	//
	//	uint16_t millis_start = millis();
	//	while (Wire.available() < 6) {
	//		if (io_timeout > 0 && ((uint16_t)millis() - millis_start) > io_timeout)
	//		{
	//			did_timeout = true;
	//			return;
	//		}
	//	}
	//
	//	uint8_t xla = Wire.read();
	//	uint8_t xha = Wire.read();
	//	uint8_t yla = Wire.read();
	//	uint8_t yha = Wire.read();
	//	uint8_t zla = Wire.read();
	//	uint8_t zha = Wire.read();

	// combine high and low bytes
	//	a.x = (int16_t)(xha << 8 | xla);
	//	a.y = (int16_t)(yha << 8 | yla);
	//	a.z = (int16_t)(zha << 8 | zla);
}

// Reads the 3 gyro channels and stores them in vector g
void LSM6readGyro(void)
{
	uint8_t data[6];
	//uint8_t data = 0;
	LSM6Read(OUTZ_L_XL, data);
	//LSM6RequestFrom(OUTX_L_G, 6, data);
	//	Wire.beginTransmission(address);
	//	// automatic increment of register address is enabled by default (IF_INC in CTRL3_C)
	//	Wire.write(OUTX_L_G);
	//	Wire.endTransmission();
	//	Wire.requestFrom(address, (uint8_t)6);
	//
	//	uint16_t millis_start = millis();
	//	while (Wire.available() < 6) {
	//		if (io_timeout > 0 && ((uint16_t)millis() - millis_start) > io_timeout)
	//		{
	//			did_timeout = true;
	//			return;
	//		}
	//	}

	//	uint8_t xlg = Wire.read();
	//	uint8_t xhg = Wire.read();
	//	uint8_t ylg = Wire.read();
	//	uint8_t yhg = Wire.read();
	//	uint8_t zlg = Wire.read();
	//	uint8_t zhg = Wire.read();

	// combine high and low bytes
	//	g.x = (int16_t)(xhg << 8 | xlg);
	//	g.y = (int16_t)(yhg << 8 | ylg);
	//	g.z = (int16_t)(zhg << 8 | zlg);
}


void LSM6vector_normalize(vector *a)
{
	float mag = sqrt(dot_product(a, a));
	a->x /= mag;
	a->y /= mag;
	a->z /= mag;
}

// Private Methods //////////////////////////////////////////////////////////////

double dot_product(vector *u, vector *v)
{
	return (u->x * v->x) + (u->y * v->y) + (u->z * v->z);
}

vector * cross_product(vector *u, vector *v)
{
	vector r;
	r.x = (u->y * v->z) - (u->z * v->y);
	r.y = (u->z * v->x) - (u->x * v->z);
	r.z = (u->x * v->y) - (u->y * v->x);
	return &r;
}


void LSM6readAll(void)
{
	LSM6readAcc();
	LSM6readGyro();
}






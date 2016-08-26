/*
 * MPR121_i2c.h
 *
 *  Created on: Jun 20, 2016
 *      Author: mfonk
 */

#ifndef MPR121_I2C_H_
#define MPR121_I2C_H_


#include "MPR121_defs.h"
#include "stdbool.h"
#include "stdint.h"


#define DEFAULT_TTHRESH		40
#define DEFAULT_RTHRESH		20
#define DEFAULT_INTERRUPT	4 	// note that this is not a hardware interrupt, just the digital
				// pin that the MPR121 ~INT pin is connected to
#define DEFAULT_MHDR		0x01
#define DEFAULT_NHDR		0x01
#define DEFAULT_NCLR		0x10
#define DEFAULT_FDLR		0x20
#define DEFAULT_MHDF		0x01
#define DEFAULT_NHDF		0x01
#define DEFAULT_NCLF		0x10
#define DEFAULT_FDLF		0x20
#define DEFAULT_NHDT		0x01
#define DEFAULT_NCLT		0x10
#define DEFAULT_FDLT		0xFF
#define DEFAULT_MHDPROXR	0x0F
#define DEFAULT_NHDPROXR	0x0F
#define DEFAULT_NCLPROXR	0x00
#define DEFAULT_FDLPROXR	0x00
#define DEFAULT_MHDPROXF	0x01
#define DEFAULT_NHDPROXF	0x01
#define DEFAULT_NCLPROXF	0xFF
#define DEFAULT_FDLPROXF	0xFF
#define DEFAULT_NHDPROXT	0x00
#define DEFAULT_NCLPROXT	0x00
#define DEFAULT_FDLPROXT	0x00
#define DEFAULT_DTR			0x11
#define DEFAULT_AFE1		0xFF
#define DEFAULT_AFE2		0x30
#define DEFAULT_ECR			0xCC // default to fast baseline startup and 12 electrodes enabled, no prox
#define DEFAULT_ACCR0		0x00
#define DEFAULT_ACCR1		0x00
#define DEFAULT_USL			0x00
#define DEFAULT_LSL			0x00
#define DEFAULT_TL			0x00

// idea behind this is to create a settings structure that we can use to store
// all the setup variables for a particular setup - comes pre-instantiated with
// defaults and can be easily tweaked - we pass by reference (as a pointer) to
// save RAM

struct MPR121_settings_t
{
	// touch and release thresholds
	uint8_t TTHRESH;
	uint8_t RTHRESH;

	uint8_t INTERRUPT;

	// general electrode touch sense baseline filters
	// rising filter
	uint8_t MHDR;
	uint8_t NHDR;
	uint8_t NCLR;
	uint8_t FDLR;

	// falling filter
	uint8_t MHDF;
	uint8_t NHDF;
	uint8_t NCLF;
	uint8_t FDLF;

	// touched filter
	uint8_t NHDT;
	uint8_t NCLT;
	uint8_t FDLT;

	// proximity electrode touch sense baseline filters
	// rising filter
	uint8_t MHDPROXR;
	uint8_t NHDPROXR;
	uint8_t NCLPROXR;
	uint8_t FDLPROXR;

	// falling filter
	uint8_t MHDPROXF;
	uint8_t NHDPROXF;
	uint8_t NCLPROXF;
	uint8_t FDLPROXF;

	// touched filter
	uint8_t NHDPROXT;
	uint8_t NCLPROXT;
	uint8_t FDLPROXT;

	// debounce settings
	uint8_t DTR;

	// configuration registers
	uint8_t AFE1;
	uint8_t AFE2;
	uint8_t ECR;

	// auto-configuration registers
	uint8_t ACCR0;
	uint8_t ACCR1;
	uint8_t USL;
	uint8_t LSL;
	uint8_t TL;

};

// GPIO pin function constants
enum mpr121_pinf_t
{
	// INPUT and OUTPUT are already defined by Arduino, use its definitions

	//INPUT,		// digital input
	INPUT_PU,		// digital input with pullup
	INPUT_PD,		// digital input with pulldown
	//OUTPUT,		// digital output (push-pull)
	OUTPUT_HS,		// digital output, open collector (high side)
	OUTPUT_LS		// digital output, open collector (low side)
};

// "13th electrode" proximity modes
// N.B. this does not relate to normal proximity detection
// see http://cache.freescale.com/files/sensors/doc/app_note/AN3893.pdf
enum mpr121_proxmode_t
{
	DISABLED,		// proximity mode disabled
	PROX0_1,		// proximity mode for ELE0..ELE1
	PROX0_3,		// proximity mode for ELE0..ELE3
	PROX0_11		// proximity mode for ELE0..ELE11
};

// error codes
enum mpr121_error_t
{
	NO_ERROR,			// no error
	RETURN_TO_SENDER,	// not implemented
	ADDRESS_UNKNOWN,	// no MPR121 found at specified I2C address
	READBACK_FAIL,		// readback from MPR121 was not as expected
	OVERCURRENT_FLAG,	// overcurrent on REXT pin
	OUT_OF_RANGE,		// autoconfiguration fail, often a result of shorted pins
	NOT_INITED			// device has not been initialised
};


// -------------------- BASIC FUNCTIONS --------------------

// begin() must be called before using any other function
// address is optional, default is 0x5C
bool MPR121init();

// I2C speed control functions - goFast() sets the SCL clock
// to 400kHz - goSlow() sets the SCL clock to 100kHz. Defaults
// to 100kHz and affects all devices on the I2C bus. Included
// for speed freaks only.
void goSlow();
void goFast();

// getError() returns an mpr121_error_t indicating the current
// error on the MPR121 - clearError() clears this
enum mpr121_error_t MPR121getError();
void clearError();

// returns status of the MPR121 INT pin as read via digitalRead() on the
// Arduino board - this tells us if there has been a change in touch status
// on any active electrode since we last read any data
bool MPR121touchStatusChanged();

// updates the data from the MPR121 into our internal buffer
// updateTouchData() does this only for touch on / off status
// updateBaseLineData() does this for background baseline
// updateFilteredData() does this for continuous proximity data
// updateAll() does all three

// the appropriate function from these must be called before data
// from getTouchData(), getFilteredData() etc. can be considered
// valid
void updateTouchData();
bool updateBaselineData();
bool updateFilteredData();
void updateAll();

// returns a boolean indicating the touch status of a given electrode
bool getTouchData(uint8_t electrode);

// returns the number of touches currently detected
uint8_t getNumTouches();

// returns continous proximity or baseline data for a given electrode
int getFilteredData(uint8_t electrode);
int getBaselineData(uint8_t electrode);

// returns boolean indicating whether a new touch or release has been
// detected since the last time updateTouchData() was called
bool isNewTouch(uint8_t electrode);
bool isNewRelease(uint8_t electrode);

// sets touch and release thresholds either for all electrodes, or
// for a specfic electrode - higher values = less sensitive and
// release threshold must ALWAYS be lower than touch threshold
void MPR121setTouchThresholdAll(uint8_t val);
void MPR121setTouchThreshold(uint8_t electrode, uint8_t val);
void MPR121setReleaseThresholdAll(uint8_t val);
void MPR121setReleaseThreshold(uint8_t electrode, uint8_t val);

// returns the current touch or release threshold for a specified electrode
uint8_t MPR121getTouchThreshold(uint8_t electrode);
uint8_t MPR121getReleaseThreshold(uint8_t electrode);

// ------------------ ADVANCED FUNCTIONS ------------------

// applies a complete array of settings from an
// MPR121_settings_t variable passed as a pointer
// useful if you want to do a bulk setup of the device
void MPR121applySettings(struct MPR121_settings_t *settings);

// setRegister() and getRegister() manipulate registers on
// the MPR121 directly, whilst correctly stopping and
// restarting the MPR121 if necessary
void MPR121setRegister(uint8_t reg, uint8_t value);
uint8_t MPR121getRegister(uint8_t reg);

// stop() and run() take the MPR121 in and out of stop mode
// which reduces current consumption to 3uA
void MPR121run();
void MPR121stop();

// resets the MPR121
bool MPR121reset();

// tells us if we are in run mode, and if we have inited the
// MPR121
bool MPR121isRunning();
bool MPR121isInited();

// sets the pin that the MPR121 INT output is connected to on the
// Arduino board - does not have to be a hardware interrupt pin
// if it is, however, an interrupt service routine will automatically
// set an internal flag when a touch event occurs - thus minimising
// lost events if you are also reading other data types (filtered data,
// baseline data)
void MPR121setInterruptPin(uint8_t pin);

// set number of electrodes to use to generate virtual "13th"
// proximity electrode
// see http://cache.freescale.com/files/sensors/doc/app_note/AN3893.pdf
//
// N.B. - this is not related to general proximity detection or
// reading back continuous proximity data
void MPR121setProxMode(enum mpr121_proxmode_t mode);

// Enables GPIO mode for up to 8 of the MPR121 electrodes
// starts with electrode 11 - i.e. setNumDigPins(1) sets just
// electrode 11 as GPIO, setNumDigPins(2) sets electrodes 11
// & 10 as GPIO, and so on. Electrodes 0 to 3 cannot be used
// as GPIO
//
// N.B. electrodes are 3.3V and WILL be damaged if driven by
// a greater voltage
void setNumDigPins(uint8_t numPins);

// Sets pin mode for an electrode already set as GPIO by
// setNumDigPins() - see section "GPIO pin function constants"
// for details
void pinMode(uint8_t electrode, enum mpr121_pinf_t mode);
void pinMode(uint8_t electrode, int mode);

// Similar to digitalWrite in Arduino for GPIO electrode
void MPR121digitalWrite(uint8_t electrode, uint8_t val);

// Toggles electrode set as GPIO output
void MPR121digitalToggle(uint8_t electrode);

// Reads electrode set as GPIO input
bool MPR121digitalRead(uint8_t electrode);

// Writes PWM value to electrode set as GPIO output - very limited
// (4 bit, although input to function is 0..255 to match Arduino,
// internally reduced to 4 bit) and broken on ELE9 and ELE10
// see https://community.freescale.com/thread/305474
void MPR121analogWrite(uint8_t electrode, uint8_t val);

// functions / variables internal to the MPR121_t class - you cannot access these externally

bool MPR121getLastTouchData(uint8_t electrode);	// we use this to catch touch / release events that happen
// during other update calls

#endif /* MPR121_I2C_H_ */

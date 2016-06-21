/*
 * MPR121_i2c.c
 *
 *  Created on: Jun 20, 2016
 *      Author: mfonk
 */


#include "MPR121_i2c.h"
#include "i2c_universal.h"

#define NOT_INITED_BIT 			0
#define ADDRESS_UNKNOWN_BIT 	1
#define READBACK_FAIL_BIT 		2
#define OVERCURRENT_FLAG_BIT 	3
#define OUT_OF_RANGE_BIT 		4

//private:
// internal helper functions and variables
// not exposed externally to the user
uint8_t address;
struct MPR121_settings_t defaultSettings;
uint8_t ECR_backup = 0x00; // so we can re-enable the correct number of electrodes
// when recovering from stop mode
uint8_t error = 1<<NOT_INITED_BIT;;
bool running = false;
int interruptPin;

int filteredData[13];
int baselineData[13];
uint16_t touchData = 0;
uint16_t lastTouchData = 0;

bool autoTouchStatusFlag = false;

bool MPR121init(){
	error &= ~(1<<NOT_INITED_BIT); // clear NOT_INITED error flag

	if(MPR121reset()){
		// default values...
		MPR121applySettings(&defaultSettings);
		MPR121getRegister(ECR);
		return true;
	} else {
		return false;
	}

}

void MPR121setRegister(uint8_t reg, uint8_t value){

	bool wasRunning = false;

	if(reg==ECR){	// if we are modding ECR, update our internal running status
		if(value&0x3F){
			running = true;
		} else {
			running = false;
		}
	} else if(reg<CTL0){
		wasRunning = running;
		if(wasRunning) MPR121stop(); 	// we should ALWAYS be in stop mode for this
								// unless modding ECR or GPIO / LED register
	}
	MPR121Write(reg, &value, 1);
//    Wire.beginTransmission(address);
//    Wire.write(reg);
//    Wire.write(value);
//    if(Wire.endTransmission()!=0){
//    	error |= 1<<ADDRESS_UNKNOWN_BIT; // set address unknown bit
//    } else {
//    	error &= ~(1<<ADDRESS_UNKNOWN_BIT);
//    }
//
//    if(wasRunning) run();		// restore run mode if necessary
}

uint8_t MPR121getRegister(uint8_t reg){
	uint8_t value;
	MPR121Read(reg, &value);
//    Wire.beginTransmission(address);
//    Wire.write(reg); // set address to read from our requested register
//    Wire.endTransmission(false); // repeated start
//    Wire.requestFrom(address,(uint8_t)1);  // just a single byte
//    if(Wire.endTransmission()!=0){
//    	error |= 1<<ADDRESS_UNKNOWN_BIT;
//    } else {
//    	error &= ~(1<<ADDRESS_UNKNOWN_BIT);
//    }
    //scratch = Wire.read();
    // auto update errors for registers with error data
    if(reg == TS2 && ( ( value&0x80 ) != 0)){
    	error |= 1<<OVERCURRENT_FLAG_BIT;
    } else {
    	error &= ~(1<<OVERCURRENT_FLAG_BIT);
    }
    if((reg == OORS1 || reg == OORS2) && (value != 0)){
    	error |= 1<<OUT_OF_RANGE_BIT;
    } else {
    	error &= ~(1<<OUT_OF_RANGE_BIT);
    }
    return value;
}


void MPR121run(){
	if(!MPR121isInited()) return;
	MPR121setRegister(ECR, ECR_backup); // restore backup to return to run mode
}

void MPR121stop(){
	if(!MPR121isInited()) return;
	ECR_backup = MPR121getRegister(ECR);	// backup ECR to restore when we enter run
	MPR121setRegister(ECR, ECR_backup & 0xC0); // turn off all electrodes to stop
}

bool MPR121reset(){
	// return true if we successfully reset a device at the
	// address we are expecting

	// AFE2 is one of the few registers that defaults to a non-zero value -
	// checking it is sensible as reading back an incorrect value implies
	// something went wrong - we also check TS2 bit 7 to see if we have an
	// overcurrent flag set

	MPR121setRegister(SRST, 0x63); // soft reset

	if(MPR121getRegister(AFE2)!=0x24){
		error |= 1<<READBACK_FAIL_BIT;
	} else {
		error &= ~(1<<READBACK_FAIL_BIT);
	}

	if((MPR121getRegister(TS2)&0x80)!=0){
		error |= 1<<OVERCURRENT_FLAG_BIT;
	} else {
		error &= ~(1<<OVERCURRENT_FLAG_BIT);
	}

	if(MPR121getError() == NOT_INITED || MPR121getError() == NO_ERROR){ // if our only error is that we are not inited...
		return true;
	} else {
		return false;
	}
}

void MPR121applySettings(struct MPR121_settings_t *settings)
{
	bool wasRunning = running;
	if(wasRunning) MPR121stop();  // can't change most regs when running - checking
							// here avoids multiple stop() / run() calls
	MPR121setRegister(MHDR,DEFAULT_MHDR);
	MPR121setRegister(NHDR,DEFAULT_NHDR);
	MPR121setRegister(NCLR,DEFAULT_NCLR);
	MPR121setRegister(FDLR,DEFAULT_FDLR);
	MPR121setRegister(MHDF,DEFAULT_MHDF);
	MPR121setRegister(NHDF,DEFAULT_NHDF);
	MPR121setRegister(NCLF,DEFAULT_NCLF);
	MPR121setRegister(FDLF,DEFAULT_FDLF);
	MPR121setRegister(NHDT,DEFAULT_NHDT);
	MPR121setRegister(NCLT,DEFAULT_NCLT);
	MPR121setRegister(FDLT,DEFAULT_FDLT);
	MPR121setRegister(MHDPROXR,DEFAULT_MHDPROXR);
	MPR121setRegister(NHDPROXR,DEFAULT_NHDPROXR);
	MPR121setRegister(NCLPROXR,DEFAULT_NCLPROXR);
	MPR121setRegister(FDLPROXR,DEFAULT_FDLPROXR);
	MPR121setRegister(MHDPROXF,DEFAULT_MHDPROXF);
	MPR121setRegister(NHDPROXF,DEFAULT_NHDPROXF);
	MPR121setRegister(NCLPROXF,DEFAULT_NCLPROXF);
	MPR121setRegister(FDLPROXF,DEFAULT_FDLPROXF);
	MPR121setRegister(NHDPROXT,DEFAULT_NHDPROXT);
	MPR121setRegister(NCLPROXT,DEFAULT_NCLPROXT);
	MPR121setRegister(FDLPROXT,DEFAULT_FDLPROXT);
	MPR121setRegister(DTR, DEFAULT_DTR);
  	MPR121setRegister(AFE1, DEFAULT_AFE1);
	MPR121setRegister(AFE2, DEFAULT_AFE2);
	MPR121setRegister(ACCR0, DEFAULT_ACCR0);
	MPR121setRegister(ACCR1, DEFAULT_ACCR1);
	MPR121setRegister(USL, DEFAULT_USL);
	MPR121setRegister(LSL, DEFAULT_LSL);
	MPR121setRegister(TL, DEFAULT_TL);

	MPR121setRegister(ECR, DEFAULT_ECR);

	error &= ~(1<<NOT_INITED_BIT); // clear not inited error as we have just inited!
	MPR121setTouchThresholdAll(DEFAULT_TTHRESH);
	MPR121setReleaseThresholdAll(DEFAULT_RTHRESH);
	//MPR121setInterruptPin(DEFAULT_INTERRUPT);

	if(wasRunning) MPR121run();
}

enum mpr121_error_t MPR121getError(){

	// important - this resets the IRQ pin - as does any I2C comms

	MPR121getRegister(OORS1);	// OOR registers - we may not have read them yet,
	MPR121getRegister(OORS2);	// whereas the other errors should have been caught

	// order of error precedence is determined in this logic block

	if(!MPR121isInited()) return NOT_INITED; // this has its own checker function

	if((error & (1<<ADDRESS_UNKNOWN_BIT)) != 0){
		return ADDRESS_UNKNOWN;
	} else if((error & (1<<READBACK_FAIL_BIT)) != 0){
		return READBACK_FAIL;
	} else if((error & (1<<OVERCURRENT_FLAG_BIT)) != 0){
		return OVERCURRENT_FLAG;
	} else if((error & (1<<OUT_OF_RANGE_BIT)) != 0){
		return OUT_OF_RANGE;
	} else return NO_ERROR;

}
//
//void MPR121clearError(){
//	error = 0;
//}
//
//bool MPR121isRunning(){
//	return running;
//}
//
bool MPR121isInited(){
	return (error & (1<<NOT_INITED_BIT)) == 0;
}

void MPR121updateTouchData(){
	if(!MPR121isInited()) return;

	autoTouchStatusFlag = false;

	lastTouchData = touchData;
	touchData = (unsigned int)MPR121getRegister(TS1) + ((unsigned int)MPR121getRegister(TS2)<<8);
}

bool MPR121getTouchData(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return false; // avoid out of bounds behaviour

	return((touchData>>electrode)&1);
}

uint8_t MPR121getNumTouches(){
	if(!MPR121isInited()) return(0xFF);

	uint8_t scratch = 0;
	for(uint8_t i=0; i<13; i++){
		if(MPR121getTouchData(i)) scratch++;
	}

	return(scratch);
}

bool MPR121getLastTouchData(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return false; // avoid out of bounds behaviour

	return((lastTouchData>>electrode)&1);
}

bool MPR121updateFilteredData(){
	if(!MPR121isInited()) return(false);
	uint8_t data[13];

//  if(touchStatusChanged()) {
//		autoTouchStatusFlag = true;
//	}


	uint8_t LSB, MSB;

	MPR121RequestFrom(E0BV, 26, data);
//  if(touchStatusChanged()) {
//		autoTouchStatusFlag = true;
//	}

		for(int i=0; i<13; i++){ // 13 filtered values
//			if(touchStatusChanged()) {
//				autoTouchStatusFlag = true;
//			}
		  LSB = data[i*2];
//		  if(touchStatusChanged()) {
//				autoTouchStatusFlag = true;
//			}
		  MSB = data[i*2+1];
		  filteredData[i] = ((MSB << 8) | LSB);
		}
		return(true);
}

int MPR121getFilteredData(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return(0xFFFF); // avoid out of bounds behaviour

	return(filteredData[electrode]);
}

bool MPR121updateBaselineData(){
	if(!MPR121isInited()) return(false);
	uint8_t data[13];

//  if(touchStatusChanged()) {
//		autoTouchStatusFlag = true;
//	}
	MPR121RequestFrom(E0BV, 13, data);
		for(int i=0; i<13; i++){ // 13 filtered values
//	    if(touchStatusChanged()) {
//				autoTouchStatusFlag = true;
//			}

		  baselineData[i] = data[i];
		}
		return(true);
//	  } else {
//	  	// if we don't get back all 26 values we requested, don't update the BVAL values
//	  	// and return false
//		return(false);
//  }
}

int MPR121getBaselineData(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return(0xFFFF); // avoid out of bounds behaviour

	return(baselineData[electrode]);
}

bool MPR121isNewTouch(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return(false); // avoid out of bounds behaviour
	return((MPR121getLastTouchData(electrode) == false) && (MPR121getTouchData(electrode) == true));
}

bool MPR121isNewRelease(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return(false); // avoid out of bounds behaviour
	return((MPR121getLastTouchData(electrode) == true) && (MPR121getTouchData(electrode) == false));
}

void MPR121updateAll(){
	MPR121updateTouchData();
	MPR121updateBaselineData();
	MPR121updateFilteredData();
}

void MPR121setTouchThresholdAll(uint8_t val){
	if(!MPR121isInited()) return;
	bool wasRunning = running;

	if(wasRunning) MPR121stop();	// can only change thresholds when not running
							// checking here avoids multiple stop() / run()
							// calls

	for(uint8_t i=0; i<13; i++){
		MPR121setTouchThreshold(i, val);
	}

	if(wasRunning) MPR121run();
}

void MPR121setTouchThreshold(uint8_t electrode, uint8_t val){
	if(electrode>12 || !MPR121isInited()) return; // avoid out of bounds behaviour

	// this relies on the internal register map of the MPR121
	MPR121setRegister(E0TTH + (electrode<<1), val);
}

void MPR121setReleaseThresholdAll(uint8_t val){
	if(!MPR121isInited()) return;
	bool wasRunning = running;

	if(wasRunning) MPR121stop();	// can only change thresholds when not running
							// checking here avoids multiple stop / starts

	for(uint8_t i=0; i<13; i++){
		MPR121setReleaseThreshold(i,val);
	}

	if(wasRunning) MPR121run();
}

void MPR121setReleaseThreshold(uint8_t electrode, uint8_t val){
	if(electrode>12 || !MPR121isInited()) return; // avoid out of bounds behaviour

	// this relies on the internal register map of the MPR121
	MPR121setRegister(E0RTH + (electrode<<1), val);
}

uint8_t MPR121getTouchThreshold(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return(0xFF); // avoid out of bounds behaviour
	return(MPR121getRegister(E0TTH+(electrode<<1))); // "255" issue is in here somewhere
	//return(101);
}
uint8_t MPR121getReleaseThreshold(uint8_t electrode){
	if(electrode>12 || !MPR121isInited()) return(0xFF); // avoid out of bounds behaviour
	return(MPR121getRegister(E0RTH+(electrode<<1))); // "255" issue is in here somewhere
	//return(51);
}

//void MPR121setInterruptPin(uint8_t pin){
//	// :: here forces the compiler to use Arduino's pinMode, not MPR121's
//	if(!isInited()) return;
//	::pinMode(pin, INPUT_PULLUP);
//	interruptPin = pin;
//}
//
//bool MPR121touchStatusChanged(){
//	// :: here forces the compiler to use Arduino's digitalRead, not MPR121's
//	return(autoTouchStatusFlag || (!::digitalRead(interruptPin)));
//}
//
//void MPR121setProxMode(mpr121_proxmode_t mode){
//
//	if(!isInited()) return;
//
//	bool wasRunning = running;
//
//	if(wasRunning) stop();
//
//	switch(mode){
//		case DISABLED:
//			ECR_backup &= ~(3<<4);	// ELEPROX[0:1] = 00
//			break;
//		case PROX0_1:
//			ECR_backup |=  (1<<4);	// ELEPROX[0:1] = 01
//			ECR_backup &= ~(1<<5);
//			break;
//		case PROX0_3:
//			ECR_backup &= ~(1<<4);	// ELEPROX[0:1] = 10
//			ECR_backup |=  (1<<5);
//			break;
//		case PROX0_11:
//			ECR_backup |=  (3<<4);	// ELEPROX[0:1] = 11
//			break;
//	}
//
//	if(wasRunning) run();
//}
//
//void MPR121setNumDigPins(uint8_t numPins){
//	if(!isInited()) return;
//	bool wasRunning = running;
//
//	if(numPins>8) numPins = 8; // maximum number of GPIO pins is 8 out of 12
//
//	if(wasRunning){
//		stop(); // have to stop to change ECR
//	}
//	ECR_backup = (0x0F&(12-numPins)) | (ECR_backup&0xF0);
//	if(wasRunning){
//		run();
//	}
//
//}

void MPR121pinMode(uint8_t electrode, enum mpr121_pinf_t mode){

	// only valid for ELE4..ELE11
	if(electrode<4 || electrode >11 || !MPR121isInited()) return;

	// LED0..LED7
	uint8_t bitmask = 1<<(electrode-4);

	switch(mode){
		case INPUT_PU:
			// EN = 1
			// DIR = 0
			// CTL0 = 1
			// CTL1 = 1
			MPR121setRegister(EN, MPR121getRegister(EN) | bitmask);
			MPR121setRegister(DIR, MPR121getRegister(DIR) & ~bitmask);
			MPR121setRegister(CTL0, MPR121getRegister(CTL0) | bitmask);
			MPR121setRegister(CTL1, MPR121getRegister(CTL1) | bitmask);
			break;
		case INPUT_PD:
			// EN = 1
			// DIR = 0
			// CTL0 = 1
			// CTL1 = 0
			MPR121setRegister(EN, MPR121getRegister(EN) | bitmask);
			MPR121setRegister(DIR, MPR121getRegister(DIR) & ~bitmask);
			MPR121setRegister(CTL0, MPR121getRegister(CTL0) | bitmask);
			MPR121setRegister(CTL1, MPR121getRegister(CTL1) & ~bitmask);
			break;
		case OUTPUT_HS:
			// EN = 1
			// DIR = 1
			// CTL0 = 1
			// CTL1 = 1
			MPR121setRegister(EN, MPR121getRegister(EN) | bitmask);
			MPR121setRegister(DIR, MPR121getRegister(DIR) | bitmask);
			MPR121setRegister(CTL0, MPR121getRegister(CTL0) | bitmask);
			MPR121setRegister(CTL1, MPR121getRegister(CTL1) | bitmask);
			break;
		case OUTPUT_LS:
			// EN = 1
			// DIR = 1
			// CTL0 = 1
			// CTL1 = 0
			MPR121setRegister(EN, MPR121getRegister(EN) | bitmask);
			MPR121setRegister(DIR, MPR121getRegister(DIR) | bitmask);
			MPR121setRegister(CTL0, MPR121getRegister(CTL0) | bitmask);
			MPR121setRegister(CTL1, MPR121getRegister(CTL1) & ~bitmask);
			break;
	}
}
//
//void MPR121pinMode(uint8_t electrode, int mode){
//	if(!isInited()) return;
//
//	// this is to catch the fact that Arduino prefers its definition of INPUT
//	// and OUTPUT to ours...
//
//	uint8_t bitmask = 1<<(electrode-4);
//
//	if(mode == OUTPUT){
//		// EN = 1
//		// DIR = 1
//		// CTL0 = 0
//		// CTL1 = 0
//		setRegister(EN, getRegister(EN) | bitmask);
//		setRegister(DIR, getRegister(DIR) | bitmask);
//		setRegister(CTL0, getRegister(CTL0) & ~bitmask);
//		setRegister(CTL1, getRegister(CTL1) & ~bitmask);
//
//	} else if(mode == INPUT){
//		// EN = 1
//		// DIR = 0
//		// CTL0 = 0
//		// CTL1 = 0
//		setRegister(EN, getRegister(EN) | bitmask);
//		setRegister(DIR, getRegister(DIR) & ~bitmask);
//		setRegister(CTL0, getRegister(CTL0) & ~bitmask);
//		setRegister(CTL1, getRegister(CTL1) & ~bitmask);
//	} else {
//		return; // anything that isn't a 1 or 0 is invalid
//	}
//}
//
//void MPR121digitalWrite(uint8_t electrode, uint8_t val){
//
//	// avoid out of bounds behaviour
//
//	if(electrode<4 || electrode>11 || !isInited()) return;
//
//	if(val){
//		setRegister(SET, 1<<(electrode-4));
//	} else {
//		setRegister(CLR, 1<<(electrode-4));
//	}
//}
//
//void MPR121_t::digitalToggle(uint8_t electrode){
//
//	// avoid out of bounds behaviour
//
//	if(electrode<4 || electrode>11 || !isInited()) return;
//
//	setRegister(TOG, 1<<(electrode-4));
//}
//
//bool MPR121digitalRead(uint8_t electrode){
//
//	// avoid out of bounds behaviour
//
//	if(electrode<4 || electrode>11 || !isInited()) return false;
//
//	return(((getRegister(DAT)>>(electrode-4))&1)==1);
//}
//
//void MPR121analogWrite(uint8_t electrode, uint8_t value){
//	// LED output 5 (ELE9) and output 6 (ELE10) have a PWM bug
//	// https://community.freescale.com/thread/305474
//
//	// avoid out of bounds behaviour
//
//	if(electrode<4 || electrode>11 || !isInited()) return;
//
//	uint8_t shiftedVal = value>>4;
//
//	if(shiftedVal > 0){
//		setRegister(SET, 1<<(electrode-4)); // normal PWM operation
//	} else {
//		// this make a 0 PWM setting turn off the output
//		setRegister(CLR, 1<<(electrode-4));
//	}
//
//	uint8_t scratch;
//
//	switch(electrode-4){
//
//	case 0:
//	  scratch = getRegister(PWM0);
//	  setRegister(PWM0, (shiftedVal & 0x0F) | (scratch & 0xF0));
//	  break;
//	case 1:
//	  scratch = getRegister(PWM0);
//	  setRegister(PWM0, ((shiftedVal & 0x0F)<<4) | (scratch & 0x0F));
//	  break;
//	case 2:
//	  scratch = getRegister(PWM1);
//	  setRegister(PWM1, (shiftedVal & 0x0F) | (scratch & 0xF0));
//	  break;
//	case 3:
//	  scratch = getRegister(PWM1);
//	  setRegister(PWM1, ((shiftedVal & 0x0F)<<4) | (scratch & 0x0F));
//	  break;
//	case 4:
//	  scratch = getRegister(PWM2);
//	  setRegister(PWM2, (shiftedVal & 0x0F) | (scratch & 0xF0));
//	  break;
//	case 5:
//	  scratch = getRegister(PWM2);
//	  setRegister(PWM2, ((shiftedVal & 0x0F)<<4) | (scratch & 0x0F));
//	  break;
//	case 6:
//	  scratch = getRegister(PWM3);
//	  setRegister(PWM3, (shiftedVal & 0x0F) | (scratch & 0xF0));
//	  break;
//	case 7:
//	  scratch = getRegister(PWM3);
//	  setRegister(PWM3, ((shiftedVal & 0x0F)<<4) | (scratch & 0x0F));
//	  break;
//	}
//
//
//}

//MPR121_t MPR121 = MPR121_t();

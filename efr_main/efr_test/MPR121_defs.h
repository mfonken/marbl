/*
 * MPR121_defs.h
 *
 *  Created on: Jun 20, 2016
 *      Author: mfonk
 */

#ifndef MPR121_DEFS_H_
#define MPR121_DEFS_H_

#include "stdint.h"

// MPR121 Register Defines

// touch and OOR statuses
static uint8_t TS1 = 0x00;
static uint8_t TS2 = 0x01;
static uint8_t OORS1 = 0x02;
static uint8_t OORS2 = 0x03;

// filtered data
static uint8_t E0FDL = 0x04;
static uint8_t E0FDH = 0x05;
static uint8_t E1FDL = 0x06;
static uint8_t E1FDH = 0x07;
static uint8_t E2FDL = 0x08;
static uint8_t E2FDH = 0x09;
static uint8_t E3FDL = 0x0A;
static uint8_t E3FDH = 0x0B;
static uint8_t E4FDL = 0x0C;
static uint8_t E4FDH = 0x0D;
static uint8_t E5FDL = 0x0E;
static uint8_t E5FDH = 0x0F;
static uint8_t E6FDL = 0x10;
static uint8_t E6FDH = 0x11;
static uint8_t E7FDL = 0x12;
static uint8_t E7FDH = 0x13;
static uint8_t E8FDL = 0x14;
static uint8_t E8FDH = 0x15;
static uint8_t E9FDL = 0x16;
static uint8_t E9FDH = 0x17;
static uint8_t E10FDL = 0x18;
static uint8_t E10FDH = 0x19;
static uint8_t E11FDL = 0x1A;
static uint8_t E11FDH = 0x1B;
static uint8_t E12FDL = 0x1C;
static uint8_t E12FDH = 0x1D;

// baseline values
static uint8_t E0BV = 0x1E;
static uint8_t E1BV = 0x1F;
static uint8_t E2BV = 0x20;
static uint8_t E3BV = 0x21;
static uint8_t E4BV = 0x22;
static uint8_t E5BV = 0x23;
static uint8_t E6BV = 0x24;
static uint8_t E7BV = 0x25;
static uint8_t E8BV = 0x26;
static uint8_t E9BV = 0x27;
static uint8_t E10BV = 0x28;
static uint8_t E11BV = 0x29;
static uint8_t E12BV = 0x2A;

// general electrode touch sense baseline filters
// rising filter
static uint8_t MHDR = 0x2B;
static uint8_t NHDR = 0x2C;
static uint8_t NCLR = 0x2D;
static uint8_t FDLR = 0x2E;

// falling filter
static uint8_t MHDF = 0x2F;
static uint8_t NHDF = 0x30;
static uint8_t NCLF = 0x31;
static uint8_t FDLF = 0x32;

// touched filter
static uint8_t NHDT = 0x33;
static uint8_t NCLT = 0x34;
static uint8_t FDLT = 0x35;

// proximity electrode touch sense baseline filters
// rising filter
static uint8_t MHDPROXR = 0x36;
static uint8_t NHDPROXR = 0x37;
static uint8_t NCLPROXR = 0x38;
static uint8_t FDLPROXR = 0x39;

// falling filter
static uint8_t MHDPROXF = 0x3A;
static uint8_t NHDPROXF = 0x3B;
static uint8_t NCLPROXF = 0x3C;
static uint8_t FDLPROXF = 0x3D;

// touched filter
static uint8_t NHDPROXT = 0x3E;
static uint8_t NCLPROXT = 0x3F;
static uint8_t FDLPROXT = 0x40;

// electrode touch and release thresholds
static uint8_t E0TTH = 0x41;
static uint8_t E0RTH = 0x42;
static uint8_t E1TTH = 0x43;
static uint8_t E1RTH = 0x44;
static uint8_t E2TTH = 0x45;
static uint8_t E2RTH = 0x46;
static uint8_t E3TTH = 0x47;
static uint8_t E3RTH = 0x48;
static uint8_t E4TTH = 0x49;
static uint8_t E4RTH = 0x4A;
static uint8_t E5TTH = 0x4B;
static uint8_t E5RTH = 0x4C;
static uint8_t E6TTH = 0x4D;
static uint8_t E6RTH = 0x4E;
static uint8_t E7TTH = 0x4F;
static uint8_t E7RTH = 0x50;
static uint8_t E8TTH = 0x51;
static uint8_t E8RTH = 0x52;
static uint8_t E9TTH = 0x53;
static uint8_t E9RTH = 0x54;
static uint8_t E10TTH = 0x55;
static uint8_t E10RTH = 0x56;
static uint8_t E11TTH = 0x57;
static uint8_t E11RTH = 0x58;
static uint8_t E12TTH = 0x59;
static uint8_t E12RTH = 0x5A;

// debounce settings
static uint8_t DTR = 0x5B;

// configuration registers
static uint8_t AFE1 = 0x5C;
static uint8_t AFE2 = 0x5D;
static uint8_t ECR = 0x5E;

// electrode currents
static uint8_t CDC0 = 0x5F;
static uint8_t CDC1 = 0x60;
static uint8_t CDC2 = 0x61;
static uint8_t CDC3 = 0x62;
static uint8_t CDC4 = 0x63;
static uint8_t CDC5 = 0x64;
static uint8_t CDC6 = 0x65;
static uint8_t CDC7 = 0x66;
static uint8_t CDC8 = 0x67;
static uint8_t CDC9 = 0x68;
static uint8_t CDC10 = 0x69;
static uint8_t CDC11 = 0x6A;
static uint8_t CDC12 = 0x6B;

// electrode charge times
static uint8_t CDT01 = 0x6C;
static uint8_t CDT23 = 0x6D;
static uint8_t CDT45 = 0x6E;
static uint8_t CDT67 = 0x6F;
static uint8_t CDT89 = 0x70;
static uint8_t CDT1011 = 0x71;
static uint8_t CDT11 = 0x72;

// GPIO
static uint8_t CTL0 = 0x73;
static uint8_t CTL1 = 0x74;
static uint8_t DAT = 0x75;
static uint8_t DIR = 0x76;
static uint8_t EN = 0x77;
static uint8_t SET = 0x78;
static uint8_t CLR = 0x79;
static uint8_t TOG = 0x7A;

// auto-config
static uint8_t ACCR0 = 0x7B;
static uint8_t ACCR1 = 0x7C;
static uint8_t USL = 0x7D;
static uint8_t LSL = 0x7E;
static uint8_t TL = 0x7F;

// soft reset
static uint8_t SRST = 0x80;

// PWM
static uint8_t PWM0 = 0x81;
static uint8_t PWM1 = 0x82;
static uint8_t PWM2 = 0x83;
static uint8_t PWM3 = 0x84;

#endif /* MPR121_DEFS_H_ */

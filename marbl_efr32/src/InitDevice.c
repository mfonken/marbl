//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library includes]
#include "em_system.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpcrc.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_ldma.h"
#include "em_prs.h"
#include "em_rtcc.h"
// [Library includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	CHIP_Init();

	EMU_enter_DefaultMode_from_RESET();
	LFXO_enter_DefaultMode_from_RESET();
	CMU_enter_DefaultMode_from_RESET();
	RTCC_enter_DefaultMode_from_RESET();
	I2C0_enter_DefaultMode_from_RESET();
	GPCRC_enter_DefaultMode_from_RESET();
	LDMA_enter_DefaultMode_from_RESET();
	PRS_enter_DefaultMode_from_RESET();
	PORTIO_enter_DefaultMode_from_RESET();
	// [Config Calls]$

}

//================================================================================
// EMU_enter_DefaultMode_from_RESET
//================================================================================
extern void EMU_enter_DefaultMode_from_RESET(void) {

	// $[EMU Initialization]
	/* Initialize DCDC regulator */
	EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;

	dcdcInit.powerConfig = emuPowerConfig_DcdcToDvdd;
	dcdcInit.dcdcMode = emuDcdcMode_LowNoise;
	dcdcInit.mVout = 1800;
	dcdcInit.em01LoadCurrent_mA = 15;
	dcdcInit.em234LoadCurrent_uA = 10;
	dcdcInit.maxCurrent_mA = 200;
	dcdcInit.anaPeripheralPower = emuDcdcAnaPeripheralPower_DCDC;
	dcdcInit.reverseCurrentControl = 160;

	EMU_DCDCInit(&dcdcInit);
	// [EMU Initialization]$

}

//================================================================================
// LFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void LFXO_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// CMU_enter_DefaultMode_from_RESET
//================================================================================
extern void CMU_enter_DefaultMode_from_RESET(void) {

	// $[High Frequency Clock Setup]
	/* Initializing HFXO */
	CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

	hfxoInit.autoStartEm01 = 1;

	CMU_HFXOInit(&hfxoInit);

	/* Skipping HFXO oscillator enable, as it is auto-enabled on EM0/EM1 entry */

	/* Setting system HFXO frequency */
	SystemHFXOClockSet(38400000);

	/* Using HFXO as high frequency clock, HFCLK */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

	/* HFRCO not needed when using HFXO */
	CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);
	// [High Frequency Clock Setup]$

	// $[LE clocks enable]
	/* Enable clock to LE modules */
	CMU_ClockEnable(cmuClock_CORELE, true);
	/* Initializing LFXO */
	CMU_LFXOInit_TypeDef lfxoInit = CMU_LFXOINIT_DEFAULT;

	CMU_LFXOInit(&lfxoInit);

	/* Enable LFXO oscillator, and wait for it to be stable */
	CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

	/* Setting system LFXO frequency */
	SystemLFXOClockSet(32768);

	// [LE clocks enable]$

	// $[LFACLK Setup]
	// [LFACLK Setup]$

	// $[LFBCLK Setup]
	// [LFBCLK Setup]$

	// $[LFECLK Setup]
	/* Select LFXO as clock source for LFECLK */
	CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFXO);
	// [LFECLK Setup]$

	// $[Peripheral Clock enables]
	/* Enable clock for HF peripherals */
	CMU_ClockEnable(cmuClock_HFPER, true);

	/* Enable clock for GPCRC */
	CMU_ClockEnable(cmuClock_GPCRC, true);

	/* Enable clock for I2C0 */
	CMU_ClockEnable(cmuClock_I2C0, true);

	/* Enable clock for LDMA */
	CMU_ClockEnable(cmuClock_LDMA, true);

	/* Enable clock for PRS */
	CMU_ClockEnable(cmuClock_PRS, true);

	/* Enable clock for RTCC */
	CMU_ClockEnable(cmuClock_RTCC, true);

	/* Enable clock for GPIO by default */
	CMU_ClockEnable(cmuClock_GPIO, true);

	// [Peripheral Clock enables]$

	// $[Clock output]
	/* Disable CLKOUT0 output */
	CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_CLKOUTSEL0_MASK)
			| CMU_CTRL_CLKOUTSEL0_DISABLED;
	/* Disable CLKOUT1 output */
	CMU->CTRL = (CMU->CTRL & ~_CMU_CTRL_CLKOUTSEL1_MASK)
			| CMU_CTRL_CLKOUTSEL1_DISABLED;

	// [Clock output]$

	// $[CMU_IO]
	/* Disable CLKOUT0 pin */
	CMU->ROUTEPEN &= ~CMU_ROUTEPEN_CLKOUT0PEN;

	/* Disable CLKOUT1 pin */
	CMU->ROUTEPEN &= ~CMU_ROUTEPEN_CLKOUT1PEN;

	// [CMU_IO]$

}

//================================================================================
// ADC0_enter_DefaultMode_from_RESET
//================================================================================
extern void ADC0_enter_DefaultMode_from_RESET(void) {

	// $[ADC0_Init]
	// [ADC0_Init]$

	// $[ADC0_InputConfiguration]
	// [ADC0_InputConfiguration]$

}

//================================================================================
// ACMP0_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP0_enter_DefaultMode_from_RESET(void) {

	// $[ACMP0_Init]
	// [ACMP0_Init]$

	// $[ACMP0_IO]
	// [ACMP0_IO]$

}

//================================================================================
// ACMP1_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP1_enter_DefaultMode_from_RESET(void) {

	// $[ACMP1_Init]
	// [ACMP1_Init]$

	// $[ACMP1_IO]
	// [ACMP1_IO]$

}

//================================================================================
// IDAC0_enter_DefaultMode_from_RESET
//================================================================================
extern void IDAC0_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// RTCC_enter_DefaultMode_from_RESET
//================================================================================
extern void RTCC_enter_DefaultMode_from_RESET(void) {

	// $[Compare/Capture Channel 0 init]
	// [Compare/Capture Channel 0 init]$

	// $[Compare/Capture Channel 1 init]
	// [Compare/Capture Channel 1 init]$

	// $[Compare/Capture Channel 2 init]
	// [Compare/Capture Channel 2 init]$

	// $[RTCC init]
	RTCC_Init_TypeDef rtccInit = RTCC_INIT_DEFAULT;

	rtccInit.enable = true;
	rtccInit.debugRun = false;
	rtccInit.precntWrapOnCCV0 = false;
	rtccInit.cntWrapOnCCV1 = false;
	rtccInit.prescMode = rtccCntTickPresc;
	rtccInit.presc = rtccCntPresc_32;
	rtccInit.enaOSCFailDetect = false;
	rtccInit.cntMode = rtccCntModeNormal;

	RTCC_Init(&rtccInit);
	// [RTCC init]$

}

//================================================================================
// USART0_enter_DefaultMode_from_RESET
//================================================================================
extern void USART0_enter_DefaultMode_from_RESET(void) {

	// $[USART_InitAsync]
	// [USART_InitAsync]$

	// $[USART_InitSync]
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	// [USART_InitPrsTrigger]$

	// $[USART_InitIO]
	// [USART_InitIO]$

	// $[USART_Misc]
	// [USART_Misc]$

	// $[USART_Enable]
	// [USART_Enable]$

}

//================================================================================
// USART1_enter_DefaultMode_from_RESET
//================================================================================
extern void USART1_enter_DefaultMode_from_RESET(void) {

	// $[USART_InitAsync]
	// [USART_InitAsync]$

	// $[USART_InitSync]
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	// [USART_InitPrsTrigger]$

	// $[USART_InitIO]
	// [USART_InitIO]$

	// $[USART_Misc]
	// [USART_Misc]$

	// $[USART_Enable]
	// [USART_Enable]$

}

//================================================================================
// LEUART0_enter_DefaultMode_from_RESET
//================================================================================
extern void LEUART0_enter_DefaultMode_from_RESET(void) {

	// $[LEUART0 initialization]
	// [LEUART0 initialization]$

}

//================================================================================
// WDOG0_enter_DefaultMode_from_RESET
//================================================================================
extern void WDOG0_enter_DefaultMode_from_RESET(void) {

	// $[WDOG Initialization]
	// [WDOG Initialization]$

}

//================================================================================
// I2C0_enter_DefaultMode_from_RESET
//================================================================================
extern void I2C0_enter_DefaultMode_from_RESET(void) {

	// $[I2C0 I/O setup]
	/* Set up SCL */
	I2C0->ROUTEPEN = I2C0->ROUTEPEN | I2C_ROUTEPEN_SCLPEN;
	I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SCLLOC_MASK))
			| I2C_ROUTELOC0_SCLLOC_LOC15;
	/* Set up SDA */
	I2C0->ROUTEPEN = I2C0->ROUTEPEN | I2C_ROUTEPEN_SDAPEN;
	I2C0->ROUTELOC0 = (I2C0->ROUTELOC0 & (~_I2C_ROUTELOC0_SDALOC_MASK))
			| I2C_ROUTELOC0_SDALOC_LOC15;
	// [I2C0 I/O setup]$

	// $[I2C0 initialization]
	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	init.enable = 1;
	init.master = 1;
	init.freq = I2C_FREQ_STANDARD_MAX;
	init.clhr = i2cClockHLRStandard;
	I2C_Init(I2C0, &init);
	// [I2C0 initialization]$

}

//================================================================================
// GPCRC_enter_DefaultMode_from_RESET
//================================================================================
extern void GPCRC_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// LDMA_enter_DefaultMode_from_RESET
//================================================================================
extern void LDMA_enter_DefaultMode_from_RESET(void) {

}

//================================================================================
// TIMER0_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER0_enter_DefaultMode_from_RESET(void) {

	// $[TIMER0 I/O setup]
	// [TIMER0 I/O setup]$

	// $[TIMER0 initialization]
	// [TIMER0 initialization]$

	// $[TIMER0 CC0 init]
	// [TIMER0 CC0 init]$

	// $[TIMER0 CC1 init]
	// [TIMER0 CC1 init]$

	// $[TIMER0 CC2 init]
	// [TIMER0 CC2 init]$

	// $[TIMER0 DTI init]
	// [TIMER0 DTI init]$

}

//================================================================================
// TIMER1_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER1_enter_DefaultMode_from_RESET(void) {

	// $[TIMER1 I/O setup]
	// [TIMER1 I/O setup]$

	// $[TIMER1 initialization]
	// [TIMER1 initialization]$

	// $[TIMER1 CC0 init]
	// [TIMER1 CC0 init]$

	// $[TIMER1 CC1 init]
	// [TIMER1 CC1 init]$

	// $[TIMER1 CC2 init]
	// [TIMER1 CC2 init]$

	// $[TIMER1 CC3 init]
	// [TIMER1 CC3 init]$

}

//================================================================================
// LETIMER0_enter_DefaultMode_from_RESET
//================================================================================
extern void LETIMER0_enter_DefaultMode_from_RESET(void) {

	// $[LETIMER0 Compare Values]
	// [LETIMER0 Compare Values]$

	// $[LETIMER0 Repeat Values]
	// [LETIMER0 Repeat Values]$

	// $[LETIMER0 Initialization]
	// [LETIMER0 Initialization]$

	// $[LETIMER0 PRS Input Triggers]
	// [LETIMER0 PRS Input Triggers]$

	// $[LETIMER0 I/O setup]
	// [LETIMER0 I/O setup]$

}

//================================================================================
// CRYOTIMER_enter_DefaultMode_from_RESET
//================================================================================
extern void CRYOTIMER_enter_DefaultMode_from_RESET(void) {

	// $[CRYOTIMER_Init]
	// [CRYOTIMER_Init]$

}

//================================================================================
// PCNT0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCNT0_enter_DefaultMode_from_RESET(void) {

	// $[PCNT0 I/O setup]
	// [PCNT0 I/O setup]$

	// $[PCNT0 initialization]
	// [PCNT0 initialization]$

}

//================================================================================
// PRS_enter_DefaultMode_from_RESET
//================================================================================
extern void PRS_enter_DefaultMode_from_RESET(void) {

	// $[PRS initialization]
	/* Set up DMA triggers */
	PRS->DMAREQ0 |= PRS_DMAREQ0_PRSSEL_PRSCH0;
	PRS->DMAREQ1 |= PRS_DMAREQ1_PRSSEL_PRSCH0;
	// [PRS initialization]$

}

//================================================================================
// PORTIO_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTIO_enter_DefaultMode_from_RESET(void) {

	// $[Port A Configuration]
	// [Port A Configuration]$

	// $[Port B Configuration]
	// [Port B Configuration]$

	// $[Port C Configuration]

	/* Pin PC10 is configured to Open-drain with pull-up and filter */
	GPIO_PinModeSet(gpioPortC, 10, gpioModeWiredAndPullUpFilter, 0);

	/* Pin PC11 is configured to Open-drain with pull-up and filter */
	GPIO_PinModeSet(gpioPortC, 11, gpioModeWiredAndPullUpFilter, 0);
	// [Port C Configuration]$

	// $[Port D Configuration]

	/* Pin PD13 is configured to Push-pull */
	GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 0);

	/* Pin PD14 is configured to Push-pull */
	GPIO_PinModeSet(gpioPortD, 14, gpioModePushPull, 0);
	// [Port D Configuration]$

	// $[Port E Configuration]
	// [Port E Configuration]$

	// $[Port F Configuration]
	// [Port F Configuration]$

}


/***********************************************************************************************//**
 * \file   app_hw/app_hw.c
 * \brief  Hardware specific application code
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/
#include "boards.h" //todo move his to config header

#include CONFIGURATION_HEADER

/* BG stack headers */
#include "bg_types.h"

#ifndef HOST

/* STK header files. */
#include "bspconfig.h"
#include "bsp.h"

/* Temp sensor and I2c*/
#include "i2cspmconfig.h"
#include "i2cspm.h"
#include "si7013.h"
#include "tempsens.h"
#include "i2c_universal.h"

#endif /* !HOST */

#include "app_ui.h"
#include "app_cfg.h"

/* Own headers*/
#include "app_hw.h"

/***********************************************************************************************//**
 * @addtogroup app_hardware
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app_hw
 * @{
 **************************************************************************************************/


/***************************************************************************************************
  Local Macros and Definitions
 ***************************
 **************************************************************************************************/

#ifndef HOST
/* Text definitions*/
#define APP_HW_SENSOR_FAIL_TEXT         "Failed to detect\nsi7021 sensor."

/***************************************************************************************************
 Local Variables
 **************************************************************************************************/

/** Status flag of the Temperature Sensor. */
static bool si7013_status = false;
#endif /* !HOST */

/* Heart Rate Sensor */
static uint16_t appHwEnergyExpended;

/* CSC Sensor */
static uint32_t appHwCscWheelCount;

/* Max Rate Sensor */

/***************************************************************************************************
 Static Function Declarations
 **************************************************************************************************/

static void appBtnCback(AppUiBtnEvt_t btn);
/***************************************************************************************************
 Public Function Definitions
 **************************************************************************************************/

void appHwInit(void)
{
	//appUiBlinkLed();
	initSensors(DS33_ADDR, MPR121_ADDR);

	//ITM_SendChar('H');
  //LSM6readGyro();

}

/***************************************************************************************************
 HTM sensor
 **************************************************************************************************/

int32_t appHwReadTm(int32_t* tempData)
{
#ifdef HOST
  static uint16 dummyTemp = 0;
  dummyTemp +=1000;
  *tempData = dummyTemp;
  return 0;
#else /* !HOST */
  uint32_t rhData = 0;
  /* Read temperature sensor over I2C */
  return Si7013_MeasureRHAndTemp(I2C0, SI7021_ADDR, &rhData, tempData);
#endif /* HOST */
}

bool appHwInitTempSens(void)
{
#ifdef HOST
  return 0;
#else /* !HOST */

  /* Get initial sensor status over I2C */
  si7013_status = Si7013_Detect(I2C0, SI7021_ADDR, NULL);
  return si7013_status;
#endif /* HOST */
}


/***************************************************************************************************
 HR sensor - dummy functions for demonstation purposes
 **************************************************************************************************/

uint16_t appHwReadHr(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

uint16_t appHwReadEnergyExpended(void)
{
  return appHwEnergyExpended++;
}

void appHwClearEnergyExpended(void)
{
  appHwEnergyExpended = 0;
}

void appHwReadRRInterval(uint8_t *length, uint16_t *buf)
{
  uint8_t i;
  static uint16_t appHwDummy;
  appHwDummy++;
  if (appHwDummy > 7) {
    appHwDummy = 0;
  }
  for (i = 0; i < appHwDummy; i++) {
    *(buf++) = i;
  }
  *length = appHwDummy;

}

/***************************************************************************************************
 Battery sensor - dummy functions for demonstation purposes
 **************************************************************************************************/

uint8_t appHwReadBatteryLevel(void)
{
  static uint16_t appHwDummy;
  appHwDummy++;

  if (100 < appHwDummy) {
    appHwDummy = 0;
  }

  return appHwDummy;
}

uint16_t appHwReadBatteryLevelMilliVolts(void)
{
  static uint16_t appHwDummy;

  return appHwDummy++;
}

/***************************************************************************************************
 Cycling Power sensor and Cycling Cadence and Speed sensor - dummy functions for demonstation
 purposes
 **************************************************************************************************/

int16_t appHwReadActPower(void)
{
  static int16_t appHwDummy;
  return ++appHwDummy;
}

uint8_t appHwReadPedalBalance(void)
{
  static int16_t appHwDummy;

  if (100 < appHwDummy) {
    appHwDummy = 0;
  }

  return ++appHwDummy;
}

uint16_t appHwReadTotalTorque(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

uint32_t appHwReadWheelRevCount(void)
{
  /* Wheel revolution data not allowed to roll over */
  if (appHwCscWheelCount < UINT32_MAX) {
    return appHwCscWheelCount++;
  }
  else {
    return appHwCscWheelCount;
  }
}

void appHwSetRevCount(uint32_t appHwNewCumulValue)
{
	appHwCscWheelCount = appHwNewCumulValue;
}

uint16_t appHwReadLastWheelTime(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

uint16_t appHwReadTotalCrankRevs(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

uint16_t appHwReadLastCrankRevTime(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

int16_t appHwReadMaxForce(void)
{
  static int16_t appHwDummy;
  return ++appHwDummy;
}

int16_t appHwReadMinForce(void)
{
  static int16_t appHwDummy;
  return ++appHwDummy;
}

int16_t appHwReadMaxTorque(void)
{
  static int16_t appHwDummy;
  return ++appHwDummy;
}

int16_t appHwReadMinTorque(void)
{
  static int16_t appHwDummy;
  return ++appHwDummy;
}

uint16_t appHwReadMaxAngle(void)
{
  static uint16_t appHwDummy;
   appHwDummy++;
   if ( 4096 >= appHwDummy) {
     appHwDummy = 0;
   }

   return appHwDummy;
}

uint16_t appHwReadMinAngle(void)
{
  static uint16_t appHwDummy;
   appHwDummy++;
   if ( 4096 >= appHwDummy) {
     appHwDummy = 0;
   }

   return appHwDummy;
}

uint16_t appHwReadTopDeadSpotAngle(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

uint16_t appHwReadBottomDeadSpotAngle(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

uint16_t appHwReadAccumulatedEnergy(void)
{
  static uint16_t appHwDummy;
  return ++appHwDummy;
}

uint16_t appHwReadFirstCrankMeasAngle(void)
{
  static uint16_t appHwDummy;
  ++appHwDummy;
  if (360 < appHwDummy) {
    appHwDummy = 0;
  }
  return appHwDummy;
}

void appHwReadInstantForceArray(uint8_t *length, uint16_t *buf)
{
  uint8_t i;
  static uint16_t appHwDummy;
  appHwDummy++;
  if (appHwDummy > 6) {
    appHwDummy = 0;
  }
  for (i = 0; i < appHwDummy; i++) {
    *(buf++) = i;
  }
  *length = appHwDummy;
}
void appHwReadInstantTorqueArray(uint8_t *length, uint16_t *buf)
{
  uint8_t i;
  static uint16_t appHwDummy;
  appHwDummy++;
  if (appHwDummy > 5) {
    appHwDummy = 0;
  }
  for (i = 0; i < appHwDummy; i++) {
    *(buf++) = i;
  }
  *length = appHwDummy;
}

uint8_t appHwGetSamplingRate(void)
{
  return 1;
}

/***************************************************************************************************
 Static Function Definitions
 **************************************************************************************************/

/***********************************************************************************************//**
 *  \brief  Button press callback.
 *  \param[in]  btn  Button press length and button number
 **************************************************************************************************/
static void appBtnCback(AppUiBtnEvt_t btn)
{
  for (int i = 0; i < appCfgButtonEventSize; i++) {
    if ( (appCfgButtonEvent[i].buttonEventId == btn) && (appCfgButtonEvent[i].fctn) ) {
      appCfgButtonEvent[i].fctn();
    }
  }
}


/** @} (end addtogroup app_hw) */
/** @} (end addtogroup app_hardware) */


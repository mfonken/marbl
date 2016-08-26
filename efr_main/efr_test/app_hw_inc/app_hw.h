/***********************************************************************************************//**
 * \file   app_hw/app_hw.h
 * \brief  Hardware specific application header file
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

#ifndef APP_HW_H
#define APP_HW_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/***********************************************************************************************//**
 * \defgroup app_hardware Application HW
 * \brief Application HW.
 **************************************************************************************************/

/***********************************************************************************************//**
 * \defgroup app_hw Application Hardware Abstraction
 * \brief Application Hardware Abstraction Layer.
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app_hardware
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app_hw
 * @{
 **************************************************************************************************/


/***************************************************************************************************
  Data Types
***************************************************************************************************/

/***************************************************************************************************
  Function Declarations
***************************************************************************************************/

/***********************************************************************************************//**
 *  \brief  Initialize buttons and Temperature sensor.
 **************************************************************************************************/
void appHwInit(void);

/***************************************************************************************************
   Temperature Sensor
 **************************************************************************************************/

/***********************************************************************************************//**
 *  \brief  Perform a temperature measurement.  Return the measurement data.
 *  \param[out]  tempData  Result of temperature conversion.
 *  \return  0 if Temp Read successful, otherwise -1
 **************************************************************************************************/
int32_t appHwReadTm(int32_t* tempData);

/***********************************************************************************************//**
 *  \brief  Initialise temperature measurement.
 *  \return  true if a Si7013 is detected, false otherwise
 **************************************************************************************************/
bool appHwInitTempSens(void);

/***************************************************************************************************
 Heart Rate Sensor
 **************************************************************************************************/

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Energy Expanded measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Heart Rate measurement.
 *  \return  The number of times it has been called.
 **************************************************************************************************/
uint16_t appHwReadEnergyExpended(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Heart Rate measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Heart Rate measurement.
 *  \return  The number of times it has been called.
 **************************************************************************************************/
uint16_t appHwReadHr(void);

/***********************************************************************************************//**
 *  \brief  Clear Energy Expended.
 **************************************************************************************************/
void appHwClearEnergyExpended(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of RR Interval Read.
 *  Returns a buffer with always increasing number of elements (max is 8), each element having the
 *  value of the element index.
 *  This behaviour must be overwritten with the actual RR_Interval measurement.
 *  \param[in]  buf  buffer containing RR Interval values.
 *  \param[in]  length number of R-R Interval measurements in the buffer.
 *   The length of the RR-Interval field depends upon the transmission interval and the Heart Rate
 *   Value. The higher the Heart Rate value, the larger the number of RR-Interval events per second
 *   and the larger the number of RR-Interval sub-fields in the characteristic. For example, if the
 *   Heart Rate Measurement Value format of UINT8 is used with a 23-octet ATT_MTU, the maximum
 *   number of RR-Interval Values that can be notified if Energy Expended is present is 8 and the
 *   maximum number.
 **************************************************************************************************/
void appHwReadRRInterval(uint8_t *length, uint16_t *buf);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Battery Level measurement.
 *  Returns a value with always increasing number (max is 100),
 *  This behaviour must be overwritten with the actual Battery Level measurement.
 *  \return  Battery Level [%].
 **************************************************************************************************/
uint8_t appHwReadBatteryLevel(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Battery Level measurement.
 *  Returns a value with always increasing number,
 *  This behaviour must be overwritten with the actual Battery Level measurement.
 *  \return  Battery Level [mV].
 **************************************************************************************************/
uint16_t appHwReadBatteryLevelMilliVolts(void);

/***************************************************************************************************
 Cycling Power sensor
 **************************************************************************************************/

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Actual Power measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Instantaneous Power.  Unit is in watts with a resolution of 1.
 **************************************************************************************************/
int16_t appHwReadActPower(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Pedal Power Balance measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Pedal Power Balance.
 *  Unit is in percentage with a resolution of 1/2.
 **************************************************************************************************/
uint8_t appHwReadPedalBalance(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Accumulated Torque measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Accumulated Torque .
 *   Unit is in newton metres with a resolution of 1/32.
 **************************************************************************************************/
uint16_t appHwReadTotalTorque(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Wheel Revolution measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Wheel Revolution Data - Cumulative Wheel Revolutions .
 **************************************************************************************************/
uint32_t appHwReadWheelRevCount(void);

/***********************************************************************************************//**
 *  \brief  Set Cumulative Value for wheel revolution data.
 *  \param[in]  appHwNewCumulValue  New cumulative value.
 **************************************************************************************************/
void appHwSetRevCount(uint32_t appHwNewCumulValue);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Wheel Revolution measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Wheel Revolution Data - Last Wheel Event Time.
 *   Unit is in seconds with a resolution of 1/2048.
 **************************************************************************************************/
uint16_t appHwReadLastWheelTime(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Crank Revolution measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Crank Revolution Data- Cumulative Crank Revolutions .
 **************************************************************************************************/
uint16_t appHwReadTotalCrankRevs(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Crank Revolution measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Crank Revolution Data- Last Crank Event Time
 *  Unit is in seconds with a resolution of 1/1024.
 **************************************************************************************************/
uint16_t appHwReadLastCrankRevTime(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Force measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Extreme Force Magnitudes - Maximum Force Magnitude.
 *  Unit is in newtons with a resolution of 1.
 **************************************************************************************************/
int16_t appHwReadMaxForce(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Force measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Extreme Force Magnitudes - Minimum Force Magnitude .
 *   Unit is in newtons with a resolution of 1.
 **************************************************************************************************/
int16_t appHwReadMinForce(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Extreme Torque measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Extreme Torque Magnitudes- Maximum Torque Magnitude.
 *   Unit is in newton metres with a resolution of 1/32.
 **************************************************************************************************/
int16_t appHwReadMaxTorque(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Extreme Torque measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Extreme Torque Magnitudes- Minimum Torque Magnitude.
 *   Unit is in newton metres with a resolution of 1/32.
 **************************************************************************************************/
int16_t appHwReadMinTorque(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Angle measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Extreme Angles - Maximum Angle.
 *    Unit is in degrees with a resolution of 1.
 **************************************************************************************************/
uint16_t appHwReadMaxAngle(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Angle measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Extreme Angles - Minimum Angle.
 *   Unit is in degrees with a resolution of 1.
 **************************************************************************************************/
uint16_t appHwReadMinAngle(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Top Dead Spot Angle measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Top Dead Spot Angle.  Unit is in degrees with a resolution of 1.
 **************************************************************************************************/
uint16_t appHwReadTopDeadSpotAngle(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Bottom  Dead Spot Angle measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Bottom Dead Spot Angle.  Unit is in degrees with a resolution of 1.
 **************************************************************************************************/
uint16_t appHwReadBottomDeadSpotAngle(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Accumulated Energy measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Accumulated Energy.  Unit is in kilojoules with a resolution of 1.
 **************************************************************************************************/
uint16_t appHwReadAccumulatedEnergy(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Accumulated Energy measurement.
 *  Returns a value with always increasing number (max is 65535),
 *  This behaviour must be overwritten with the actual Cyclic Power measurement.
 *  \return  Accumulated Energy.  Unit is in kilojoules with a resolution of 1.
 **************************************************************************************************/
uint16_t appHwReadFirstCrankMeasAngle(void);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Instantaneous Force Magnitude Array measurement.
 *  Returns a buffer with always increasing number of elements (max is 6), each element having the
 *  value of the element index.
 *  The unit is in newtons with a resolution of 1
 *  Array Order - Older is towards the LSO and Newer is towards the MSO
 *  \param  length  Number of bytes to read from buffer.
 *  \param  buf  Pointer to buffer to read.
 **************************************************************************************************/
void appHwReadInstantForceArray(uint8_t *length, uint16_t *buf);

/***********************************************************************************************//**
 *  \brief  Dummy implementation of Instantaneous Torque Magnitude Array measurement.
 *  Returns a buffer with always increasing number of elements (max is 6), each element having the
 *  value of the element index.
 *  Unit is in newton/meter with a resolution of 1/32
 *  Array Order - Older is towards the LSO and Newer is towards the MSO
 *  \param  length  Number of bytes to read from buffer.
 *  \param  buf  Pointer to buffer to read.
 **************************************************************************************************/
void appHwReadInstantTorqueArray(uint8_t *length, uint16_t *buf);

/***********************************************************************************************//**
 *  \brief  Request sampling rate. this dummy implementation always returns 1.
 *  \return  Sampling Rate.  Unit is in Hertz.
 **************************************************************************************************/
uint8_t appHwGetSamplingRate(void);


/** @} (end addtogroup app_hw) */
/** @} (end addtogroup app_hardware) */

#ifdef __cplusplus
};
#endif

#endif /* APP_HW_H */

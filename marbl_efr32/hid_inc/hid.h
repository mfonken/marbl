/***********************************************************************************************//**
 * \file   hid.h
 * \brief  Human Interface Device Service
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

#ifndef HID_H
#define HID_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************//**
 * \defgroup hid Human Interface Device
 * \brief Human Interface Device Service API
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup Features
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup hid
 * @{
 **************************************************************************************************/


/***************************************************************************************************
  Type Definitions
***************************************************************************************************/

/***************************************************************************************************
  Function Declarations
***************************************************************************************************/

/***********************************************************************************************//**
 *  \brief  Initialise HID.
 *  \details  HID plugin initialisation.
 **************************************************************************************************/
void hidInit(void);

/***********************************************************************************************//**
*  \brief Human Interface Device Client Characteristic Config change for Boot Keyboard input report.
*  \param[in]  connection  Connection ID.
*  \param[in]  clientConfig  New value of CCCD.
***************************************************************************************************/
void hidBootKeyInCharStatusChange(uint8_t connection, uint16_t clientConfig);

/***********************************************************************************************//**
*  \brief  Human Interface Device Client Characteristic Config change for Keyboard input report.
*  \param[in]  connection  Connection ID.
*  \param[in]  clientConfig  New value of CCCD.
***************************************************************************************************/
void hidKeyInCharStatusChange(uint8_t connection, uint16_t clientConfig);

/***********************************************************************************************//**
*  \brief  Write operation was performed on HID protocol mode.
*  \param[in]  writeValue  New value of attribute.
***************************************************************************************************/
void hidProtocolModeWrite(uint8array *writeValue);

/***********************************************************************************************//**
*  \brief  Send a predefined text to the host device.
***************************************************************************************************/
void hidSendKeyboardText(void);

void hidSendChar(uint8_t ch);

/** @} (end addtogroup hid) */
/** @} (end addtogroup Features) */

#ifdef __cplusplus
};
#endif

#endif /* HID_H */

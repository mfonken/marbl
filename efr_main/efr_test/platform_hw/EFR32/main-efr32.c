/***********************************************************************************************//**
 * \file   main-efr32.c
 * \brief  Main plugin implementation
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

/* generated headers */
#include CONFIGURATION_HEADER
#include BOOKKEEPING_HEADER
#include CALLBACKS_HEADER

/***********************************************************************************************//**
 * \defgroup main_efr32 Main EFR32
 * \brief Main implementation for the EFR32
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup platform_hw
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup main_efr32
 * @{
 **************************************************************************************************/


/***********************************************************************************************//**
 *  \brief  Main function
 **************************************************************************************************/
void main(void)
{
  /* Perform initialisation of the stack. */
  emberAfMainEfr32StackInitCallback();

  /* Services will be initialized only at stack boot event (gecko_evt_system_boot_id) handler. */

  /* Perform initialisation of the application. */
  emberAfMainEfr32AppInitCallback();

  while (1) {
    /* Perform periodic stack functions. */
    emberAfMainStackTickCallback();
    /* Perform periodic functions implemented in plugins. */
    emberAfMainPluginsTick();
    /* Perform periodic application functions. */
    emberAfMainAppTickCallback();
  }
}


/** @} (end addtogroup main_efr32) */
/** @} (end addtogroup platform_hw) */


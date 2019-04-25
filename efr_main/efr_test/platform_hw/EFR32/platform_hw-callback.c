/***********************************************************************************************//**
 * \file   platform_hw-callback.c
 * \brief  Callbacks related to HW platform
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/
 
#include "boards.h"

#include CONFIGURATION_HEADER
#include CALLBACKS_HEADER

/* standard library headers */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


/* BG stack headers */
#include "bg_types.h"
#include "native_gecko.h"

/* application specific files */
#include "app.h"
#include "app_ui.h"
#include "platform_hw-callback.h"


/* libraries containing default gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
#include "bspconfig.h"
#include "em_system.h"
//#include "flashpwr.h"
#include "initDevice.h"
#ifdef SILABS_AF_PLUGIN_PTI
#include "pti.h"

/* own header */
#include "platform_hw-callback.h"
/***************************************************************************************************
  Local Variables
 **************************************************************************************************/

static const RADIO_PTIInit_t ptiInit =
{
  RADIO_PTI_MODE_UART,
  SILABS_AF_PLUGIN_PTI_BAUD,
  SILABS_AF_PLUGIN_PTI_D_OUT_LOC,
  (GPIO_Port_TypeDef)SILABS_AF_PLUGIN_PTI_DOUT_PORT,
  SILABS_AF_PLUGIN_PTI_DOUT_PIN,
  /* SPI Data clock (DCLK) settings are not relevant for UART mode */
  0,(GPIO_Port_TypeDef)0,0,
  SILABS_AF_PLUGIN_PTI_DFRAME_LOC,
  (GPIO_Port_TypeDef)SILABS_AF_PLUGIN_PTI_DFRAME_PORT,
  SILABS_AF_PLUGIN_PTI_DFRAME_PIN
};
#endif /* SILABS_AF_PLUGIN_PTI */

#if defined SILABS_AF_PLUGIN_PTI || defined SILABS_AF_PLUGIN_IDLE_SLEEP
/* Gecko configuration parameters (see gecko_configuration.h) */
static const gecko_configuration_t config=
{
  /* USARTs can be configured (see datasheet for signal location options */

  /* I2C can be configured (see datasheet for signal location options. flags field must be set to
  I2C_FLAGS_ENABLED to enable peripheral */

  /* GPIO default configuration can be set (see EFR Reference Manual)
  CTRL - Port Control Register
  MODEL - Port Pin Mode Low Register
  MODEH - Port Pin Mode High Register
  DOUT - Port Data Out Register */

  /* Power management (DC/DC regulator) can be configured, for initial setting see EFR Reference
   * Manual and em_emu.h file */

  /* High Frequency Oscillator and Low Frequency Oscillators  can be configured, for initial setting
   *  see Clock Management in reference manual and em_cmu.h file */

  /* Packet Trace Interface can be enabled by giving here the boards specific settings
   * or disabled by giving here NULL */
#ifdef SILABS_AF_PLUGIN_PTI
  .pti = &ptiInit,
#endif /* SILABS_AF_PLUGIN_PTI */

#ifdef SILABS_AF_PLUGIN_IDLE_SLEEP
  .sleep =
  {
    SLEEP_FLAGS_DEEP_SLEEP_ENABLE, 0, 0
  }
#endif /* SILABS_AF_PLUGIN_IDLE_SLEEP */

};
#else /* !defined SILABS_AF_PLUGIN_PTI && !defined SILABS_AF_PLUGIN_IDLE_SLEEP */
static const gecko_configuration_t config;
#endif /* defined SILABS_AF_PLUGIN_PTI || defined SILABS_AF_PLUGIN_IDLE_SLEEP */

/***************************************************************************************************
 Function Definitions
 **************************************************************************************************/

void mainEfr32StackInitCallback(void) {
#if (EMBER_AF_BOARD_TYPE == BRD4100A) \
    || (EMBER_AF_BOARD_TYPE == BRD4151A) \
    || (EMBER_AF_BOARD_TYPE == BRD4153A) \
    || (EMBER_AF_BOARD_TYPE == BRD4301A) \
  /* Put the SPI flash into Deep Power Down mode for those radio boards where it is available */
  flashpwrInit();
  flashpwrDeepPowerDown();
#endif /* EMBER_AF_BOARD_TYPE */
  enter_DefaultMode_from_RESET();
  /* Init stack using configuration structure. */
  gecko_init(&config);
}

void mainAppTickCallback(void) {
  struct gecko_cmd_packet* evt;

  /* Check for stack event. */
  evt = gecko_peek_event();
  /* Run application and event handler. */
  appHandleEvents(evt);
}


/***********************************************************************************************//**
 * \file   app_hw/app_ui.c
 * \brief  User interface specific application code
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

#include "boards.h" //todo move his to config header

#include CONFIGURATION_HEADER

/* BG stack headers*/
#include "bg_types.h"
#include "infrastructure.h"
#include "native_gecko.h"

/* em library */
#include "em_gpio.h"

/* STK header files. */
#if (EMBER_AF_BOARD_TYPE != BRD4300A) && (EMBER_AF_BOARD_TYPE != BRD4300AREVA02) && (EMBER_AF_BOARD_TYPE != BRD4301A)
#include "bspconfig.h"
#include "bsp.h"
#endif /* EMBER_AF_BOARD_TYPE != BRD4300A */
/* LCD */
#include "graphics.h"

/* application specific header files*/
#include "event_control.h"
#include "app_cfg.h"

/* Own header */
#include "app_ui.h"

/***********************************************************************************************//**
 * @addtogroup app_hardware
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app_ui
 * @{
 **************************************************************************************************/


/***************************************************************************************************
 Public Variables
 **************************************************************************************************/

 EmberEventControl uiTimerEvt = { EVENT_INACTIVE, 0 };

/***************************************************************************************************
  Local Macros and Definitions
 **************************************************************************************************/
 /* Text definitions*/
 #define APP_HEADER                   "SILICON LABORATORIES\nBluetooth Smart Demo\n\n" \
                                        "Blue Gecko #%05u \n\n"
 #define APP_HEADER_DEFAULT           "SILICON LABORATORIES\nBluetooth Smart Demo\n\n" \
                                        "Blue Gecko #00000 \n\n"
 #define APP_HEADER_SIZE              (sizeof(APP_HEADER_DEFAULT))

/** UI Timer periodical call frequency in ms. */
#define APP_UITIMER_PERIOD            100

#define BLINK_PERIOD				  500

/** UI Timer periodical call frequency in ms. */
#define APP_RC_DISCHARGE_PERIOD       2

/** Max. short Press Duration as a multiple of 100 ms. */
#define APP_SHORT_PRESS_DUR           20
/** Min. Long Press Duration as a multiple of 100 ms. */
#define APP_LONG_PRESS_DUR            50


/***************************************************************************************************
 Local Type Definitions
 **************************************************************************************************/
/** Struct for states of the available LEDs on the board. */
struct appUiLedStates {
  uint8_t led1State;  /**< state can be 0 (off) and 1 (on). */
  uint8_t led2State;  /**< state can be 0 (off) and 1 (on). */
};

/** An LED sequence request consists of the sequence and its length. */
struct appUiLedSeqReq {
  struct appUiLedStates *ledSeq;  /**< pointer to the LED sequence. */
  uint8_t ledSeqLen;              /**< length of the sequence. */
};

/** Button press handler struct. */
static struct {
  appUiBtnCback_t cback;
} appUiBtn;

static uint8_t blink_state;

/***************************************************************************************************
 Local Variables
 **************************************************************************************************/
#if (EMBER_AF_BOARD_TYPE != BRD4301A)
/** Character array to hold the string to be printed on the graphical display. */
static char appUiHeaderString[APP_HEADER_SIZE];
#endif /* BRD4301A */

/** Off LED sequence and request. */
static struct appUiLedStates appUiLedSeqOff[] = { { 0, 0 } };
static struct appUiLedSeqReq appUiLedSeqOffReq = {appUiLedSeqOff, COUNTOF(appUiLedSeqOff)};

/** Low alert LED sequence and request. */
static struct appUiLedStates appUiLedSeqLowAlert[] = { { 1, 0 }, { 1, 0 },
                                                       { 1, 0 }, { 1, 0 },
                                                       { 1, 0 }, { 1, 0 },
                                                       { 1, 0 }, { 1, 0 },
                                                       { 0, 1 }, { 0, 1 },
                                                       { 0, 1 }, { 0, 1 },
                                                       { 0, 1 }, { 0, 1 },
                                                       { 0, 1 }, { 0, 1 } };
static struct appUiLedSeqReq appUiLedSeqLowAlertReq =
  {appUiLedSeqLowAlert, COUNTOF(appUiLedSeqLowAlert)};

/** High alert LED sequence and request. */
static struct appUiLedStates appUiLedSeqHighAlert[] = { { 1, 0 }, { 1, 0 },
                                                        { 0, 1 }, { 0, 1 } };
static struct appUiLedSeqReq appUiLedSeqHighAlertReq =
  {appUiLedSeqHighAlert, COUNTOF(appUiLedSeqHighAlert)};

/** Request a sequence for driving the LEDs. */
static struct appUiLedSeqReq *appUiLedSeqReq = NULL;

/***************************************************************************************************
 Static Function Declarations
 **************************************************************************************************/
static void appUiLedTimerCback(void);

#if (EMBER_AF_BOARD_TYPE == BRD4300A) || (EMBER_AF_BOARD_TYPE == BRD4300AREVA02) || (EMBER_AF_BOARD_TYPE == BRD4301A)
static void appUiButtonInit(void);
static void appUiLedsInit(void);
static void BSP_LedSet(uint8_t AppUiLedId);
static void BSP_LedClear(uint8_t AppUiLedId);
#endif /* EMBER_AF_BOARD_TYPE == BRD4300A */

/***************************************************************************************************
 Public Function Definitions
 **************************************************************************************************/

void appUiBlinkLed()
{
	blink_state = 0;
	eventControlSetDelayMS(&uiTimerEvt, BLINK_PERIOD);
}

void appUiBtnRegister(appUiBtnCback_t cback)
{
  appUiBtn.cback = cback;
}

void appUiLedOff(void)
{
  appUiLedSeqReq = &appUiLedSeqOffReq;
}

void appUiLedLowAlert(void)
{
  appUiLedSeqReq = &appUiLedSeqLowAlertReq;
}

void appUiLedHighAlert(void)
{
  appUiLedSeqReq = &appUiLedSeqHighAlertReq;
}

void appUiInit(uint16_t devId)
{

#if (EMBER_AF_BOARD_TYPE == BRD4300A) || (EMBER_AF_BOARD_TYPE == BRD4300AREVA02) || (EMBER_AF_BOARD_TYPE == BRD4301A)
  /* Start repeating (auto-load) timer */
  eventControlSetDelayMS(&uiTimerEvt,APP_UITIMER_PERIOD - APP_RC_DISCHARGE_PERIOD);
#else /* EMBER_AF_BOARD_TYPE != BRD4300A */
  /* Initialise LEDs */

  /* Start repeating (auto-load) timer */
  eventControlSetDelayMS(&uiTimerEvt,APP_UITIMER_PERIOD);
#endif /* EMBER_AF_BOARD_TYPE == BRD4300A */

#if EMBER_AF_BOARD_TYPE != BRD4301A
  /* Initialize graphics */
  /* Create the device name string based on the device ID */
  snprintf(appUiHeaderString, APP_HEADER_SIZE, APP_HEADER, devId);
  //graphInit(appUiHeaderString);
#endif /* No LCD for BRD4301A*/
}

#if (EMBER_AF_BOARD_TYPE == BRD4300A) || (EMBER_AF_BOARD_TYPE == BRD4300AREVA02) || (EMBER_AF_BOARD_TYPE == BRD4301A)
void appUiTick(void)
{
	GPIO_PinOutSet(gpioPortA, 0);
  /* On BGM111A LEDs and buttons are connected to the same GPIOs, so before we poll buttons we have
   * to set GPIOs to input and wait for input capacitors to discharge
   */

  /* Flag indicating whether discharge has been done since last time GPIO was set to output */
  static bool appUiRcDischargeDone = false;

  if (false == appUiRcDischargeDone) {
    /* Initialize buttons */
    appUiButtonInit();
    /* Start a timer measuring a small time period, during which capacitors on GPIO ports can discharge */
    eventControlSetDelayMS(&uiTimerEvt, APP_RC_DISCHARGE_PERIOD);
    appUiRcDischargeDone = true; /* Indicate discharge has been done */
  }
  else {
	/* Read button state*/
    appUiButtonTimerCallback();

    /* Initialise and drive LEDs */
    appUiLedsInit();
    appUiLedTimerCback();

    /* Restart timer */
    eventControlSetDelayMS(&uiTimerEvt, APP_UITIMER_PERIOD - APP_RC_DISCHARGE_PERIOD);

    /* Discharge needs to be done before next button read */
    appUiRcDischargeDone = false;
  }
}
#else /* EMBER_AF_BOARD_TYPE != BRD4300A */
void appUiTick(void)
{

  /* Refresh LEDs */
  appUiLedTimerCback();
  /* Read button states */

  /* Restart timer */
  eventControlSetDelayMS(&uiTimerEvt,APP_UITIMER_PERIOD);
}
#endif /* EMBER_AF_BOARD_TYPE == BRD4300A */


void appUiWriteString(char *string)
{
#if EMBER_AF_BOARD_TYPE != BRD4301A
  //graphWriteString(string);
#endif /* No LCD for BRD4301A */
}

/***************************************************************************************************
 Static Function Definitions
 **************************************************************************************************/

/***********************************************************************************************//**
 *  \brief  Timer callback for driving the LEDs on the DK based on the requested sequence.
 **************************************************************************************************/
static void appUiLedTimerCback(void)
{
	//blink_state = !blink_state;
	//eventControlSetDelayMS(&uiTimerEvt, BLINK_PERIOD);
	if(blink_state)
	{
		GPIO_PinOutSet(gpioPortD, 13);
	}
	else
	{
		GPIO_PinOutClear(gpioPortD, 13);
	}
//  static uint8_t pos = 0;
//  static struct appUiLedSeqReq *activeReq = &appUiLedSeqOffReq;
//
//  /* If there is a request and it is not yet processed */
//  if (appUiLedSeqReq && (activeReq != appUiLedSeqReq)) {
//    activeReq = appUiLedSeqReq;
//    pos = 0;
//  }
//
//  /* Process the active request if it exists */
//  if (activeReq) {
//    activeReq->ledSeq[pos].led1State ?  BSP_LedSet(1) : BSP_LedClear(1);
//    activeReq->ledSeq[pos].led2State ?  BSP_LedSet(0) : BSP_LedClear(0);
//    pos++;
//    if (pos >= activeReq->ledSeqLen) {
//      pos = 0;
//    }
//
//    /* If the active request is the special off request, then after processing
//     * clear the active request (and save some processing time while LEDs are off) */
//    if (activeReq == &appUiLedSeqOffReq) {
//      activeReq = NULL;
//    }
//  }
}



/***********************************************************************************************//**
 *  \brief  Dispatch a button pressed event by calling the registered button event callback.
 *  \param[in]  btn  Button number and press duration enumeration.
 **************************************************************************************************/

#if (EMBER_AF_BOARD_TYPE == BRD4300A) || (EMBER_AF_BOARD_TYPE == BRD4300AREVA02) || (EMBER_AF_BOARD_TYPE == BRD4301A)
static void appUiButtonInit(void)
{
  /* Configure pin as input */
  GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeInput, 1);
  /* Configure pin as input */
  GPIO_PinModeSet(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, gpioModeInput, 1);
}

static void appUiLedsInit(void)
{
  /* Configure pin as output */
  GPIO_PinModeSet(BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN, gpioModePushPull, 1);
  /* Configure pin as output */
  GPIO_PinModeSet(BSP_GPIO_LED0_PORT, BSP_GPIO_LED1_PIN, gpioModePushPull, 1);

}

/* Output = 0 -> LED is on, Output = 1 -> LED is off */
static void BSP_LedSet(uint8_t AppUiLedId)
{
  switch (AppUiLedId)
  {
  case 0:
    GPIO_PinOutClear(BSP_GPIO_LED0_PORT,BSP_GPIO_LED0_PIN);
      break;
  case 1:
    GPIO_PinOutClear(BSP_GPIO_LED1_PORT,BSP_GPIO_LED1_PIN);
      break;
  default:
      break;
  }
}

/* Output = 0 -> LED is on, Output = 1 -> LED is off */
static void BSP_LedClear(uint8_t AppUiLedId)
{
  switch (AppUiLedId)
  {
  case 0:
    GPIO_PinOutSet(BSP_GPIO_LED0_PORT,BSP_GPIO_LED0_PIN);
      break;
  case 1:
    GPIO_PinOutSet(BSP_GPIO_LED1_PORT,BSP_GPIO_LED1_PIN);
      break;
  default:
      break;
  }
}
#endif /* EMBER_AF_BOARD_TYPE == BRD4300A */


/** @} (end addtogroup app_ui) */
/** @} (end addtogroup app_hardware) */


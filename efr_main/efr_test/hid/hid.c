/***********************************************************************************************//**
 * \file   hid.c
 * \brief  Human Interface Device Service
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

#include CONFIGURATION_HEADER
#include CALLBACKS_HEADER

/* standard libraries*/
#ifdef HOST
#if _WIN32 != 1
#include <termios.h>
#include <sys/select.h>
#include <unistd.h>
#else /* _WIN32 == 1 */
#include <conio.h>
#endif /* _WIN32 */
#endif /* HOST */

/* BG stack headers */
#include "bg_types.h"
#include "gatt_db.h"
#ifdef HOST
#include "gecko_bglib.h"
#else /* !HOST */
#include "native_gecko.h"
#endif /* !HOST */
#include "infrastructure.h"

/* application specific headers */
#include "event_control.h"
#include "app_ui.h"
#include "connection.h"

/* Own header */
#include "hid.h"

/***********************************************************************************************//**
 * @addtogroup Features
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup hid
 * @{
 **************************************************************************************************/


/***************************************************************************************************
  Local Macros and Definitions
***************************************************************************************************/

/* HID Protocol mode characteristic values */
/** HID report mode. */
#define HID_REPORT_MODE                      1
/** HID boot mode. */
#define HID_BOOT_MODE                        0

/** HID notification period in ms. */
#define HID_IND_TIMEOUT                      250
/** Indicates currently there is no active connection using this service. */
#define HID_NO_CONNECTION                    0xFF
/** Default maximum payload length for most PDUs. */
#define ATT_DEFAULT_PAYLOAD_LEN              20

/***************************************************************************************************
  Type Definitions
***************************************************************************************************/

/***************************************************************************************************
  Local Variables
***************************************************************************************************/

/* attribute handle of characteristic where notifications can be enabled */
static uint8_t hidAttribute;

/* Pressed buttons on the keyboard will be interpreted as characters to send, or not */
static uint8_t hidKeyboardEnabled = 0;

#ifndef HOST
/* Text to display on HID host device */
static const uint8_t hidText[] = SILABS_AF_PLUGIN_HID_HID_TEXT;
static uint8_t hidTextIndex = 0;
#endif /* !HOST */

/***************************************************************************************************
 Static Function Declarations
 **************************************************************************************************/

static uint8_t hidGetChar(void);
static bool hidIsCharLeftToSend(void);
static void hidSendKeyboardPress(uint8_t character);

#ifdef HOST
#if _WIN32 != 1
static int kbhit(void);
static char getch(void);
static void tty_cbreak(void);
/* todo currently not used. Must be called when connection ends*/
#if 0
static void tty_restore(void);
#endif /* 0 */
#endif /* _WIN32 */
#endif /* HOST */

/***************************************************************************************************
 Public Variable Definitions
 **************************************************************************************************/
#ifdef HOST
#if _WIN32 != 1
static struct termios oldTermiosSettings = {0};
#endif /* _WIN32 */
#endif /* HOST */

EmberEventControl hidTimerEvt = { EVENT_INACTIVE, 0 };

/***************************************************************************************************
 Function Definitions
 **************************************************************************************************/

void hidInit(void)
{
  hidAttribute = gattdb_hid_keyboard_in;  /* HID Protocol mode is initially Report mode */

  eventControlSetInactive(hidTimerEvt);  /* HID Timer is initially inactive */

#ifdef HOST
#if _WIN32 != 1
  tty_cbreak();
#endif /* _WIN32 */
#endif /* HOST */
}

void hidKeyInCharStatusChange(uint8_t connection, uint16_t clientConfig)
{
  /* if the new CCCD value of Keyboard Input is not 0 (either indication or notification enabled)
   *  start waiting for button press, which triggers sending indications */
  if (clientConfig) {
    hidKeyboardEnabled = 1; /* Listening for keyboard press started */
#ifdef HOST
    eventControlSetDelayMS(&hidTimerEvt, HID_IND_TIMEOUT);
#endif /* HOST */
  } else {
	/* indications switched off */
    eventControlSetInactive(hidTimerEvt);
    hidKeyboardEnabled = 0;
  }
}

void hidBootKeyInCharStatusChange(uint8_t connection, uint16_t clientConfig)
{
  /* if the new CCCD value of Boot Keyboard Input is not 0 (either indication or notification
   * enabled) start waiting for button press, which triggers sending indications */
  if (clientConfig) {
    hidKeyboardEnabled = 1; /* Listening for keyboard press started */
#ifdef HOST
    eventControlSetDelayMS(&hidTimerEvt, HID_IND_TIMEOUT);
#endif /* HOST */
  } else {
    /* indications switched off */
    eventControlSetInactive(hidTimerEvt);
    hidKeyboardEnabled = 0;
  }
}

void hidProtocolModeWrite(uint8array *writeValue)
{
  switch (writeValue->data[0]) {
    default:
    case HID_REPORT_MODE:
      /* HID protocol Mode value is set to Report Protocol Mode */
      hidAttribute = gattdb_hid_keyboard_in;
      break;

    case HID_BOOT_MODE:
      /* HID protocol Mode value is set to Boot Protocol Mode */
      hidAttribute = gattdb_hid_boot_keyboard_in;
      break;
  }
}

void hidSendChar(uint8_t ch)
{
	hidSendKeyboardPress(ch);
}

void hidSendKeyboardText(void)
{
  uint8_t ch;

  /* Send character only if CCC is enabled and we are connected. */
  if ((hidKeyboardEnabled) && (HID_NO_CONNECTION != conGetConnectionId())) {
    /* Get character to send. */
    if ((ch = hidGetChar())) {
      /* Send character. */
      hidSendKeyboardPress(ch);
      /* Check if there is any char left to send. */
      if (hidIsCharLeftToSend()) {
        /* Schedule next char check. */
        eventControlSetDelayMS(&hidTimerEvt, HID_IND_TIMEOUT);
      } else {
        /* No more char to send. */
        eventControlSetInactive(hidTimerEvt);
      }
    }
  }
}

/***************************************************************************************************
 Static Function Definitions
 **************************************************************************************************/

/***********************************************************************************************//**
*  \brief  Return a single character which should be sent next.
*  \return  Single character to send.
**************************************************************************************************/
static uint8_t hidGetChar(void)
{
#ifdef HOST
  if (kbhit()) {
    return getch();
  }

  return 0;
#else /* !HOST */
  return hidText[hidTextIndex];
#endif /* HOST */
}

/***********************************************************************************************//**
*  \brief  Determines whether there are more characters available to send.
*  \return  Are there more characters to send?.
**************************************************************************************************/
static bool hidIsCharLeftToSend(void)
{
#ifdef HOST
  return true;
#else /* !HOST */
  if (hidText[++hidTextIndex]) {
    return true;
  }
  hidTextIndex = 0;
  return false;
#endif /* HOST */
}


/***********************************************************************************************//**
*  \brief  Send a specific character to the HID host.
*  Both the push and release of keyboard button is reported.
*  \param[in]  character  Character to be sent.
**************************************************************************************************/
static void hidSendKeyboardPress(uint8_t character)
{
  uint8_t length = 8;
  uint8_t hidTempBuffer[8];

  memset(hidTempBuffer,0,8); /* set 0 to all bytes */

  emberAfPluginHidSendNewCharCallback(character); /* Send callback */

  /* Push Shift if we find a capital letter */
  if ((character >= 'A') && (character <= 'Z')) {
    hidTempBuffer[0] = 2; /* SHIFT*/
    character = character - 'A' + 'a'; /* tolower() */
  }

  /* Handle some special characters like SPACE, '.' and '\n' */
  if (character == ' ') {
    hidTempBuffer[2] = 44; /* HID usage ID of spacebar */
#if _WIN32 != 1
  } else if (character == '\n') {
#else /* _WIN32 == 1 */
  } else if (character == '\r') {
#endif /* _WIN32 */
    hidTempBuffer[2] = 40; /* HID usage ID of \n */
  } else if (character == '.') {
    hidTempBuffer[2] = 55; /* HID usage ID of . */
  } else if (character == '?') {
    hidTempBuffer[0] = 2; /* SHIFT*/
    hidTempBuffer[2] = 56; /* HID usage ID of ? */
#if _WIN32 != 1
  } else if (character == 127) {
#else /* _WIN32 == 1 */
  } else if (character == 8) {
#endif /* _WIN32 */
    hidTempBuffer[2] = 42; /* HID usage ID of Backspace */
  } else if (character == ',') {
    hidTempBuffer[2] = 54; /* HID usage ID of , */
  } else if (character == '!') {
    hidTempBuffer[0] = 2; /* SHIFT*/
    hidTempBuffer[2] = 30; /* HID usage ID of ! */
  } else if (character == '0') {
     hidTempBuffer[2] = 39; /* HID usage ID of 0 */
  } else if ((character >= '1') && (character <= '9')) {
       hidTempBuffer[2] = character -'1' + 30 ;; /* HID usage ID of numbers */
  }else  if ((character >= 'a') && (character <= 'z')) {
    hidTempBuffer[2] = character -'a' + 4 ; /* HID usage ID of letters */
  } else {
    return; // not supported character
  }

  /* Send notification about the button press */
  gecko_cmd_gatt_server_send_characteristic_notification(conGetConnectionId(), hidAttribute, length,
                                                         hidTempBuffer);

  /* release all characters on keyboard */
  hidTempBuffer[0] = 0;
  hidTempBuffer[2] = 0;

  /* Send notification about the button release */
  gecko_cmd_gatt_server_send_characteristic_notification(conGetConnectionId(), hidAttribute, length,
                                                         hidTempBuffer);

}
#ifdef HOST
#if _WIN32 != 1
/***********************************************************************************************//**
*  \brief  Unix implementation of _kbhit function from conio.h in Windows systems.
*  The function tells if a character has been pressed
*  \return 0 if no character has been pressed, nonzero otherwise.
**************************************************************************************************/
static int kbhit(void)
{
  struct timeval timeval;
  fd_set fds;

  timeval.tv_sec = 0;
  timeval.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
  select(STDIN_FILENO+1, &fds, NULL, NULL, &timeval);
  return FD_ISSET(STDIN_FILENO, &fds);
}

/***********************************************************************************************//**
*  \brief  Switch terminal to 'cbreak' mode. (Characters are not echoed but returned immediately as
*   they are typed)
**************************************************************************************************/
static void tty_cbreak(void)
{
  /* read old termios settings */
  if (tcgetattr(0, &oldTermiosSettings) < 0) {
    perror("tcsetattr()");
  }
  oldTermiosSettings.c_lflag &= ~ICANON; /* turn off canonical mode */
  oldTermiosSettings.c_lflag &= ~ECHO; /* suppress echoing */
  oldTermiosSettings.c_cc[VMIN] = 1; /* minimum number of characters for non-canonical read */
  oldTermiosSettings.c_cc[VTIME] = 0; /* Timeout for noncanonical read set to ZERO */
  /* set new settings */
  if (tcsetattr(0, TCSANOW, &oldTermiosSettings) < 0) {
    perror("tcsetattr ICANON");
  }
}

/***********************************************************************************************//**
*  \brief  Switch terminal back to its original settings.
**************************************************************************************************/
/* todo currently not used. Must be called when connection ends*/
#if 0
static void tty_restore(void)
{
    oldTermiosSettings.c_lflag |= ICANON;
    oldTermiosSettings.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &oldTermiosSettings) < 0) {
      perror ("tcsetattr ~ICANON");
    }
}
#endif
/***********************************************************************************************//**
*  \brief  Unix implementation of _getch function from conio.h in Windows systems.
*  Capture one character from standard input without having to wait for ENTER to be pressed.
*  Only works in cbreak mode (tty_cbreak() has to be called before calling this function).
*  \return  ASCII code of pressed character.
**************************************************************************************************/
static char getch(void)
{
  char character = 0;
  if (read(0, &character, 1) < 0) {
    perror ("read()");
  }
  return (character);
}
#endif /* _WIN32 */
#endif /* HOST */


/** @} (end addtogroup hid) */
/** @} (end addtogroup Features) */


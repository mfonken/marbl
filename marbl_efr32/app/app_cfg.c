/***********************************************************************************************//**
 * \file   app_cfg.c
 * \brief  Application configuration  file
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

/* generated headers */
#include CONFIGURATION_HEADER
#include CALLBACKS_HEADER
#include BOOKKEEPING_HEADER

/* BG stack headers */
#include "bg_types.h"
#include "infrastructure.h"

#ifdef HOST
#include "gecko_bglib.h"
#else /* !HOST */
#include "native_gecko.h"
#endif /* !HOST */

/* BG stack headers */
#include "gatt_db.h"

/* application specific headers */
#include "app_ui.h"
#include "event_control.h"

/* features */
#ifdef SILABS_AF_PLUGIN_CONNECTION
#include "connection.h"
#endif /* SILABS_AF_PLUGIN_CONNECTION */
#ifdef SILABS_AF_PLUGIN_ADVERTISEMENT
#include "advertisement.h"
#endif /* SILABS_AF_PLUGIN_ADVERTISEMENT */
#ifdef SILABS_AF_PLUGIN_ANC
#include "anc.h"
#endif /* SILABS_AF_PLUGIN_ANC */
#ifdef SILABS_AF_PLUGIN_DISC
#include "disc.h"
#endif /* SILABS_AF_PLUGIN_DISC */
#ifdef SILABS_AF_PLUGIN_BATT
#include "batt.h"
#endif /* SILABS_AF_PLUGIN_BATT */
#ifdef SILABS_AF_PLUGIN_CP
#include "cp.h"
#endif /* SILABS_AF_PLUGIN_CP */
#ifdef SILABS_AF_PLUGIN_CSC
#include "csc.h"
#endif /* SILABS_AF_PLUGIN_CSC */
#ifdef SILABS_AF_PLUGIN_HID
#include "hid.h"
#endif /* SILABS_AF_PLUGIN_HID */
#ifdef SILABS_AF_PLUGIN_HR
#include "hr.h"
#endif /* SILABS_AF_PLUGIN_HR */
#ifdef SILABS_AF_PLUGIN_HTM
#include "htm.h"
#endif /* SILABS_AF_PLUGIN_HTM */
#ifdef SILABS_AF_PLUGIN_IA
#include "ia.h"
#endif /* SILABS_AF_PLUGIN_IA */
#ifdef SILABS_AF_PLUGIN_LL
#include "ll.h"
#endif /* SILABS_AF_PLUGIN_LL */
#ifdef SILABS_AF_PLUGIN_CABLE_SERVER
#include "cable_server.h"
#endif /* SILABS_AF_PLUGIN_CABLE_SERVER */
#ifdef SILABS_AF_PLUGIN_CABLE_CLIENT
#include "cable_client.h"
#endif /* SILABS_AF_PLUGIN_CABLE_CLIENT */
#ifdef SILABS_AF_PLUGIN_CENTRAL
#include "central.h"
#endif /* SILABS_AF_PLUGIN_CENTRAL */
#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER
#include "sqa_throughput_server.h"
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER */
#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT
#include "sqa_throughput_client.h"
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT */
#ifdef SILABS_AF_PLUGIN_SQA_LATENCY
#include "sqa_latency.h"
#endif /* SILABS_AF_PLUGIN_SQA_LATENCY */

/* Own header */
#include "app_cfg.h"

/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app_cfg
 * @{
 **************************************************************************************************/


/***************************************************************************************************
 Variables

 **************************************************************************************************/

 EmberEventData stackEvts[] =
{
  /* Terminators. */
  {NULL, NULL}
};

AppCfgGattServerAttributeValue_t appCfgGattServerAttributeValue[] =
{
#ifdef SILABS_AF_PLUGIN_CABLE_SERVER
  {gattdb_uart_data,   cableServerGatt2Stdo},
#endif /* SILABS_AF_PLUGIN_CABLE_SERVER */
#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER
  {gattdb_uart_data,   sqaThroughputServerGatt},
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER */
#ifdef SILABS_AF_PLUGIN_IA
  {gattdb_alert_level, iaImmediateAlertWrite},
#endif /* SILABS_AF_PLUGIN_IA */
#ifdef SILABS_AF_PLUGIN_LL
  {gattdb_link_loss_alert_level, llLinkLossWrite},
#endif /* SILABS_AF_PLUGIN_LL */
#ifdef SILABS_AF_PLUGIN_HID
  {gattdb_hid_protocol_mode, hidProtocolModeWrite},
#endif /* SILABS_AF_PLUGIN_HID */
  {0, NULL}
};
AppCfgGattServerUserReadRequest_t appCfgGattServerUserReadRequest[] =
{
#ifdef SILABS_AF_PLUGIN_HTM_MEAS_INTERV_CHAR
  {gattdb_meas_int, htmMeasurementIntervalRead},
#endif /* SILABS_AF_PLUGIN_HTM_MEAS_INTERV_CHAR */
#ifdef SILABS_AF_PLUGIN_BATT
  {gattdb_batt_measurement, battRead},
#endif /* SILABS_AF_PLUGIN_BATT */
  {0, NULL}
};

AppCfgGattServerUserWriteRequest_t appCfgGattServerUserWriteRequest[] =
{
#ifdef SILABS_AF_PLUGIN_HTM_MEAS_INTERV_CHAR
  {gattdb_meas_int, htmMeasurementIntervalWrite},
#endif /* SILABS_AF_PLUGIN_HTM_MEAS_INTERV_CHAR */
#ifdef SILABS_AF_PLUGIN_HR_ENERGY_EXP_SUP
  {gattdb_hr_controlpoint, hrWrite},
#endif /* SILABS_AF_PLUGIN_HR_ENERGY_EXP_SUP */
#ifdef SILABS_AF_PLUGIN_CSC_WHEEL_DATA_SUP
  {gattdb_cycling_speed_cp, cscControlPointWrite},
#endif /* SILABS_AF_PLUGIN_CSC_WHEEL_DATA_SUP */
#if defined(SILABS_AF_PLUGIN_CP_WHEEL_DATA_SUP) || defined(SILABS_AF_PLUGIN_CP_CP_VECT_SUP)
  {gattdb_cycling_power_cp, cpControlPointWrite},
#endif /* SILABS_AF_PLUGIN_CSC_WHEEL_DATA_SUP */
  {0, NULL}
};

AppCfgGattServerCharStatus_t appCfgGattServerCharStatus[] =
{
#ifdef SILABS_AF_PLUGIN_HTM
  {gattdb_temp_measurement, htmTemperatureCharStatusChange},
#endif /* SILABS_AF_PLUGIN_HTM */
#ifdef SILABS_AF_PLUGIN_HR
  {gattdb_hr_measurement, hrCharStatusChange},
#endif /* SILABS_AF_PLUGIN_HR */
#ifdef SILABS_AF_PLUGIN_BATT
  {gattdb_batt_measurement, battCharStatusChange},
#endif /* SILABS_AF_PLUGIN_BATT */
#ifdef SILABS_AF_PLUGIN_CP
  {gattdb_cycling_power_measurement, cpMeasCharStatusChange},
#endif
#ifdef SILABS_AF_PLUGIN_CP_CP_VECT_SUP
  {gattdb_cycling_vector_measurement, cpVectorCharStatusChange},
#endif /* SILABS_AF_PLUGIN_CP_CP_VECT_SUP */
#ifdef SILABS_AF_PLUGIN_CSC
  {gattdb_cycling_speed_measurement, cscCharStatusChange},
 #endif /* SILABS_AF_PLUGIN_CSC */
#ifdef SILABS_AF_PLUGIN_HID
 {gattdb_hid_keyboard_in, hidKeyInCharStatusChange},
#endif /* SILABS_AF_PLUGIN_HID */
#ifdef SILABS_AF_PLUGIN_HID
  {gattdb_hid_boot_keyboard_in, hidBootKeyInCharStatusChange},
#endif /* SILABS_AF_PLUGIN_HID */
#ifdef SILABS_AF_PLUGIN_CABLE_SERVER
  {gattdb_uart_data, cableServerCharStatusChange},
#endif /* SILABS_AF_PLUGIN_CABLE_SERVER */
#ifdef SILABS_AF_PLUGIN_CSC_WHEEL_DATA_SUP
  {gattdb_cycling_speed_cp, cscCpCharStatusChange},
#endif /* SILABS_AF_PLUGIN_CSC_WHEEL_DATA_SUP */
#if defined(SILABS_AF_PLUGIN_CP_WHEEL_DATA_SUP) || defined(SILABS_AF_PLUGIN_CP_CP_VECT_SUP)
  {gattdb_cycling_power_cp, cpCpCharStatusChange},
#endif /* SILABS_AF_PLUGIN_CSC_WHEEL_DATA_SUP */
  {0, NULL}
};

AppCfgGattServerConfirmation_t appCfgGattServerConfirmation[] =
{
#if defined(SILABS_AF_PLUGIN_CP_WHEEL_DATA_SUP) || defined(SILABS_AF_PLUGIN_CP_CP_VECT_SUP)
  {gattdb_cycling_power_cp, cpConfirmation},
#endif
#ifdef SILABS_AF_PLUGIN_CSC_WHEEL_DATA_SUP
  {gattdb_cycling_speed_cp, cscConfirmation},
#endif /* SILABS_AF_PLUGIN_CSC */
  {0, NULL}
};

AppCfgButtonEvent_t appCfgButtonEvent[] =
{
#ifdef SILABS_AF_PLUGIN_ADVERTISEMENT
  {APP_UI_BTN_0_SHORT, advSwitchAdvMessage},
#endif /* SILABS_AF_PLUGIN_ADVERTISEMENT */
#ifdef SILABS_AF_PLUGIN_HID
  {APP_UI_BTN_1_SHORT, hidSendKeyboardText},
#endif /* SILABS_AF_PLUGIN_HID */
  {APP_UI_BTN_NONE, NULL}
};

size_t appCfgGattServerAttributeValueSize = COUNTOF(appCfgGattServerAttributeValue) - 1;
size_t appCfgGattServerUserReadRequestSize = COUNTOF(appCfgGattServerUserReadRequest) - 1;
size_t appCfgGattServerUserWriteRequestSize = COUNTOF(appCfgGattServerUserWriteRequest) - 1;
size_t appCfgGattServerCharStatusSize = COUNTOF(appCfgGattServerCharStatus) - 1;
size_t appCfgGattServerConfirmationSize = COUNTOF(appCfgGattServerConfirmation) - 1;
size_t appCfgButtonEventSize = COUNTOF(appCfgButtonEvent) - 1;

/***************************************************************************************************
 Function Definitions
 **************************************************************************************************/

void appCfgConnectionClosedEvent(uint8_t connection, uint16_t reason)
{
#ifdef SILABS_AF_PLUGIN_CONNECTION
  conConnectionClosed();
#endif /* SILABS_AF_PLUGIN_CONNECTION */

#ifdef SILABS_AF_PLUGIN_DISC
  discConnClosed();
#endif /* SILABS_AF_PLUGIN_DISC */

#ifdef SILABS_AF_PLUGIN_ADVERTISEMENT
  advInit();
#endif /* SILABS_AF_PLUGIN_ADVERTISEMENT */

  emberAfMainPluginsInit();

#ifdef SILABS_AF_PLUGIN_LL
  llHandleConnectionLostEvent(reason);
#endif /* SILABS_AF_PLUGIN_LL */

#ifdef SILABS_AF_PLUGIN_CABLE_SERVER
  cableServerConnectionClosed();
#endif /* SILABS_AF_PLUGIN_CABLE_SERVER */

#ifdef SILABS_AF_PLUGIN_CABLE_CLIENT
  cableClientConnectionClosed();
#endif /* SILABS_AF_PLUGIN_CABLE_CLIENT */

#ifdef SILABS_AF_PLUGIN_CENTRAL
  centralConnectionClosed();
#endif /* SILABS_AF_PLUGIN_CENTRAL */

#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER
  sqaThroughputServerConnectionClosed();
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER */

#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT
  sqaThroughputClientConnectionClosed();
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT */

#ifdef SILABS_AF_PLUGIN_SQA_LATENCY
  sqaLatencyConnectionClosed();
#endif /* SILABS_AF_PLUGIN_SQA_LATENCY */
}

void appCfgResetEvent(void)
{
#ifdef SILABS_AF_PLUGIN_ADVERTISEMENT
  advInit();
#endif /* SILABS_AF_PLUGIN_ADVERTISEMENT */

#ifdef SILABS_AF_PLUGIN_CONNECTION
  conConnectionInit();  
#endif /* SILABS_AF_PLUGIN_CONNECTION */

emberAfMainPluginsInit(); 

#ifdef SILABS_AF_PLUGIN_CABLE_SERVER
  cableServerSystemBoot();
#endif /* SILABS_AF_PLUGIN_CABLE_SERVER */

#ifdef SILABS_AF_PLUGIN_CENTRAL
  centralSystemBoot();
#endif /* SILABS_AF_PLUGIN_CABLE_CLIENT */

#ifdef SILABS_AF_PLUGIN_CABLE_CLIENT
  cableClientSystemBoot();
#endif /* SILABS_AF_PLUGIN_CABLE_CLIENT */

#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER
  sqaThroughputServerSystemBoot();
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER */

#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT
  sqaThroughputClientSystemBoot();
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT */

#ifdef SILABS_AF_PLUGIN_SQA_LATENCY
  sqaLatencySystemBoot();
#endif /* SILABS_AF_PLUGIN_SQA_LATENCY */

  emberAfPluginResetEventCallback();

}


void appCfgConnectionOpenedEvent(uint8_t connection, uint8_t bonding)
{
#ifdef SILABS_AF_PLUGIN_CONNECTION
  conConnectionStarted(connection, bonding);
#endif /* SILABS_AF_PLUGIN_CONNECTION */

#ifdef SILABS_AF_PLUGIN_ADVERTISEMENT
  advConnectionStarted();
#endif /* SILABS_AF_PLUGIN_ADVERTISEMENT */

#ifdef SILABS_AF_PLUGIN_DISC
  discConnOpen(connection);
#endif /* SILABS_AF_PLUGIN_DISC */

#ifdef SILABS_AF_PLUGIN_CABLE_SERVER
  cableServerConnectionOpened();
#endif /* SILABS_AF_PLUGIN_CABLE_SERVER */

#ifdef SILABS_AF_PLUGIN_CABLE_CLIENT
  cableClientConnectionOpened();
#endif /* SILABS_AF_PLUGIN_CABLE_CLIENT */

#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER
  sqaThroughputServerConnectionOpened();
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_SERVER */

#ifdef SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT
  sqaThroughputClientConnectionOpened();
#endif /* SILABS_AF_PLUGIN_SQA_THROUGHPUT_CLIENT */

#ifdef SILABS_AF_PLUGIN_SQA_LATENCY
  sqaLatencyConnectionOpened();
#endif /* SILABS_AF_PLUGIN_SQA_LATENCY */
}

void appCfgConnectionParametersEvent(uint8_t connection,
                                     uint16_t interval,
                                     uint16_t latency,
                                     uint16_t timeout,
                                     uint8_t security_mode)
{
#ifdef SILABS_AF_PLUGIN_CONNECTION
  conConnectionParameters(connection,
                          interval,
                          latency,
                          timeout,
                          security_mode);
#endif /* SILABS_AF_PLUGIN_CONNECTION */
}

void appCfgGattProcCompEvent(uint16_t result)
{
#ifdef SILABS_AF_PLUGIN_DISC
  discGattProcComplete(result);
#endif /* SILABS_AF_PLUGIN_DISC */

#ifdef SILABS_AF_PLUGIN_SQA_LATENCY
  sqaLatencyGattProcComplete(result);
#endif /* SILABS_AF_PLUGIN_SQA_LATENCY */
}

void appCfgGattBondedEvent(struct gecko_msg_sm_bonded_evt_t* bond)
{
#ifdef SILABS_AF_PLUGIN_DISC
  discRunCallbacks();
#endif /* SILABS_AF_PLUGIN_DISC */
}

void appCfgServiceFoundEvent(struct gecko_msg_gatt_service_evt_t* srv)
{
#ifdef SILABS_AF_PLUGIN_DISC
  discServiceFound(srv);
#endif /* SILABS_AF_PLUGIN_DISC */
}

void appCfgChrFoundEvent(struct gecko_msg_gatt_characteristic_evt_t* chr)
{
#ifdef SILABS_AF_PLUGIN_DISC
  discChrFound(chr);
#endif /* SILABS_AF_PLUGIN_DISC */
}

void appCfgChrValueReceivedEvent (struct gecko_msg_gatt_characteristic_value_evt_t* chr)
{
  /* todo we must check connection ID and characteristic handle here as well */
  if (chr->att_opcode == gatt_handle_value_notification) {
#ifdef SILABS_AF_PLUGIN_ANC
    ancChrValueReceived(chr);
#endif /* SILABS_AF_PLUGIN_ANC */
#ifdef SILABS_AF_PLUGIN_CABLE_CLIENT
    cableClientCharValueChanged(chr);
#endif /* SILABS_AF_PLUGIN_CABLE_CLIENT */
  }
}

void appCfgScanResponse(struct gecko_cmd_packet *evt)
{
#ifdef SILABS_AF_PLUGIN_CENTRAL
  centralScanResponse(evt->data.evt_le_gap_scan_response.data.data,
      evt->data.evt_le_gap_scan_response.data.len,
      evt->data.evt_le_gap_scan_response.address,
      evt->data.evt_le_gap_scan_response.address_type);
#endif /* SILABS_AF_PLUGIN_CABLE_CLIENT */
}

/** @} (end addtogroup app_cfg) */
/** @} (end addtogroup Application) */


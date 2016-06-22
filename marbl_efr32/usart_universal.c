///*
// * usart_universal.c
// *
// *  Created on: Jun 21, 2016
// *      Author: mfonk
// */
//
//#include "uartdrv.h"
//#include "em_gpio.h"
//
//#define UART_PORT_TX 	gpioPortB
//#define UART_PIN_TX		11
//#define UART_PORT_RX 	gpioPortB
//#define UART_PIN_RX		12
//
//#define USART_BAUD		115200
//
//void UARTinit(void)
//{
//
//	UARTDRV_Init_t *initData;
//	initData->baudRate = USART_BAUD;
//	initData->portLocationRx = 6;
//	initData->portLocationTx = 6;
//	initData->stopBits = usartStopbits1;
//	initData->parity = usartNoParity;
//	initData->oversampling = usartOVS16;
//	initData->fcType = uartdrvFlowControlNone;
//
////	  USART_TypeDef              *port;             ///< The peripheral used for UART
////	  uint32_t                   baudRate;          ///< UART baud rate
////	#if defined( _USART_ROUTELOC0_MASK )
////	  uint8_t                    portLocationTx;    ///< Location number for UART Tx pin.
////	  uint8_t                    portLocationRx;    ///< Location number for UART Rx pin.
////	#else
////	  uint8_t                    portLocation;      ///< Location number for UART pins
////	#endif
////	  USART_Stopbits_TypeDef     stopBits;          ///< Number of stop bits
////	  USART_Parity_TypeDef       parity;            ///< Parity configuration
////	  USART_OVS_TypeDef          oversampling;      ///< Oversampling mode
////	#if defined(USART_CTRL_MVDIS)
////	  bool                       mvdis;             ///< Majority Vote Disable for 16x, 8x and 6x oversampling modes
////	#endif
////	  UARTDRV_FlowControlType_t  fcType;            ///< Flow control mode
////	  GPIO_Port_TypeDef          ctsPort;           ///< CTS pin port number
////	  uint8_t                    ctsPin;            ///< CTS pin number
////	  GPIO_Port_TypeDef          rtsPort;           ///< RTS pin port number
////	  uint8_t                    rtsPin;            ///< RTS pin number
////	  UARTDRV_Buffer_FifoQueue_t *rxQueue;          ///< Receive operation queue
////	  UARTDRV_Buffer_FifoQueue_t *txQueue;          ///< Transmit operation queue
////	#if defined( _USART_ROUTELOC1_MASK )
////	  uint8_t                    portLocationCts;   ///< Location number for UART CTS pin.
////	  uint8_t                    portLocationRts;   ///< Location number for UART RTS pin.
////#endif
//
//	UARTDRV_Handle_t handle;
//	handle->initData = *initData;
//	handle->rxPort = UART_PORT_RX;
//	handle->rxPin = UART_PIN_RX;
//	handle->txPort = UART_PORT_TX;
//	handle->txPin = UART_PIN_TX;
//	handle->uartClock = cmuClock_LFE;
//
////	 UARTDRV_Init_t             initData;          // Driver instance initialization data
////	  unsigned int               txDmaCh;           // DMA ch assigned to Tx
////	  unsigned int               rxDmaCh;           // DMA ch assigned to Rx
////	  DMADRV_PeripheralSignal_t  txDmaSignal;       // DMA Tx trigger source signal
////	  DMADRV_PeripheralSignal_t  rxDmaSignal;       // DMA Rx trigger source signal
////	  UARTDRV_FlowControlState_t fcSelfState;       // Current flow control state of self
////	  UARTDRV_FlowControlState_t fcSelfCfg;         // Flow control override configuration of self
////	  UARTDRV_FlowControlState_t fcPeerState;       // Current flow control state of peer
////	  bool                       IgnoreRestrain;    // Transmit does not respect uartdrvFlowControlOff
////	  GPIO_Port_TypeDef          rxPort;            // RX pin port number
////	  uint8_t                    rxPin;             // RX pin number
////	  GPIO_Port_TypeDef          txPort;            // TX pin port number
////	  uint8_t                    txPin;             // RTS pin number
////	  CMU_Clock_TypeDef          uartClock;         // Clock source select
////	  UARTDRV_Buffer_FifoQueue_t *rxQueue;          // Receive operation queue
////	  UARTDRV_Buffer_FifoQueue_t *txQueue;          // Transmit operation queue
////	  volatile bool              rxDmaActive;       // Receive DMA is currently active
////	  volatile bool              txDmaActive;       // Transmit DMA is currently active
//
//
//
//
//	UARTDRV_Init(handle, initData);
//}
//

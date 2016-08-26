///***********************************************************************************************//**
// * \file   platform_hw-callback.h
// * \brief  Callbacks related to HW platform
// ***************************************************************************************************
// * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
// ***************************************************************************************************
// * This file is licensed under the Silabs License Agreement. See the file
// * "Silabs_License_Agreement.txt" for details. Before using this software for
// * any purpose, you must agree to the terms of that agreement.
// **************************************************************************************************/
//
///***************************************************************************************************
// Function Declarations
// **************************************************************************************************/
//
///***********************************************************************************************//**
// *  \brief  Main Stack Init on EFR32.
// *  \details  This function is called when the stack on the EFR32 starts and can be used to perform
// *  necessary initialization required at system startup.
// **************************************************************************************************/
//void mainEfr32StackInitCallback(void);
//
///***********************************************************************************************//**
// *  \brief  Main Application Tick.
// *  \details  This function is called in each iteration of the main application loop and can be used
// *  to perform periodic functions. The frequency with which this function is called depends on how
// *  quickly the main loop runs. If the application blocks at any time during the main loop, this
// *  function will not be called until execution resumes. On SoC platforms, sleeping and idling will
// *  block. On Unix hosts, process yielding (e.g., via select) will block.
// **************************************************************************************************/
//void mainAppTickCallback(void) ;

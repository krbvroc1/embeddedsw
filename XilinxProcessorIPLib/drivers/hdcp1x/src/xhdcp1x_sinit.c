/******************************************************************************
*
* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/
/*****************************************************************************/
/**
*
* @file xhdcp1x_sinit.c
*
* This file contains static initialization method for Xilinx HDCP driver
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ------ -------- --------------------------------------------------
* 1.00  fidus  07/16/15 Initial release.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xhdcp1x.h"
#include "xhdcp1x_cipher.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions *******************************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

extern XHdcp1x_Config XHdcp1x_ConfigTable[];

/************************** Function Definitions *****************************/

/*****************************************************************************/
/**
* This function returns a reference to an XHdcp1x_Config structure based on
* specified device ID.
*
* @param	DeviceID is the unique core ID of the HDCP interface.
*
* @return	A reference to the config record in the configuration table (in
*		xhdcp_g.c) corresponding the specified DeviceID. NULL if no
*		match is found.
*
* @note		None.
*
******************************************************************************/
XHdcp1x_Config *XHdcp1x_LookupConfig(u16 DeviceID)
{
	XHdcp1x_Config *OneToCheck = XHdcp1x_ConfigTable;
	XHdcp1x_Config *CfgPtr = NULL;
	u32 NumLeft = XPAR_XHDCP_NUM_INSTANCES;

	/* Iterate through the configuration table */
	do {
		/* Is this the one? */
		if (OneToCheck->DeviceId == DeviceID) {
			CfgPtr = OneToCheck;
		}

		/* Update for loop */
		OneToCheck++;
		NumLeft--;

	}
	while ((NumLeft > 0) && (CfgPtr == NULL));

	/* Sanity Check */
	if (CfgPtr != 0) {
		u32 Value = 0;
		u32 BaseAddress = CfgPtr->BaseAddress;

		/* Initialize flags */
		CfgPtr->IsRx = FALSE;
		CfgPtr->IsHDMI = FALSE;

		/* Update IsRx */
		Value  = (XHdcp1x_CipherReadReg(BaseAddress,
				XHDCP1X_CIPHER_REG_TYPE));
		Value &= XHDCP1X_CIPHER_BITMASK_TYPE_DIRECTION;
		if (Value == XHDCP1X_CIPHER_VALUE_TYPE_DIRECTION_RX) {
			CfgPtr->IsRx = TRUE;
		}

		/* Update IsHDMI */
		Value  = (XHdcp1x_CipherReadReg(BaseAddress,
				XHDCP1X_CIPHER_REG_TYPE));
		Value &= XHDCP1X_CIPHER_BITMASK_TYPE_PROTOCOL;
		if (Value == XHDCP1X_CIPHER_VALUE_TYPE_PROTOCOL_HDMI) {
			CfgPtr->IsHDMI = TRUE;
		}
	}

	return (CfgPtr);
}
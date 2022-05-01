 /******************************************************************************
 *
 * Module: PduR
 *
 * File Name: PduR.c
 *
 * Description: Source file for  PduR Module
 * AUTOSAR Version:            20-11
 ******************************************************************************/
/********************************************************************************************************************************
 **                                                          Includes                                                                                                **
 ********************************************************************************************************************************/
#include "PduR.h"
#include "Det.h"
/********************************************************************************************************************************
 **                                                       Global Variables                                                                                       **
 ********************************************************************************************************************************/
extern PduR_PBConfigType PduR;
 PduR_StateType PduRState = PDUR_UNINIT;//global 
/********************************************************************************************************************************
**                                                      Functions  definition                                                  **
*********************************************************************************************************************************/
/*********************************************************************************************************************************
 Service name:                  PduR_Init
 Service ID:                      0xF0
 Parameters (in):           ConfigPtr--> Pointer to post build configuration
 Parameters (inout):              None
 Parameters (out):                None
 Return value:                    None
 Description:                  Initializes the PDU Router.
*******************************************************************************************************************************/
void PduR_Init(const PduR_PBConfigType* ConfigPtr)
{
  if (PduRState!= PDUR_UNINIT)
{
		#if PduRDevErrorDetect
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_ComTransmit_SID ,PDUR_E_UNINIT);
		#endif
}
  else {
	PduRState = PDUR_ONLINE;
  }}


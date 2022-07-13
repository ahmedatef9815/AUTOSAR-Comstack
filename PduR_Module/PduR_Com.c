 /******************************************************************************
 *
 * Module: PduR
 *
 * File Name: PduR_Com.c
 *
 * Description: Source file for  PduR Module
 * AUTOSAR Version:            20-11
 ******************************************************************************/
/********************************************************************************************************************************
 **                                                          Includes                                                                                                **
 ********************************************************************************************************************************/
#include "PduR_Com.h"
#include "helper.h"

/********************************************************************************************************************************
 **                                                       Global Variables                                                                                       **
 ********************************************************************************************************************************/
extern PduR_PBConfigType PduR;
extern PduR_StateType PduRState;
/********************************************************************************************************************************
**                                                      Functions  definition                                                  **
*********************************************************************************************************************************/
/*********************************************************************************************************************************
 Service name:                  PduR_ComTransmit
 Service ID:                       0x49
 Parameters (in):           TxPduId--> Identification of the I-PDU.
			   PduInfoPtr-->Length and pointer to the buffer of the I-PDU.
 Parameters (inout):              None
 Parameters (out):                None
 Return value:              Std_ReturnType-->
							E_OK - request is accepted by the destination module; transmission is continued.
							E_NOT_OK - request is not accepted by the destination module;
							transmission is aborted.
 Description:               Requests transmission of an I-PDU.
*******************************************************************************************************************************/
Std_ReturnType PduR_ComTransmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
	uint8 PduRRoutingPathIndex;

	if (PduRState == PDUR_ONLINE) 
	{ 
		for (PduRRoutingPathIndex = 0; PduRRoutingPathIndex < PduRMaxRoutingPathCnt; PduRRoutingPathIndex++)
		{
			if (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRSrcPdu.PduRSourcePduHandleId == TxPduId)
			{ 
                         
				return CanTp_Transmit(PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRDestPdu.PduRDestPduHandleId, PduInfoPtr);
			}
			
		}
                 #if PduRDevErrorDetect
			Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_ComTransmit_SID , PDUR_E_PDU_ID_INVALID); 
	         #endif
        }
	else
	{
		#if PduRDevErrorDetect
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_ComTransmit_SID,PDUR_E_UNINIT);
		#endif
		
		
		
	}
         
	return E_NOT_OK;
}

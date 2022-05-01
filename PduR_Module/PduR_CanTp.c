/******************************************************************************
 *
 * Module: PduR
 *
 * File Name: PduR_CanTp.c
 *
 * Description: Source file for  PduR Module
 * AUTOSAR Version:            20-11
 ******************************************************************************/
/********************************************************************************************************************************
 **                                                          Includes                                                                                                **
 ********************************************************************************************************************************/
#include "PduR_CanTp.h"
#include "helper.h"
/********************************************************************************************************************************
 **                                                       Global Variables                                                                                       **
 ********************************************************************************************************************************/
extern PduR_PBConfigType PduR;
extern PduR_StateType PduRState ;
/********************************************************************************************************************************
**                                                      Functions  definition                                                  **
*********************************************************************************************************************************/
/*********************************************************************************************************************************
 Service name:                 PduR_CanTpRxIndication
 Service ID:                      0x45
 Parameters (in):         PduId--> ID of the received I-PDU.
			  result -->Result of the reception.
 Parameters (inout):              None
 Parameters (out):                None
 Return value:                    None
 Description:                Called after an I-PDU has been received via the TP API, the result indicates whether the
                             transmission was successful or not.

*******************************************************************************************************************************/
void PduR_CanTpRxIndication( PduIdType id, Std_ReturnType result)
{
	 /*
     The reception of an I-PDU received from a communication interface module or from
     transport protocol module and forwarded to the COM module.
    */
    uint8 PduRRoutingPathIndex;
	if  (PduRState == PDUR_ONLINE) 
	{ for(PduRRoutingPathIndex=0; PduRRoutingPathIndex < PduRMaxRoutingPathCnt;PduRRoutingPathIndex++)
		{
			if (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRSrcPdu.PduRSourcePduHandleId == id)
			{ Com_TpRxIndication(PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRDestPdu.PduRDestPduHandleId, result);
                        return;
			}
			
		}
              #if PduRDevErrorDetect
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpRxIndication_SID , PDUR_E_PDU_ID_INVALID); 
		#endif
		
	}
	else
	{
          #if PduRDevErrorDetect
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpRxIndication_SID , PDUR_E_UNINIT);
	   #endif
		
		
	}
      
	return;
}
/*********************************************************************************************************************************
 Service name:                   PduR_CanTpTxConfirmation
 Service ID:                      0x48
 Parameters (in):           TxPduId--> ID of the I-PDU that has been transmitted.
                            result--> Result of the transmission of the I-PDU
 Parameters (inout):              None
 Parameters (out):                None
 Return value:                    None
 Description:               This function is called after the I-PDU has been transmitted on its network, the result indicates
                             whether the transmission was successful or not
*******************************************************************************************************************************/
void  PduR_CanTpTxConfirmation ( PduIdType id,Std_ReturnType result)
{
	uint8 PduRRoutingPathIndex;
        if  (PduRState == PDUR_ONLINE) 
	   { for(PduRRoutingPathIndex=0; PduRRoutingPathIndex < PduRMaxRoutingPathCnt;PduRRoutingPathIndex++)
		{
			if (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRSrcPdu.PduRSourcePduHandleId == id)
			{
				 Com_TpTxConfirmation(PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRDestPdu.PduRDestPduHandleId, result);
                                 return;
			}
			
		}
             #if PduRDevErrorDetect
			Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpTxConfirmation_SID, PDUR_E_PDU_ID_INVALID); 
		#endif
		
	}
	else
	{ 
		#if PduRDevErrorDetect
		Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpTxConfirmation_SID, PDUR_E_UNINIT);
		#endif
		
	}
					
	return;	
		
}			

/*********************************************************************************************************************************
 Service name:                   PduR_CanTpStartOfReception
 Service ID:                      0x46
 Parameters (in):           id-->Identification of the I-PDU.
                          info--> Pointer to a PduInfoType structure containing the payload data
                                 (without protocol information) and payload length of the first
                                 frame or single frame of a transport protocol I-PDU reception, and
                                 the MetaData related to this PDU. If neither first/single frame data
                                 nor MetaData are available, this parameter is set to NULL_PTR.
                      TpSduLength<-- Total length of the N-SDU to be received.
 Parameters (inout):              None
 Parameters (out):     bufferSizePtr<-- Available receive buffer in the receiving module. This parameter
                                        will be used to compute the Block Size (BS) in the transport
                                        protocol module.
                       BufReq_ReturnType<-- BUFREQ_OK: Connection has been accepted. bufferSizePtr
                                        indicates the available receive buffer; reception is continued. If no
                                        buffer of the requested size is available, a receive buffer size of 0
                                        shall be indicated by bufferSizePtr.
                                        BUFREQ_E_NOT_OK: Connection has been rejected; reception
                                        is aborted. bufferSizePtr remains unchanged.
                                        BUFREQ_E_OVFL: No buffer of the required length can be
                                        provided; reception is aborted. bufferSizePtr remains unchanged
 
 Description:               This function is called at the start of receiving an N-SDU. The N-SDU might be fragmented into
                            multiple N-PDUs (FF with one or more following CFs) or might consist of a single N-PDU (SF).
                            The service shall provide the currently available maximum buffer size when invoked with TpSdu
                            Length equal to 0.

*******************************************************************************************************************************/


BufReq_ReturnType PduR_CanTpStartOfReception (PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{ uint8 PduRRoutingPathIndex;

if  (PduRState == PDUR_ONLINE) {
                for(PduRRoutingPathIndex=0; PduRRoutingPathIndex < PduRMaxRoutingPathCnt;PduRRoutingPathIndex++)
		  {
			if (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRSrcPdu.PduRSourcePduHandleId == id)
			{
		            return Com_StartOfReception (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRDestPdu.PduRDestPduHandleId,info, TpSduLength, bufferSizePtr);
			}
                        
                  }
                #if PduRDevErrorDetect
			Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpStartOfReception_SID, PDUR_E_PDU_ID_INVALID); 
		#endif
			return BUFREQ_E_NOT_OK;
			
		   
                      }
else    { 
	       #if PduRDevErrorDetect
		 Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpStartOfReception_SID, PDUR_E_UNINIT);
	        #endif
                 	return BUFREQ_E_NOT_OK;
		
	        }
				
	}


BufReq_ReturnType PduR_CanTpCopyRxData ( PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr)
{ uint8 PduRRoutingPathIndex;

               
                for(PduRRoutingPathIndex=0; PduRRoutingPathIndex < PduRMaxRoutingPathCnt;PduRRoutingPathIndex++)
		  {
			if (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRSrcPdu.PduRSourcePduHandleId == id)
			{
		            return Com_CopyRxData (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRDestPdu.PduRDestPduHandleId, info, bufferSizePtr);
			}
                        
                  }
                #if PduRDevErrorDetect
			Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpCopyRxData_SID, PDUR_E_PDU_ID_INVALID); 
		#endif
			return BUFREQ_E_NOT_OK;
			
		
	}


 BufReq_ReturnType PduR_CanTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,PduLengthType* availableDataPtr)
{ uint8 PduRRoutingPathIndex;

               
                for(PduRRoutingPathIndex=0; PduRRoutingPathIndex < PduRMaxRoutingPathCnt;PduRRoutingPathIndex++)
		  {
			if (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRSrcPdu.PduRSourcePduHandleId == id)
			{
		            return  Com_CopyTxData (PduR.PduRRoutingPaths.PduRRoutingPath[PduRRoutingPathIndex].PduRDestPdu.PduRDestPduHandleId, info,retry, availableDataPtr);

			}
                        
                  }
                #if PduRDevErrorDetect
			Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, PduR_CanTpCopyTxData_SID, PDUR_E_PDU_ID_INVALID); 
		#endif
			return BUFREQ_E_NOT_OK;
			
		   
                      

		
    
		
	}

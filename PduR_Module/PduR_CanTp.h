/******************************************************************************
 *
 * Module: PduR_CanTp
 *
 * File Name: PduR_CanTp.h
 *
 * Description: Header file  PduR Module
 *
 * Author: 
 ******************************************************************************/
#ifndef PDUR_CANTP_H
#define PDUR_CANTP_H
/* PduR Pre-Compile Configuration Header file */
#include "PduR.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for PduR CanTp Rx Indication */
#define PduR_CanTpRxIndication_SID     (uint8)0x45
/* Service ID for PduR CanTp Copy Rx Data */
#define PduR_CanTpCopyRxData_SID       (uint8)0x44
/* Service ID for PduR CanTp StartOfReception */
#define PduR_CanTpStartOfReception_SID (uint8)0x46
/* Service ID for PduR CanTp CopyTxData */
#define PduR_CanTpCopyTxData_SID       (uint8)0x43
/* Service ID for PduR CanTp TxConfirmation */
#define PduR_CanTpTxConfirmation_SID   (uint8)0x48
/*******************************************************************************************************************************
                                               Function Prototypes
******************************************************************************************************************************/
/* Function is  Called after an I-PDU has been received via the TP API*/
void PduR_CanTpRxIndication ( PduIdType id, Std_ReturnType result);
/* Function is  called to provide the received data of an I-PDU segment (N-PDU) to the upper layer*/
BufReq_ReturnType PduR_CanTpCopyRxData ( PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr);
/* Function is called at the start of receiving an N-SDU*/
BufReq_ReturnType PduR_CanTpStartOfReception ( PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr);
/* Function is called to acquire the transmit data of an I-PDU segment (N-PDU)*/
BufReq_ReturnType PduR_CanTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,PduLengthType* availableDataPtr);
/* Function is is called after the I-PDU has been transmitted on its network*/
void PduR_CanTpTxConfirmation ( PduIdType id,Std_ReturnType result);

#endif /*PDUR_CANTP_H*/

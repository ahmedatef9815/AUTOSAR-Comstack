/******************************************************************************
 *
 * Module: PduR_Com
 *
 * File Name: PduR_Com.h
 *
 * Description: Header file  PduR Module
 *
 * Author: 
 ******************************************************************************/
#ifndef PDUR_COM_H
#define PDUR_COM_H
/* PduR Pre-Compile Configuration Header file */
#include "PduR.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PduR Com Transmit */
#define PduR_ComTransmit_SID           (uint8)0x49

/*******************************************************************************************************************************
                                               Function Prototypes
******************************************************************************************************************************/
/* Function for Requests transmission of a PDU*/
Std_ReturnType PduR_ComTransmit (PduIdType TxPduId,const PduInfoType* PduInfoPtr);

#endif /*PDUR_COM_H*/

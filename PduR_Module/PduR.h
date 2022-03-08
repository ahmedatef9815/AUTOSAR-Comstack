 /******************************************************************************
 *
 * Module: PduR
 *
 * File Name: PduR.h
 *
 * Description: Header file  PduR Module
 ******************************************************************************/
#ifndef PDUR_H
#define PDUR_H

/* PduR Pre-Compile Configuration Header file */
#include "PduR_Cfg.h"
#include "ComStack_Types.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PduR Init */
#define PduR_Init_SID                  (uint8)0xf0
/*******************************************************************************************************************************
                                           PduR_Types
******************************************************************************************************************************/
 #define PDUR_MODULE_ID            (uint16)51
#define PDUR_INSTANCE_ID           (uint16)0
/********************************************************************************************************************************
Name:                                PduR_StateType
Type:                                Enumeration
Description:           		  Status of the PDU Router
*********************************************************************************************************************************/
typedef enum{
	/* PDU Router not initialised */
	PDUR_UNINIT,
	/* PDU Router initialized successfully */
	PDUR_ONLINE
}PduR_StateType;
/********************************************************************************************************************************
Name:                                PduRDestPdu
Type:                                Structure
Description:           	This container is a subcontainer of PduRRoutingPath and specifies one
			destination for the PDU to be routed.
*********************************************************************************************************************************/
typedef struct{
	/* PDU identifier assigned by PDU Router. Used by communication interface
	and transport protocol modules for confirmation
	(PduR_<Lo>TxConfirmation) and for TriggerTransmit
	(PduR_<Lo>TriggerTransmit).*/ 
	uint16 PduRDestPduHandleId;
}PduRDestPdu_Type;
/********************************************************************************************************************************
Name:                                PduRSrcPdu
Type:                                Structure
Description:           	This container is a subcontainer of PduRRoutingPath and specifies the
		        source of the PDU to be routed.
*********************************************************************************************************************************/
typedef struct{
	/* PDU identifier assigned by PDU Router. */
	uint16 PduRSourcePduHandleId;
	
	/* When enabled, the TxConfirmation will be forwarded to the upper layer.
	Prerequisites: Lower layer and upper layer support TxConfirmation. */
	boolean PduRSrcPduUpTxConf;
}PduRSrcPdu_Type;
/********************************************************************************************************************************
Name:                                PduRRoutingPath
Type:                                Structure
Description:          This container is a subcontainer of PduRRoutingTable and specifies
                      the routing path of a PDU.
*********************************************************************************************************************************/
typedef struct{
	/* This container is a subcontainer of PduRRoutingPath and
	specifies one destination for the PDU to be routed. */
	PduRDestPdu_Type PduRDestPdu;
	/*This container is a subcontainer of PduRRoutingPath and specifies the
	source of the PDU to be routed. */
	PduRSrcPdu_Type PduRSrcPdu;
}PduRRoutingPath_Type;

/********************************************************************************************************************************
Name:                               PduRRoutingPaths_Type
Type:                                Structure
Description:                         Represents one table of routing paths.
                                     This routing table allows multiple configurations that can be used to
                                     create several routing tables in the same configuration. This is mainly
                                     used for post-build (e.g. post-build selectable) but can be used by
                                     pre-compile and link-time for variant handling.
*********************************************************************************************************************************/
typedef struct{
	 PduRRoutingPath_Type  PduRRoutingPath[PduRMaxRoutingPathCnt];
}PduRRoutingPaths_Type;
/********************************************************************************************************************************
Name:                               PduR_PBConfigType
Type:                                Structure
Description:                       Data structure containing post-build-time configuration data of the PDU Router.
*********************************************************************************************************************************/

typedef struct{
	PduRRoutingPaths_Type PduRRoutingPaths;
}PduR_PBConfigType;



/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid configuration pointer */
#define PDUR_E_INIT_FAILED(uint8)0x00
/* API service (except PduR_GetVersionInfo) used
without module initialization or PduR_Init called in
any state other than PDUR_UNINIT */
#define PDUR_E_UNINIT             (uint8)0x01

/*  Invalid PDU identifier  */
#define PDUR_E_PDU_ID_INVALID   (uint8)0x02

/*******************************************************************************************************************************
                                               Function Prototypes
******************************************************************************************************************************/
/* Function for PduR Init*/
void PduR_Init (const PduR_PBConfigType* ConfigPtr);

#endif /*PDUR_H*/
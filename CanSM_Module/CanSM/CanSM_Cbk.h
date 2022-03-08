/******************************************************************************
 * Module: CanSM
 *
 * File Name: CanSM.h
 *
 * Description: Header file for Can State Manager Call-Back APIs
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */

#ifndef CANSM_CBK_H
#define CANSM_CBK_H

#define CANSM_CBK_SW_MAJOR_VERSION                  (1U)
#define CANSM_CBK_SW_MINOR_VERSION                  (0U)
#define CANSM_CBK_SW_PATCH_VERSION                  (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CANSM_CBK_AR_RELEASE_MAJOR_VERSION          (4U)
#define CANSM_CBK_AR_RELEASE_MINOR_VERSION          (0U)
#define CANSM_CBK_AR_RELEASE_PATCH_VERSION          (3U)


#include "ComStack_Types.h"
#if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION !=CANSM_CBK_AR_RELEASE_MAJOR_VERSION)\
		|| (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != CANSM_CBK_AR_RELEASE_MINOR_VERSION)\
		|| (COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION != CANSM_CBK_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif
#include"CanIF.h"
#if ((CANIF_AR_RELEASE_MAJOR_VERSION !=CANSM_CBK_AR_RELEASE_MAJOR_VERSION)\
		|| (CANIF_AR_RELEASE_MINOR_VERSION != CANSM_CBK_AR_RELEASE_MINOR_VERSION)\
		|| (CANIF_AR_RELEASE_PATCH_VERSION != CANSM_CBK_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

/*******************************************************************************
 *                      Call-Back Function Prototypes                          *
 *******************************************************************************/
void CanSM_ControllerBusOff(
uint8 ControllerId
);

void CanSM_ControllerModeIndication(
uint8 ControllerId,
Can_ControllerStateType ControllerMode
);

void CanSM_TransceiverModeIndication(
uint8 TransceiverId,
CanTrcv_TrcvModeType TransceiverMode
);
void CanSM_TxTimeoutException(
NetworkHandleType Channel
);

void CanSM_ClearTrcvWufFlagIndication(
uint8 Transceiver
);

void CanSM_CheckTransceiverWakeFlagIndication(
uint8 Transceiver
);

void CanSM_ConfirmPnAvailability(
uint8 TransceiverId
);
/*Not Implemented CanSM_CurrentIcomConfiguration*/


#endif


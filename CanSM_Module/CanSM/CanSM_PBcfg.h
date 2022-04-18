/******************************************************************************
 * Module: CanSM
 *
 * File Name: CanSM_PBCfg.h
 *
 * Description: Post_Build Configuration Header file for Can State Manager
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */
#ifndef CANSM_PBCFG_H
#define CANSM_PBCFG_H



#define CANSM_PBCFG_SW_MAJOR_VERSION             (1U)
#define CANSM_PBCFG_SW_MINOR_VERSION             (0U)
#define CANSM_PBCFG_SW_PATCH_VERSION             (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CANSM_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define CANSM_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define CANSM_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

#include "ComStack_Types.h"
#if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION !=CANSM_PBCFG_AR_RELEASE_MAJOR_VERSION)\
		|| (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != CANSM_PBCFG_AR_RELEASE_MINOR_VERSION)\
		|| (COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION != CANSM_PBCFG_AR_RELEASE_PATCH_VERSION))
#error "The AR version of ComStack_Types.h does not match the expected version"
#endif
#include "Dem.h"
#if ((DEM_AR_RELEASE_MAJOR_VERSION !=CANSM_PBCFG_AR_RELEASE_MAJOR_VERSION)\
		|| (DEM_AR_RELEASE_MINOR_VERSION != CANSM_PBCFG_AR_RELEASE_MINOR_VERSION)\
		|| (DEM_AR_RELEASE_PATCH_VERSION != CANSM_PBCFG_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Dem.h does not match the expected version"
#endif

/*Number of can networks*/
#define CANSM_NETWORK_COUNT						(2U)
/*Pre-compile option for Diagnostics Event Manager*/
#define USE_DEM                                 STD_OFF

typedef struct {
	uint8											CanSMControllerId;
} CanSMController;

typedef struct {
	CanSMController*			    Controllers;
	uint8							CanSMTransceiverId;
	uint8							CanSMComMNetworkHandleRef;
	float                           CanSMBorTimeTxEnsured;
	float                           CanSMBorTimeL1;
	float                           CanSMBorTimeL2;
	uint8                           CanSMBorCounterL1ToL2;
	boolean      	                CanSMBorTxConfirmationPolling;
	boolean			                CanSMEnableBusOffDelay;
	#if(USE_DEM==STD_ON)
	Dem_EventIdType			        CanSMBusOffDemEvent;
    #endif
} CanSMManagerNetwork;

typedef struct
{
	uint8 							CanSMModeRequestRepetitionMax;
	float 							CanSMModeRequestRepetitionTime;
	CanSMManagerNetwork*			Networks;
}CanSMConfiguration;

typedef struct {
	CanSMManagerNetwork*			Network;
} CanSM_ConfigType;

#endif

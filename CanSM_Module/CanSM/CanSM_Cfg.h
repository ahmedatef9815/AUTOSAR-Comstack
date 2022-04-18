/******************************************************************************
 * Module: CanSM
 *
 * File Name: CanSM_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for Can State Manager
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */
#ifndef CANSM_CFG_H
#define CANSM_CFG_H


#define CANSM_CFG_SW_MAJOR_VERSION             (1U)
#define CANSM_CFG_SW_MINOR_VERSION             (0U)
#define CANSM_CFG_SW_PATCH_VERSION             (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CANSM_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define CANSM_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define CANSM_CFG_AR_RELEASE_PATCH_VERSION     (3U)


#include "CanSM_PBcfg.h"
#if ((CANSM_CFG_AR_RELEASE_MAJOR_VERSION !=CANSM_PBCFG_AR_RELEASE_MAJOR_VERSION)\
		|| (CANSM_CFG_AR_RELEASE_MINOR_VERSION != CANSM_PBCFG_AR_RELEASE_MINOR_VERSION)\
		|| (CANSM_CFG_AR_RELEASE_PATCH_VERSION != CANSM_PBCFG_AR_RELEASE_PATCH_VERSION))
#error "The AR version of CanSM_PBcfg.h does not match the expected version"
#endif
#include "ComM.h"
#if ((CANSM_CFG_AR_RELEASE_MAJOR_VERSION !=COMM_AR_RELEASE_MAJOR_VERSION)\
		|| (CANSM_CFG_AR_RELEASE_MINOR_VERSION != COMM_AR_RELEASE_MINOR_VERSION)\
		|| (CANSM_CFG_AR_RELEASE_PATCH_VERSION != COMM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of ComM.h does not match the expected version"
#endif

/*COMMUNICATION IN SLEEP MODE(UN_INITIALIZED)*/
#define COMM_SLEEP_COMMUNICATION                (3)
/* Pre-compile option for Development Error Detect */
#define CanSMDevErrorDetect						STD_ON
#define CanSMGetBusOffDelayFunction				User_GetBusOffDelay
#define CanSMIcomSupport						STD_ON
#define CanSMMainFunctionTimePeriod				100
#define CanSMPncSupport							ComMPncSupport
#define CanSMSetBaudrateApi						STD_ON
#define CanSMTxOfflineActiveSupport				STD_ON  /*Pre-compile option for Icom support APi*/
#define CanSMVersionInfoApi						STD_ON

#define CANSM_E_BUS_OFF							FALSE


extern CanSMController controller[CANSM_NETWORK_COUNT];
extern CanSMManagerNetwork CanSMNetwork[CANSM_NETWORK_COUNT];
extern CanSM_ConfigType*  configurationptr;
extern CanSMConfiguration CanSMConfig;

#endif


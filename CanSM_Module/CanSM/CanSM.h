/******************************************************************************
 * Module: CanSM
 *
 * File Name: CanSM.h
 *
 * Description: Header file for Can State Manager
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */

#ifndef CANSM_H
#define CANSM_H



#define CANSM_SW_MAJOR_VERSION                  (1U)
#define CANSM_SW_MINOR_VERSION                  (0U)
#define CANSM_SW_PATCH_VERSION                  (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CANSM_AR_RELEASE_MAJOR_VERSION          (4U)
#define CANSM_AR_RELEASE_MINOR_VERSION          (0U)
#define CANSM_AR_RELEASE_PATCH_VERSION          (3U)



/*Instance number*/
#define CANSM_INSTANCE_NUMBER                   (0U)
/*Vendor ID*/
#define CANSM_VENDOR_ID                         (1000U)
/*Module ID*/
#define CANSM_MODULE_ID                         (140U)

#include "CanSM_Cfg.h"
#if ((CANSM_CFG_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (CANSM_CFG_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (CANSM_CFG_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#include "ComStack_Types.h"
#if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#include "ComM.h"
#if ((COMM_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (COMM_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (COMM_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

/*******************************************************************************
 *                           DET Error Codes                                   *
 *******************************************************************************/
#define CANSM_E_UNINIT                          (1U)
#define CANSM_E_PARAM_POINTER                   (2U)
#define CANSM_E_INVALID_NETWORK_HANDLE          (3U)
#define CANSM_E_PARAM_CONTROLLER                (4U)
#define CANSM_E_PARAM_TRANSCEIVER               (5U)
#define CANSM_E_NOT_IN_NO_COM                   (11U)

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
#define CANSM_INIT_API_ID                       (0U)
#define CANSM_DEINIT_API_ID                     (20U)
#define CANSM_MODEREQ_API_ID                    (2U)
#define CANSM_GETMODE_API_ID                    (3U)
#define CANSM_STARTWAKEUP_API_ID                (17U)
#define CANSM_STOPWAKEUP_API_ID                 (18U)
#define CANSM_VERSIONINFO_API_ID                (1U)
#define CANSM_SETBAUDRATE_API_ID                (13U)
#define CANSM_SETICOMCONFIG_API_ID              (15U)
#define CANSM_SETECUPASSIVE_API_ID              (19U)
#define CANSM_CONTROLLERBUSSOF_API_ID           (4U)
#define CANSM_CONTROLLERMODEIDN_API_ID          (7U)
#define CANSM_TRCMODEIND_API_ID                 (9U)
#define CANSM_TXTIMEOUTEXP_API_ID               (11U)
#define CANSM_CLRTRCV_FLAGIND_API_ID            (8U)
#define CANSM_CHECKTRCV_FLAGIND_API_ID          (10U)
#define CANSM_CONFIRM_PNAVAIL_API_ID            (6U)
#define CANSM_CURRENT_ICOMCONFIG_API_ID         (16U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
#define STD_OFF                             (0U)
#define STD_ON                              (1U)
#define NULL_PTR							((void*)0)

typedef enum
{
	CANSM_UNINITED,
	CANSM_INITED,
}CanSM_StateType;

/*******************************************************************************
 *               Dummy Function Prototypes:To be removed!                      *
 *******************************************************************************/


/*******************************************************************************
 *                          Function Prototypes                                *
 *******************************************************************************/

void CanSM_Init(
CanSM_ConfigType* ConfigPtr
);

void CanSM_DeInit(
void
);

Std_ReturnType CanSM_RequestComMode(
NetworkHandleType network,
ComM_ModeType ComM_Mode
);

Std_ReturnType CanSM_GetCurrentComMode(
NetworkHandleType network,
ComM_ModeType* ComM_ModePtr
);

Std_ReturnType CanSM_StartWakeupSource(
NetworkHandleType network
);

Std_ReturnType CanSM_StopWakeupSource(
NetworkHandleType network
);
/*******************************************************************************
 *                       Optional Function Prototypes                          *
 *******************************************************************************/
#if (CanSMVersionInfoApi==STD_ON)
void CanSM_GetVersionInfo(
Std_VersionInfoType* VersionInfo
);
#endif

#if (CanSMSetBaudrateApi==STD_ON)
Std_ReturnType CanSM_SetBaudrate(
NetworkHandleType Network,
uint16 BaudRateConfigID
);
#endif
Std_ReturnType CanSM_SetEcuPassive(
boolean CanSM_Passive
);
#if (CanSMIcomSupport==STD_ON)
Std_ReturnType CanSM_SetIcomConfiguration(
NetworkHandleType Network,
IcomConfigIdType ConfigurationId
);
#endif
#if (CanSMTxOfflineActiveSupport==STD_ON)
Std_ReturnType CanSM_SetEcuPassive(
boolean CanSM_Passive
);
#endif
/*******************************************************************************
 *                     Scheduler Function Prototype                            *
 *******************************************************************************/
void CanSM_MainFunction(
void
);

#endif

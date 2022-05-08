/******************************************************************************
 * Module: CanDriver
 *
 * File Name: Can.h
 *
 * Description: Header file for Can driver.
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */
#ifndef CAN_H_
#define CAN_H_

#define CAN_SW_MAJOR_VERSION                (1U)
#define CAN_SW_MINOR_VERSION                (0U)
#define CAN_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CAN_AR_RELEASE_MAJOR_VERSION        (4U)
#define CAN_AR_RELEASE_MINOR_VERSION        (0U)
#define CAN_AR_RELEASE_PATCH_VERSION        (3U)

#define CAN_VENDOR_ID                       (1000U)
#define CAN_MODULE_ID                       (80U)

#define CAN_INSTANCE_NUMBER                 (0U)

#define NULL_PTR							((void*)0)

#include "Can_cfg.h"

#include "Can_GeneralTypes.h"

#if(CanDevErrorDetect==STD_ON)
#include "Det.h"
#endif

typedef enum
{
    CAN_E_PARAM_POINTER,
    CAN_E_PARAM_HANDLE,
    CAN_E_PARAM_DATA_LENGTH,
    CAN_E_PARAM_CONTROLLER,
    CAN_E_UNINIT,
    CAN_E_TRANSITION,
    CAN_E_PARAM_BAUDRATE,
    CAN_E_ICOM_CONFIG_INVALID,
    CAN_E_INIT_FAILED,
} Development_Errors;

void Can_Init(Can_ConfigType* Config);

#if (CanVersionInfoApi == STD_ON)
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

void Can_DeInit(void);

#if (CanSetBaudrateApi==STD_ON)
Std_ReturnType Can_SetBaudrate(uint8 Controller,uint16 BaudRateConfigID);
#endif

void Can_DisableControllerInterrupts(uint8 Controller);

void Can_EnableControllerInterrupts(uint8 Controller);

Std_ReturnType Can_CheckWakeup(uint8 Controller);

Std_ReturnType Can_GetControllerErrorState(uint8 ControllerId,Can_ErrorStateType* ErrorStatePtr);

Std_ReturnType Can_GetControllerMode(uint8 Controller,Can_ControllerStateType* ControllerModePtr);

Std_ReturnType Can_SetControllerMode(uint8 Controller,Can_ControllerStateType Transition);

Std_ReturnType Can_Write(Can_HwHandleType Hth,const Can_PduType* PduInfo);

void Can_MainFunction_Write(void);

void Can_MainFunction_Read(void);

void Can_MainFunction_BusOff(void);

void Can_MainFunction_Wakeup(void);

void Can_MainFunction_Mode(void);

/*This feature is not exist in the ECU*/
#if(CanPublicIcomSupport==STD_ON)
Std_ReturnType Can_SetIcomConfiguration(uint8 Controller,IcomConfigIdType ConfigurationId);
#endif


#endif

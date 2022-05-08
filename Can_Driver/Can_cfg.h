/******************************************************************************
 * Module: CanDriver
 *
 * File Name: Can_cfg.h
 *
 * Description: Header file for Can driver configuration.
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */
#ifndef CAN_CFG_H_
#define CAN_CFG_H_

#define CAN_CFG_SW_MAJOR_VERSION                (1U)
#define CAN_CFG_SW_MINOR_VERSION                (0U)
#define CAN_CFG_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CAN_CFG_AR_RELEASE_MAJOR_VERSION        (4U)
#define CAN_CFG_AR_RELEASE_MINOR_VERSION        (0U)
#define CAN_CFG_AR_RELEASE_PATCH_VERSION        (3U)


#include "ComStack_Types.h"

#include "Can_PBcfg.h"

#define INTERRUPT                               (1U)
#define POLLING                                 (2U)
#define STANDARD                                (1U)
#define EXTENDED                                (2U)
#define BASIC                                   (1U)
#define FULL                                    (2U)
#define RECIVE                                  (1U)
#define TRANSMIT                                (2U)
/*********************************Pre-compile time************************/

/*******************************Can General*******************************/

/*Switches the development error detection and notification on or off.
 true: detection and notification is enabled.
 false: detection and notification is disabled*/

#define CanDevErrorDetect                       STD_OFF


/*Specifies the Instance Id of this module instance.
 If only one instance is present it shall have the Id 0.*/
#define CanIndex                                ((uint8)15u)


/*parameter defines existence and name of a call_out function which called after a successful
reception of a received CAN Rx L-PDU.If this parameter is omitted no call_out shall take place.
 */
#define CanLPduReceiveCalloutFunction           CANMessageGet

/*This parameter describes the period for cyclic call to Can_MainFunction_Busoff. Unit is seconds.*/
#define CanMainFunctionBusoffPeriod			    1

/*This parameter describes the period for cyclic call to Can_MainFunction_Mode. Unit is seconds*/
#define CanMainFunctionModePeriod		1       1

/*This parameter describes the period for cyclic call to Can_MainFunction_Wakeup. Unit is seconds*/
#define  CanMainFunctionWakeupPeriod			1

/*Specifies if multiplexed transmission shall be supported.ON or OFF*/
#define CanMultiplexedTransmission		        STD_OFF

/*Selects support of Pretended Network features in Can driver.
True: Enabled
False: Disabled*/
#define	CanPublicIcomSupport			        STD_OFF

/*The support of the Can_SetBaudrate API is optional.
If parameter is true the Can_SetBaudrate API shall be supported. Otherwise it's not supported.*/
#define CanSetBaudrateApi	                    STD_ON

/*Specifies the maximum time for blocking function until a timeout is detected. Unit is seconds.*/
#define	CanTimeoutDuration				        100//Float

/*Switches the Can_GetVersionInfo() API ON or OFF.*/
#define CanVersionInfoApi	                    STD_ON

/*This parameter contains a reference to the OsCounter, which is used by the CAN driver.*/
#define CanOsCounterRef				            ((uint32)80000000)

/*The parameter refers to CanIfSupportTTCAN parameter in the CAN Interface Module configuration*/
#define	CanSupportTTCANRef                      TRUE



/*********************CanController*******************************/

/*Enables / disables API Can_MainFunction_BusOff() for handling busoff events in polling mode.*/
#define CanBusoffProcessing			            POLLING
/*Defines if a CAN controller is used in the configuration.*/

#define	CanControllerActivation			        STD_ON

/*Specifies the CAN controller base address.*/

#define	CanControllerBaseAddress	            0x40006400/*((uint32) 0x40040000u)*/       /*CAN0: 0x40006400 CAN1: 0x40006800*/

/*This parameter provides the controller ID which is unique in a given CAN Driver.*/

#define	CanControllerId				            ((uint8)30u)

/*Enables / disables API Can_MainFunction_Read() for handling PDU reception*/

#define	CanRxProcessing				            POLLING

/*Enables / disables API Can_MainFunction_Write() for handling PDU transmission events in polling mode*/

#define	CanTxProcessing				            POLLING

/* Adds / removes the service Can_CheckWakeup() from the code.
 True: Can_CheckWakeup can be used.
 False: Can_CheckWakeup cannot be used.*/

#define CanWakeupFunctionalityAPI	            STD_ON

/*Enables / disables API Can_MainFunction_Wakeup() for handling wakeup events in polling mode.*/

#define CanWakeupProcessing				        POLLING

/*Reference to baudrate configuration container configured for the Can Controller.*/

#define	CanControllerDefaultBaudrate	        512

/*Reference to the CPU clock configuration, which is set in the MCU driver configuration*/

#define McuClockReferencePoint                  ((uint32) 80000000)
#define	CanCpuClockRef		                    McuClockReferencePoint

/*This parameter contains a reference
 to the Wakeup Source for this controller as defined in the ECU State Manager.*/

#define	CanWakeupSourceRef				        ECUM_WKSOURCE_RESET

/*********************CanHardwareObject*******************************/


/*Specifies the type (Full-CAN or Basic-CAN) of a hardware object.*/
#define CanHandleType						    BASIC

/*Enables polling of this hardware object.*/
#define CanHardwareObjectUsesPolling            FALSE

/*In case of a HRH this parameter defines the number of elements in the hardware FIFO or the number of
shadow buffers,
 in case of a HTH it defines the number of hardware objects used for multiplexed transmission */
#define CanHwObjectCount			            ((uint16)u)

/*Specifies whether the IdValue is of type
- standard identifier
- extended identifier
- mixed mode
ImplementationType: Can_IdType*/
#define CanIdType                               STANDARD
/*Holds the handle ID of Hardware recieve handel or Hardware transmite handel.*/
#define CanObjectId				                ((uint16)25u)

/*Specifies if the HardwareObject is used as Transmit or as Receive object*/
#define	CanObjectType						    RECEIVE

/*This parameter defines if or if not Can supports the trigger-transmit API for this handle.*/
#define CanTriggerTransmitEnable			    FALSE

/*Reference to CAN Controller to which the Hardware object handle is associated to.*/
#define	CanControllerRef

/*Reference to CanMainFunctionPeriod*/
#define	CanMainFunctionRWPeriodRef
/*********************CanHwFilter*******************************/

/*Specifies (together with the filter mask) the identifiers range that passes the hardware filter.*/
#define CanHwFilterCode				            ((uint32)5u)

/*Describes a mask for hardware-based filtering of CAN identifiers. The CAN identifiers of
 incoming messages are masked with the appropriate CanFilterMaskValue. Bits holding a 0 mean don't care,
 i.e. do not compare the message's identifier in the respective bit position.
The mask shall be build by filling with leading 0.
In case of CanIdType EXTENDED or MIXED a 29 bit mask shall be build.
 In case of CanIdType STANDARD a 11 bit mask shall be build*/
#if (CanIdType == EXTENDED)
#define	CanHwFilterMask				            ((uint32)0u)
#elif (CanIdType == STANDARD)
#define CanHwFilterMask                         ((uint16)0u)
#endif


/*********************CanMainFunctionRWPeriods*******************************/

/*This parameter describes the period for cyclic call to Can_MainFunction_Read or Can_MainFunction_Write*/
#define CanMainFunctionPeriod				    ((sint32)5)


/*********************CanIcomConfig*******************************/

/*This parameter identifies the ID of the ICOM configuration.*/
#define CanIcomConfigId			                ((uint8)13U)

/*This parameter defines that the MCU shall wake if the bus off is detected or not.*/
#define	CanIcomWakeOnBusOff			            FALSE

/*********************CanIcomGeneral*******************************/
/*TODO*/
/*Defines the level of Pretended Networking.*/
#define	CanIcomLevel	                        /*enum CAN_ICOM_LEVEL_ONE,CAN_ICOM_LEVEL_TWO*/
/*TODO*/
/*Defines the variant, which is supported by this CanController*/
#define	CanIcomVariant	                        /*enum CAN_ICOM_VARIANT_HW,CAN_ICOM_VARIANT_NONE,CAN_ICOM_VARIANT_SW*/

/*********************CanIcomRxMessage*******************************/

/*defines that the MCU shall wake if the message with the ID is received n times on the communication
channel.*/
#define CanIcomCounterValue		                ((uint16)u)

/*This parameter defines the message ID the wakeup causes of this CanIcomRxMessage are configured for*/
#define CanIcomMessageId		                ((uint32)u)

/*Describes a mask for filtering of CAN identifiers.
The CAN identifiers of incoming messages are masked with this CanIcomMessageIdMask*/
#define CanIcomMessageIdMask	                ((uint32)u)

/*This parameter defines that the MCU shall wake if the message with the ID is not received for a
specific time in s on the
communication channel*/
#define CanIcomMissingMessageTimerValue			((uint16)u)

/*This parameter defines that the MCU shall wake if a payload error occurs*/
#define CanIcomPayloadLengthError               FALSE


/*********************CanIcomRxMessageSignalConfig*******************************/

/*This parameter shall be used to mask a signal in the payload of a CAN message*/
#define	CanIcomSignalMask		                ((uint64)u)

/*This parameter defines the operation, which shall be used to verify the signal value creates a wakeup
condition*/
#define CanIcomSignalOperation

/*This parameter shall be used to define a signal value which shall be compared (CanIcomSignalOperation)
with the masked*/
#define CanIcomSignalValue		                ((uint64)u)

/*This parameter defines a reference to the signal which shall be checked additional to the message id
(CanIcomMessageId).*/
#define CanIcomSignalRef		                ((uint8)0U)

/*************************Extern variables*************************/

/*****************************API IDs*****************************/

#define Can_Init_ID                             0x00
#define Can_GetVersionInfo_ID                   0x07
#define Can_DeInit_ID                           0x10
#define Can_SetBaudrate_ID                      0x0f
#define Can_SetControllerMode_ID                0x03
#define Can_DisableControllerInterrupts_ID      0x04
#define Can_EnableControllerInterrupts_ID       0x05
#define Can_CheckWakeup_ID                      0x0b
#define Can_GetControllerErrorState_ID          0x0b
#define Can_GetControllerMode_ID                0x12
#define Can_Write_ID                            0x06

#endif

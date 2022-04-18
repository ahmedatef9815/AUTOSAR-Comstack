#ifndef CANIF_H
#define CANIF_H

#include "ComStack_Types.h"


#define CANIF_AR_RELEASE_MAJOR_VERSION              (4U)
#define CANIF_AR_RELEASE_MINOR_VERSION              (0U)
#define CANIF_AR_RELEASE_PATCH_VERSION              (3U)

typedef enum
{
	CANIF_OFFLINE,
	CANIF_TX_OFFLINE,
	CANIF_TX_OFFLINE_ACTIVE,
	CANIF_ONLINE,
}CanIf_PduModeType;

typedef enum
{
	CAN_CS_UNINIT,
	CAN_CS_STARTED,
	CAN_CS_STOPPED,
	CAN_CS_SLEEP,
}Can_ControllerStateType;

typedef enum
{
	CANTRCV_TRCVMODE_SLEEP,
	CANTRCV_TRCVMODE_STANDBY,
	CANTRCV_TRCVMODE_NORMAL,
}CanTrcv_TrcvModeType;

typedef enum
{
    CANIF_NO_NOTIFICATION,
    CANIF_TX_RX_NOTIFICATION,
}CanIf_NotifStatusType;

Std_ReturnType  CanIf_SetControllerMode(uint8 Controller,Can_ControllerStateType Transition);
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId,CanIf_PduModeType PduModeRequest);
Std_ReturnType CanIf_SetTrcvMode(uint8 TransceiverId,CanTrcv_TrcvModeType TransceiverMode);
Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 TransceiverId);
Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 TransceiverId);
Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId,uint16 BaudRateConfigID);
Std_ReturnType CanIf_SetIcomConfiguration(uint8 ControllerId,IcomConfigIdType ConfigurationId);
CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 CanController);

#endif

#include "CanIF.h"
#include "BswM.h"
#include "CanNm_Cbk.h"
#include "ComStack_Types.h"
#include "Det.h"
#include "Dem.h"
#include "ComM_BusSM.h"
#include "CanSM_BswM.h"
#include "CanSM_Cfg.h"

#if (STD_ON==CanSMDevErrorDetect)
Std_ReturnType Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId)
{
    while(1)
    {
        /*Det is not implemented*/
    }
    return E_OK;
}
#endif
Std_ReturnType  CanIf_SetControllerMode(uint8 Controller,Can_ControllerStateType Transition)
{
	return E_OK;
}
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId,CanIf_PduModeType PduModeRequest)
{
	return E_OK;
}
Std_ReturnType CanIf_SetTrcvMode(uint8 TransceiverId,CanTrcv_TrcvModeType TransceiverMode)
{
	return E_OK;
}
void ComM_BusSM_ModeIndication(NetworkHandleType Channel,ComM_ModeType* ComMode)
{
	;
}
void BswM_CanSM_CurrentState(NetworkHandleType Network,CanSM_BswMCurrentStateType CurrentState)
{
	;
}
Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 TransceiverId)
{
	return E_OK;
}
Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 TransceiverId)
{
	return E_OK;
}
void CanNm_ConfirmPnAvailability(NetworkHandleType nmChannelHandle)
{
	;
}
Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId,uint16 BaudRateConfigID)
{
   return E_OK;
}
Std_ReturnType CanIf_SetIcomConfiguration(uint8 ControllerId,IcomConfigIdType ConfigurationId)
{
    return E_OK;
}
Std_ReturnType Dem_ReportErrorStatus(Dem_EventIdType EventID, uint8 EventStatus)
{
    return E_OK;
}
CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 CanController)
{
    return CANIF_NO_NOTIFICATION;
}

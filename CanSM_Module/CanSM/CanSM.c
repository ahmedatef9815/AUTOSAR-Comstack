/******************************************************************************
 * Module: CanSM
 *
 * File Name: CanSM.c
 *
 * Description: Source file for Can State Manager
 *
 * Author: Khaled Tarek
 ******************************************************************************/
#include "cansm.h"
#include "cansm_Internal.h"
#include "CanSM_Cbk.h"

#include "ComM_BusSM.h"
#if ((COMM_BUSSM_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (COMM_BUSSM_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (COMM_BUSSM_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#if (CanSMDevErrorDetect == STD_ON)
#include "Det.h"
#if ((DET_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (DET_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (DET_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif
#endif

#if (STD_ON==USE_DEM)
#include "Dem.h"
#if ((DEM_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (DEM_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (DEM_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif
#endif
#include "CanIf.h"
#if ((CANIF_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (CANIF_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (CANIF_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#include "CanSM_BswM.h"

#if (CanSMPncSupport == STD_ON)
#include "CanNm_Cbk.h"
#if ((CANNM_CBK_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (CANNM_CBK_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (CANNM_CBK_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif
#endif
#include "BswM.h"
#if ((BSWM_AR_RELEASE_MAJOR_VERSION !=CANSM_AR_RELEASE_MAJOR_VERSION)\
		|| (BSWM_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION)\
		|| (BSWM_AR_RELEASE_PATCH_VERSION != CANSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif


static CanSM_Internal_NetworkType CanSM_InternalNetworks[CANSM_NETWORK_COUNT];

static CanSM_InternalType CanSM_Internal = {
		.InitStatus = CANSM_UNINITED,
		.Networks = CanSM_InternalNetworks,
};

static const CanSM_ConfigType* CanSM_Config = NULL_PTR;

static boolean EcuPassiveStatus = FALSE;

/************************************************************************************
 * Service Name: CanSM_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr:Pointer to init structure for the post build parameters of the CanSM
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This service initializes the CanSM module
 ************************************************************************************/
void CanSM_Init(CanSM_ConfigType* ConfigPtr)
{
	CanSM_Config = ConfigPtr;
	uint8 i = 0;
	Std_ReturnType status = E_OK;
	if(ConfigPtr==NULL_PTR)
	{
	    status = E_NOT_OK;
	    #if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_INIT_API_ID,CANSM_E_PARAM_POINTER);
		#endif
	}
	if(status==E_OK)
    {
        CanSM_Config=ConfigPtr;
        for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
        {
            CanSM_Internal.Networks[i].requestedMode = COMM_SLEEP_COMMUNICATION;/*SLEEP MODE*/
        }
        CanSM_Internal.InitStatus=CANSM_INITED;
    }
}

/************************************************************************************
 * Service Name: CanSM_DeInit
 * Service ID[hex]: 0x14
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This service de-initializes the CanSM module
 ************************************************************************************/
void CanSM_DeInit(void)
{
    Std_ReturnType status = E_OK;
    uint8 i = 0;
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_DEINIT_API_ID,CANSM_E_UNINIT);
		#endif
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		if(CanSM_Internal.Networks[i].requestedMode==COMM_FULL_COMMUNICATION||
            CanSM_Internal.Networks[i].requestedMode==COMM_SILENT_COMMUNICATION)
		{
		    status = E_NOT_OK;
			#if (STD_ON==CanSMDevErrorDetect)
            Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_DEINIT_API_ID,CANSM_E_NOT_IN_NO_COM);
            #endif
		}
	}
	if(status==E_OK)
    {
        CanSM_Internal.InitStatus=CANSM_UNINITED;
    }
}

/************************************************************************************
 * Service Name: CanSM_RequestComMode
 * Service ID[hex]: 0x02
 * Sync/Async: ASynchronous
 * Reentrancy: Reentrant (only for different network handles)
 * Parameters (in): network - Handle of destined communication network for request
                    ComM_Mode - Requested communication mode
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Std_ReturnType  E_OK - Service accepted
                                 E_NOT_OK - Service denied
 * Description: This service shall change the communication mode of a CAN network to the
   requested one.
 ************************************************************************************/
Std_ReturnType CanSM_RequestComMode(NetworkHandleType network,ComM_ModeType ComM_Mode)
{
	Std_ReturnType totalStatus = E_OK;
	Std_ReturnType status = E_NOT_OK;
	Can_ControllerStateType CanIF_mode = CAN_CS_STARTED;
	CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[network];
	uint8 i = 0;
	if(EcuPassiveStatus == TRUE)
    {
        return E_NOT_OK;  /*!Comment:Can't change the status of network if the ECU inpassive MODE until
                                        CanSM_SetEcuPassive is set back or ECU Reset*/
    }
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_MODEREQ_API_ID,CANSM_E_UNINIT);
		#endif
		return E_NOT_OK;
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		if(NetworkManager->CanSMComMNetworkHandleRef==network)
		{
			status = E_OK;
			break;
		}
	}
	if(status==E_NOT_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_MODEREQ_API_ID,CANSM_E_INVALID_NETWORK_HANDLE);
		#endif
		return E_NOT_OK;
	}
	/*!Comment:CanIF Mode change based on requested comM mode*/
	switch(ComM_Mode)
	{
		case COMM_NO_COMMUNICATION:
			CanIF_mode = CAN_CS_STOPPED;
			break;
		case COMM_SILENT_COMMUNICATION:
		    if(CanSM_Internal.Networks[network].requestedMode != COMM_FULL_COMMUNICATION)
            {
                status = E_NOT_OK;      /*transaction to silent comm must done from full comm*/
            }
			CanIF_mode = CAN_CS_STARTED;
			break;
		case COMM_FULL_COMMUNICATION:
		    if(CanSM_Internal.Networks[network].requestedMode == COMM_SLEEP_COMMUNICATION)
            {
                status = E_NOT_OK;      /*transaction to CAN_CS_STARTED can't be done from CAN_CS_SLEEP*/
            }
			CanIF_mode = CAN_CS_STARTED;
			break;
	}
    if (status != E_OK) {
			return status;
		}
	status =  CanIf_SetControllerMode(NetworkManager->Controllers->CanSMControllerId,CanIF_mode);
	if (status != totalStatus) {
			totalStatus = status;
		}
	/*!Comment:CanSM moduleRequest to CanIF PDU*/
	CanIf_PduModeType channelMode = CANIF_OFFLINE;

	switch (ComM_Mode) {
		case COMM_NO_COMMUNICATION:
			channelMode = CANIF_OFFLINE;
			break;
		case COMM_SILENT_COMMUNICATION:
			channelMode = CANIF_TX_OFFLINE;
			break;
		case COMM_FULL_COMMUNICATION:
			channelMode = CANIF_ONLINE;
			break;
	}
	status = CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,channelMode);
	if (status != totalStatus) {
			totalStatus = status;
	}
	/*!Comment:set the Transceiver*/
	CanTrcv_TrcvModeType TrcvMode = CANTRCV_TRCVMODE_STANDBY;
	CanSM_BswMCurrentStateType CanSMCurrentState = CANSM_BSWM_NO_COMMUNICATION;
	switch (ComM_Mode)
	{
		case COMM_NO_COMMUNICATION:
			TrcvMode = CANTRCV_TRCVMODE_STANDBY;
			CanSMCurrentState = CANSM_BSWM_NO_COMMUNICATION;
			break;
		case COMM_SILENT_COMMUNICATION:
			TrcvMode = CANTRCV_TRCVMODE_NORMAL;
			CanSMCurrentState = CANSM_BSWM_SILENT_COMMUNICATION;
			break;
		case COMM_FULL_COMMUNICATION:
			TrcvMode = CANTRCV_TRCVMODE_NORMAL;
			CanSMCurrentState = CANSM_BSWM_FULL_COMMUNICATION;
			break;
	}
	status = CanIf_SetTrcvMode(NetworkManager->CanSMTransceiverId,TrcvMode);
	if (status != totalStatus) {
			totalStatus = status;
		}
	if(totalStatus==E_OK)
	{
		BswM_CanSM_CurrentState(network,CanSMCurrentState);
		ComM_BusSM_ModeIndication(network, &ComM_Mode);
		CanSM_Internal.Networks[network].requestedMode = ComM_Mode;
	}
	return totalStatus;
}
/************************************************************************************
 * Service Name: CanSM_GetCurrentComMode
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): network - Network handle, whose current communication mode shall be put out
 * Parameters (inout): None
 * Parameters (out): ComM_ModePtr - Pointer, where to put out the current communication mode
 * Return value: Std_ReturnType E_OK - Service accepted
                                E_NOT_OK - Service denied
 * Description: This service shall put out the current communication mode of a CAN network.
 ************************************************************************************/
Std_ReturnType CanSM_GetCurrentComMode(NetworkHandleType network,ComM_ModeType* ComM_ModePtr)
{
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[network];
	uint8 i = 0;
	if(ComM_ModePtr==NULL_PTR)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_GETMODE_API_ID,CANSM_E_PARAM_POINTER);
		#endif
		return E_NOT_OK;
	}
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_GETMODE_API_ID,CANSM_E_UNINIT);
		#endif
		return E_NOT_OK;
	}
	Std_ReturnType status = E_NOT_OK;
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		if(NetworkManager->CanSMComMNetworkHandleRef==network)
		{
			status = E_OK;
			break;
		}
	}
	if(status==E_NOT_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_GETMODE_API_ID,CANSM_E_INVALID_NETWORK_HANDLE);
		#endif
	}
	if(status==E_OK)
    {
        *ComM_ModePtr=CanSM_Internal.Networks[network].requestedMode;
    }
	return status;
}

/************************************************************************************
 * Service Name: CanSM_StartWakeupSource
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Std_ReturnType E_OK - Service accepted
                                E_NOT_OK - Service denied
 * Description: This function shall be called by EcuM when a wakeup source shall be started.
 ************************************************************************************/
Std_ReturnType CanSM_StartWakeupSource(NetworkHandleType network)
{
	Std_ReturnType totalStatus = E_OK;
	Std_ReturnType status = E_OK;
	boolean flag = FALSE;
	uint8 i = 0;
	if(CanSM_Internal.Networks[network].requestedMode != COMM_SLEEP_COMMUNICATION)
    {
        status = E_NOT_OK;
    }
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_STARTWAKEUP_API_ID,CANSM_E_UNINIT);
		#endif
		status = E_NOT_OK;
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
        CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMComMNetworkHandleRef==network)
		{
			flag = TRUE;
			break;
		}
	}
	if(flag==FALSE)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_STARTWAKEUP_API_ID,CANSM_E_INVALID_NETWORK_HANDLE);
		#endif
		status = E_NOT_OK;
	}
	if(status!=totalStatus)
    {
        totalStatus=status;
    }
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[network];
    if(status==E_OK)
    {
        status =  CanIf_SetControllerMode(NetworkManager->Controllers->CanSMControllerId,CAN_CS_STOPPED);
    }
	if (status != totalStatus) {
			totalStatus = status;
	}
	status = CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_OFFLINE);
	if (status != totalStatus) {
			totalStatus = status;
	}
	status = CanIf_SetTrcvMode(NetworkManager->CanSMTransceiverId,CANTRCV_TRCVMODE_STANDBY);
	if (status != totalStatus) {
			totalStatus = status;
		}
    ComM_ModeType ComM_Mode = COMM_NO_COMMUNICATION;
	if(totalStatus==E_OK)
	{
		BswM_CanSM_CurrentState(network,CANSM_BSWM_NO_COMMUNICATION);
		ComM_BusSM_ModeIndication(network, &ComM_Mode);
		CanSM_Internal.Networks[network].requestedMode = ComM_Mode;
	}
	return totalStatus;
}
/************************************************************************************
 * Service Name: CanSM_StopWakeupSource
 * Service ID[hex]: 0x12
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Std_ReturnType E_OK - Service accepted
                                E_NOT_OK - Service denied
 * Description: This function shall be called by EcuM when a wakeup source shall be stopped.
 ************************************************************************************/
Std_ReturnType CanSM_StopWakeupSource(NetworkHandleType network)
{
	Std_ReturnType totalStatus = E_OK;
	Std_ReturnType status = E_OK;
	boolean flag = FALSE;
	uint8 i = 0;
	if(CanSM_Internal.Networks[network].requestedMode != COMM_NO_COMMUNICATION)
    {
        status = E_NOT_OK;
    }
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_STARTWAKEUP_API_ID,CANSM_E_UNINIT);
		#endif
		status = E_NOT_OK;
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
	    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMComMNetworkHandleRef==network)
		{
			flag = TRUE;
			break;
		}
	}
	if(flag==FALSE)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_STARTWAKEUP_API_ID,CANSM_E_INVALID_NETWORK_HANDLE);
		#endif
		status = E_NOT_OK;
	}
	if(status!=totalStatus)
    {
        totalStatus=status;
    }
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[network];
    if(CanSM_Internal.Networks[network].requestedMode !=COMM_NO_COMMUNICATION)
    {
        return E_NOT_OK;            /*Only transaction to sleep state takes place from stopped an no communication */
    }
	if(status == E_OK)
    {
        status =  CanIf_SetControllerMode(NetworkManager->Controllers->CanSMControllerId,CAN_CS_SLEEP);
    }
	if (status != totalStatus) {
			totalStatus = status;
	}
	status = CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_OFFLINE);
	if (status != totalStatus) {
			totalStatus = status;
	}
	status = CanIf_SetTrcvMode(NetworkManager->CanSMTransceiverId,CANTRCV_TRCVMODE_SLEEP);
	if (status != totalStatus) {
			totalStatus = status;
		}
    ComM_ModeType ComM_Mode = COMM_SLEEP_COMMUNICATION;
	if(totalStatus==E_OK)
	{
		BswM_CanSM_CurrentState(network,CANSM_BSWM_NO_COMMUNICATION);
		ComM_BusSM_ModeIndication(network, &ComM_Mode);
		CanSM_Internal.Networks[network].requestedMode = ComM_Mode;
	}
	return totalStatus;
}
/************************************************************************************
 * Service Name: CanSM_GetVersionInfo
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: This service puts out the version information of this module (module ID, vendor ID,
   vendor specific version numbers related to BSW00407)
 ************************************************************************************/
#if (CanSMVersionInfoApi==STD_ON)
void CanSM_GetVersionInfo(Std_VersionInfoType* VersionInfo)
{
    #if (CanSMDevErrorDetect==STD_ON)
        if(CanSM_Internal.InitStatus!=CANSM_INITED)
        {
            Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_VERSIONINFO_API_ID,CANSM_E_UNINIT);
        }
        if(VersionInfo==NULL_PTR)
        {
            Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_VERSIONINFO_API_ID,CANSM_E_PARAM_POINTER);
        }
    #endif
    VersionInfo->vendorID = CANSM_VENDOR_ID;
    VersionInfo->moduleID = CANSM_MODULE_ID;
    VersionInfo->sw_major_version = CANSM_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = CANSM_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = CANSM_SW_PATCH_VERSION;
}
#endif
/************************************************************************************
 * Service Name: CanSM_SetBaudrate
 * Service ID[hex]: 0x0D
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant for different Networks. Non reentrant for the same Network.
 * Parameters (in): Network - Handle of the addressed CAN network for the baud rate change.
                    BaudRateConfigID -  references a baud rate configuration by ID (see CanControllerBaudRateConfigID)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Std_ReturnType E_OK - Service accepted
                                E_NOT_OK - Service denied
 * Description: This service shall start an asynchronous process to change the baud rate for the
   configured CAN controllers of a certain CAN network. Depending on necessary
   baud rate modifications the controllers might have to reset.
 ************************************************************************************/
#if (CanSMSetBaudrateApi==STD_ON)
Std_ReturnType CanSM_SetBaudrate(NetworkHandleType Network,uint16 BaudRateConfigID)
{
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[Network];
    Std_ReturnType status = E_NOT_OK;
    Std_ReturnType Commstatus = E_NOT_OK;
    uint8 i=0;
    for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		if(NetworkManager->CanSMComMNetworkHandleRef==Network)
		{
			status = E_OK;
			break;
		}
	}
	if(CanSM_Internal.Networks[Network].requestedMode==COMM_FULL_COMMUNICATION)
    {
        Commstatus=E_OK;
    }
    #if (CanSMDevErrorDetect==STD_ON)
        if(CanSM_Internal.InitStatus!=CANSM_INITED)
        {
            Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_VERSIONINFO_API_ID,CANSM_E_UNINIT);
        }
        if(status==E_NOT_OK)
        {
            Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_VERSIONINFO_API_ID,CANSM_E_INVALID_NETWORK_HANDLE);
        }
    #endif
    if(status == E_OK)
    {
        status=CanIf_SetBaudrate(NetworkManager->Controllers->CanSMControllerId,BaudRateConfigID);
    }
    if(Commstatus!=E_OK)
    {
        status = Commstatus;
    }
    return status;
}
#endif
/************************************************************************************
 * Service Name: CanSM_SetIcomConfiguration
 * Service ID[hex]: 0x0F
 * Sync/Async: Asynchronous
 * Reentrancy: Reentrant only for different network handles
 * Parameters (in): Network - Handle of destined communication network for request
                    ConfigurationId - Requested Configuration
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Std_ReturnType E_OK - Service accepted
                                E_NOT_OK - Service denied
 * Description: This service shall change the Icom Configuration of a CAN network to the
                requested one.
 ************************************************************************************/
 #if (CanSMIcomSupport==STD_ON)
Std_ReturnType CanSM_SetIcomConfiguration(NetworkHandleType Network,IcomConfigIdType ConfigurationId)
{
    Std_ReturnType status = E_NOT_OK;
    Std_ReturnType Networkstatus = E_NOT_OK;
    boolean flag = FALSE;
    uint8 i = 0;
    for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
	    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMComMNetworkHandleRef==Network)
		{
			flag = TRUE;
			break;
		}
	}
	if(flag==FALSE)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_SETICOMCONFIG_API_ID,CANSM_E_INVALID_NETWORK_HANDLE);
		#endif
		Networkstatus = E_NOT_OK;
	}
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[Network];
    status=CanIf_SetIcomConfiguration(NetworkManager->Controllers->CanSMControllerId,ConfigurationId);
    if(status!=Networkstatus)
    {
        status = E_NOT_OK;
    }
    return status;
}
#endif
/************************************************************************************
 * Service Name: CanSM_SetEcuPassive
 * Service ID[hex]: 0x13
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): CanSM_Passive TRUE - set all CanSM channels to passive, i.e. receive only  FALSE - set all CanSM channels back to non-passive
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Std_ReturnType E_OK - Request accepted  E_NOT_OK - Request not accepted
 * Description: This function can be used to set all CanSM channels of the ECU to a receive only
   mode. This mode will be kept either until it is set back, or the ECU is reset.
 ************************************************************************************/
#if (CanSMTxOfflineActiveSupport==STD_ON)
Std_ReturnType CanSM_SetEcuPassive(boolean CanSM_Passive)
{
    Std_ReturnType status = E_NOT_OK;
    Std_ReturnType totalStatus = E_OK;
    uint8 i = 0;
    CanIf_PduModeType channelMode = CANIF_ONLINE;
    if(CanSM_Passive == TRUE)
    {
        channelMode=CANIF_TX_OFFLINE;
    }
    for(i=0;i<CANSM_NETWORK_COUNT;++i)
    {
        CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
        status = CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,channelMode);
        if(status == E_NOT_OK)
        {
            totalStatus = E_NOT_OK;
        }
    }
    if(totalStatus==E_OK&&CanSM_Passive == TRUE)
    {
        EcuPassiveStatus = TRUE;
    }
    if(totalStatus==E_OK&&CanSM_Passive == FALSE)
    {
        EcuPassiveStatus = FALSE;
    }
    return totalStatus;
}
#endif
/*******************************************************************************
 *                              Call-Back APIs                                 *
 *******************************************************************************/


/************************************************************************************
 * Service Name: CanSM_ControllerBusOff
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant (only for different CanControllers)
 * Parameters (in): ControllerId - CAN controller, which detected a bus-off event
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This callback function notifies the CanSM about a bus-off event on a certain CAN
   controller, which needs to be considered with the specified bus-off recovery handling for the
   impacted CAN network.
 ************************************************************************************/
void CanSM_ControllerBusOff(uint8 ControllerId)
{
	Std_ReturnType status = E_NOT_OK;
	uint8 i = 0;
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CONTROLLERBUSSOF_API_ID,CANSM_E_UNINIT);
		#endif
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		boolean flage = FALSE;
		CanSMManagerNetwork* Network = &CanSM_Config->Network[i];
		CanSMController* ptrController = Network->Controllers;
			if(ptrController->CanSMControllerId==ControllerId)
			{
				flage = TRUE;
				status = E_OK;
			}
		if(flage==TRUE)
		{
			CanSM_Internal.Networks[i].busoffevent = TRUE;
			BswM_CanSM_CurrentState(Network->CanSMComMNetworkHandleRef,CANSM_BSWM_BUS_OFF);
		}
		flage=FALSE;
	}
	if(status != E_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CONTROLLERBUSSOF_API_ID,CANSM_E_PARAM_CONTROLLER);
		#endif
	}

}
/************************************************************************************
 * Service Name: CanSM_ControllerModeIndication
 * Service ID[hex]: 0x7
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant (only for different CanControllers)
 * Parameters (in): ControllerId - CAN controller, whose mode has changed
                    ControllerMode - Notified CAN controller mode
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This callback shall notify the CanSM module about a CAN controller mode
   change.
 ************************************************************************************/
void CanSM_ControllerModeIndication(uint8 ControllerId,Can_ControllerStateType ControllerMode)
{
	Std_ReturnType status = E_NOT_OK;
	uint8 i = 0;
	uint16 ctr = 0;
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		CanSMManagerNetwork* Network = &CanSM_Config->Network[i];
		CanSMController* ptrController = Network->Controllers;
		if(ptrController->CanSMControllerId==ControllerId)
		{
				ctr=i;
				status = E_OK;
		}
	}
	if(status==E_OK)
		{
		switch(ControllerMode)
		{
			case CAN_CS_UNINIT:
				break;
			case CAN_CS_STARTED:
				CanSM_Internal.Networks[ctr].requestedMode=COMM_FULL_COMMUNICATION;
				break;
			case CAN_CS_SLEEP:
				CanSM_Internal.Networks[ctr].requestedMode=COMM_SLEEP_COMMUNICATION;
				break;
			case CAN_CS_STOPPED:
				CanSM_Internal.Networks[ctr].requestedMode=COMM_NO_COMMUNICATION;
				break;
		}
	}
	if(status == E_NOT_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CONTROLLERMODEIDN_API_ID,CANSM_E_PARAM_CONTROLLER);;
		#endif
	}
}
/************************************************************************************
 * Service Name: CanSM_TransceiverModeIndication
 * Service ID[hex]: 0x09
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant for different CAN Transceivers
 * Parameters (in): TransceiverId - CAN transceiver, whose mode has changed
                    TransceiverMode - Notified CAN transceiver mode
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This callback shall notify the CanSM module about a CAN transceiver mode change.
 ************************************************************************************/
void CanSM_TransceiverModeIndication(uint8 TransceiverId,CanTrcv_TrcvModeType TransceiverMode)
{
	Std_ReturnType status = E_NOT_OK;
	uint8 i = 0;
	for(i=0;i<CANSM_NETWORK_COUNT;i++)
	{
		CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMTransceiverId == TransceiverId)
		{
			switch(TransceiverMode)
			{
				case CANTRCV_TRCVMODE_NORMAL:
					CanSM_Internal.Networks[i].requestedMode = COMM_FULL_COMMUNICATION;
					break;
				case CANTRCV_TRCVMODE_SLEEP:
					CanSM_Internal.Networks[i].requestedMode = COMM_SLEEP_COMMUNICATION;
					break;
				case CANTRCV_TRCVMODE_STANDBY:
					CanSM_Internal.Networks[i].requestedMode = COMM_NO_COMMUNICATION;
					break;
			}
			status=E_OK;
		}
	}
	if(status != E_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_TRCMODEIND_API_ID,CANSM_E_PARAM_TRANSCEIVER);
		#endif
	}
}

/************************************************************************************
 * Service Name: CanSM_TxTimeoutException
 * Service ID[hex]: 0x0B
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Channel - Affected can network
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This function shall notify the CanSM module, that the CanNm has detected for the
   affected partial CAN network a tx timeout exception, which shall be recovered within the
   respective network state machine of the CanSM module.
 ************************************************************************************/
 /*
 `  Probably not good
 */
void CanSM_TxTimeoutException(NetworkHandleType Channel)
{
	Std_ReturnType status = E_OK;
	boolean flag = FALSE;
	CanIf_NotifStatusType TxStatus = CANIF_NO_NOTIFICATION;
	uint8 i = 0;
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_TXTIMEOUTEXP_API_ID,CANSM_E_UNINIT);
		#endif
		status = E_NOT_OK;
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
	    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMComMNetworkHandleRef==Channel)
		{
			flag = TRUE;
			break;
		}
	}
	CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[Channel];
	if(flag==FALSE)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_TXTIMEOUTEXP_API_ID,CANSM_E_INVALID_NETWORK_HANDLE);
		#endif
		status = E_NOT_OK;
	}
    TxStatus = CanIf_GetTxConfirmationState(NetworkManager->Controllers->CanSMControllerId);
    /*!Comment i think it should call CanIf_GetTxConfirmationState in a given time CanSMBorTimeTxEnsured but to make this happen
     *it should use OS
    */
    if(status==E_OK&&TxStatus == CANIF_NO_NOTIFICATION)
    {
        CanSM_Internal.Networks[Channel].busoffevent=TRUE;
    }
}

/************************************************************************************
 * Service Name: CanSM_ClearTrcvWufFlagIndication
 * Service ID[hex]: 0x08
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant for different CAN Transceivers
 * Parameters (in): Transceiver - Requested Transceiver
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This callback function shall indicate the CanIf_ClearTrcvWufFlag API process end
   for the notified CAN Transceiver.
 ************************************************************************************/
void CanSM_ClearTrcvWufFlagIndication(uint8 Transceiver)
{
	Std_ReturnType status = E_NOT_OK;
	uint8 i = 0;
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CLRTRCV_FLAGIND_API_ID,CANSM_E_UNINIT);
		#endif
		return;
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMTransceiverId == Transceiver)
		{
			status = E_OK;
		}
	}
	if(status!=E_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CLRTRCV_FLAGIND_API_ID,CANSM_E_PARAM_TRANSCEIVER);
		#endif
		return;
	}
	if(status == E_OK)
    {
        CanIf_ClearTrcvWufFlag(Transceiver);
    }
}
/************************************************************************************
 * Service Name: CanSM_CheckTransceiverWakeFlagIndication
 * Service ID[hex]: 0x0A
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant for different CAN Transceivers
 * Parameters (in): Transceiver - Requested Transceiver
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This callback function indicates the CanIf_CheckTrcvWakeFlag API process end
   for the notified CAN Transceiver.
 ************************************************************************************/
void CanSM_CheckTransceiverWakeFlagIndication(uint8 Transceiver)
{
	Std_ReturnType status = E_NOT_OK;
	uint8 i = 0;
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CHECKTRCV_FLAGIND_API_ID,CANSM_E_UNINIT);
		#endif
		return;
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMTransceiverId == Transceiver)
		{
			status = E_OK;
		}
	}
	if(status!=E_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CHECKTRCV_FLAGIND_API_ID,CANSM_E_PARAM_TRANSCEIVER);
		#endif
	}
	if(status==E_OK)
    {
        CanIf_CheckTrcvWakeFlag(Transceiver);
    }
}
/************************************************************************************
 * Service Name: CanSM_ConfirmPnAvailability
 * Service ID[hex]: 0x06
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): : TransceiverId - CAN transceiver, which was checked for PN availability
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: This callback function indicates that the transceiver is running in PN
   communication mode
 ************************************************************************************/
void CanSM_ConfirmPnAvailability(uint8 TransceiverId)
{
	Std_ReturnType status = E_NOT_OK;
	uint8 i = 0;
	uint8 ctr = 0;
	if (CanSM_Internal.InitStatus!=CANSM_INITED)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CONFIRM_PNAVAIL_API_ID,CANSM_E_UNINIT);
		#endif
		return;
	}
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i)
	{
		CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[i];
		if(NetworkManager->CanSMTransceiverId == TransceiverId)
		{
			ctr = i;
			status = E_OK;
		}
	}
	if(status!=E_OK)
	{
		#if (STD_ON==CanSMDevErrorDetect)
		Det_ReportError(CANSM_MODULE_ID,CANSM_INSTANCE_NUMBER,CANSM_CONFIRM_PNAVAIL_API_ID,CANSM_E_PARAM_TRANSCEIVER);
		#endif
		return;
	}
	CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[ctr];
	#if (CanSMPncSupport == STD_ON)
	CanNm_ConfirmPnAvailability(NetworkManager->CanSMComMNetworkHandleRef);
	#endif
}
/*Implementation of CanSM_CurrentIcomConfiguration*/

static void CanSM_Internal_CANSM_BOR_IDLE(NetworkHandleType NetworkHandle)
{
	CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[NetworkHandle];
	Network->counter = 0;
	Network->timer = 0;
	Network->BusOffRecoveryState = CANSM_BOR_CHECK;
}

static void CanSM_Internal_CANSM_BOR_CHECK(NetworkHandleType NetworkHandle)
{
	CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[NetworkHandle];
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[NetworkHandle];
	Network->timer++;
	if(Network->busoffevent){
		Network->busoffevent = FALSE;
		Network->timer = 0;
		Network->BusOffRecoveryState = CANSM_BOR_TXOFF_L1;
		/* Restart CAN*/
		CanIf_SetControllerMode(NetworkManager->Controllers->CanSMControllerId,CAN_CS_STARTED);
		/* Tx offline*/
		CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_TX_OFFLINE);
	}
	else if(Network->timer >= NetworkManager->CanSMBorTimeTxEnsured){
        #if(USE_DEM==STD_ON)
		Dem_ReportErrorStatus(NetworkManager->CanSMBusOffDemEvent, DEM_EVENT_STATUS_PASSED);
        #endif
		Network->BusOffRecoveryState = CANSM_BOR_NO_BUS_OFF;
	}
}

static void CanSM_Internal_CANSM_BOR_NO_BUS_OFF(NetworkHandleType NetworkHandle)
{
	CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[NetworkHandle];
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[NetworkHandle];
	if(Network->busoffevent){
		Network->busoffevent = FALSE;
		Network->BusOffRecoveryState = CANSM_BOR_TXOFF_L1;
		/* Restart CAN*/
		CanIf_SetControllerMode(NetworkManager->Controllers->CanSMControllerId,CAN_CS_STARTED);
		/* Tx offline*/
		CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_TX_OFFLINE);
	}
}
static void CanSM_Internal_CANSM_BOR_TXOFF_L1(NetworkHandleType NetworkHandle)
{
	CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[NetworkHandle];
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[NetworkHandle];
	Network->timer++;
    if(Network->timer >= NetworkManager->CanSMBorTimeL1){
		Network->timer = 0;
		Network->BusOffRecoveryState = CANSM_BOR_CHECK_L1;
		/*inc busoff counter*/
		Network->counter++;
    	/*Try starting Tx again*/
		CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_ONLINE);
	}
}
static void CanSM_Internal_CANSM_BOR_CHECK_L1(NetworkHandleType NetworkHandle)
{
	CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[NetworkHandle];
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[NetworkHandle];
	Network->timer++;
	if(Network->busoffevent){
		Network->busoffevent = FALSE;
		Network->timer = 0;
		if(Network->counter >= CanSM_Config->Network[NetworkHandle].CanSMBorCounterL1ToL2){
			Network->BusOffRecoveryState = CANSM_BOR_TXOFF_L2;
		}else{
			Network->BusOffRecoveryState = CANSM_BOR_TXOFF_L1;
		}

		/* Restart CAN*/
		CanIf_SetControllerMode(NetworkManager->Controllers->CanSMControllerId,CAN_CS_STARTED);
		/* Tx offline*/
		CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_TX_OFFLINE);
	}
	else if(Network->timer >= CanSM_Config->Network[NetworkHandle].CanSMBorTimeTxEnsured){
		/* clear busoff counter*/
		Network->counter = 0;

        #if(USE_DEM==STD_ON)
		Dem_ReportErrorStatus(CanSM_Config->Network[NetworkHandle].CanSMBusOffDemEvent,  DEM_EVENT_STATUS_PASSED);
        #endif
		Network->BusOffRecoveryState = CANSM_BOR_NO_BUS_OFF;
	}
}
static void CanSM_Internal_CANSM_BOR_TXOFF_L2(NetworkHandleType NetworkHandle)
{
	CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[NetworkHandle];
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[NetworkHandle];
	Network->timer++;
    if(Network->timer >= CanSM_Config->Network[NetworkHandle].CanSMBorTimeL2){
		Network->timer = 0;
		Network->BusOffRecoveryState = CANSM_BOR_CHECK_L2;
		/* inc busoff counter*/
		Network->counter++;
    	/*Try starting Tx again*/
		CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_ONLINE);
	}
}

static void CanSM_Internal_CANSM_BOR_CHECK_L2(NetworkHandleType NetworkHandle)
{
	CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[NetworkHandle];
    CanSMManagerNetwork* NetworkManager = &CanSM_Config->Network[NetworkHandle];
	Network->timer++;
	if(Network->busoffevent){
		Network->busoffevent = FALSE;
		Network->timer = 0;
        Network->BusOffRecoveryState = CANSM_BOR_TXOFF_L2;
		/* Restart CAN*/
		CanIf_SetControllerMode(NetworkManager->Controllers->CanSMControllerId,CAN_CS_STARTED);
		/* Tx offline*/
		CanIf_SetPduMode(NetworkManager->Controllers->CanSMControllerId,CANIF_TX_OFFLINE);
	}
	else if(Network->timer >= NetworkManager->CanSMBorTimeTxEnsured){
		/* clear busoff counter */
		Network->counter = 0;
#if(USE_DEM==STD_ON)
		Dem_ReportErrorStatus(NetworkManager->CanSMBusOffDemEvent,  DEM_EVENT_STATUS_PASSED);
#endif
		Network->BusOffRecoveryState = CANSM_BOR_NO_BUS_OFF;
	}
}
/************************************************************************************
 * Service Name: CanSM_MainFunction
 * Service ID[hex]: 0x05
 * Description: Scheduled function of the CanSM.
 ************************************************************************************/
 /*
    NOT TESTED
 */
void CanSM_MainFunction(void)
{
    uint8 i= 0;
	for (i = 0; i < CANSM_NETWORK_COUNT; ++i) {
		CanSM_Internal_NetworkType *Network = &CanSM_Internal.Networks[i];
		/*Always goto IDLE if no com ordered*/
		if(Network->requestedMode == COMM_NO_COMMUNICATION){
			Network->BusOffRecoveryState = CANSM_BOR_IDLE;
		}
		else
		{
			/*Handle bus off recovery state machine*/
			switch(Network->BusOffRecoveryState)
			{
			case CANSM_BOR_IDLE:
				CanSM_Internal_CANSM_BOR_IDLE(i);
				break;
			case CANSM_BOR_CHECK:
				CanSM_Internal_CANSM_BOR_CHECK(i);
				break;
			case CANSM_BOR_NO_BUS_OFF:
				CanSM_Internal_CANSM_BOR_NO_BUS_OFF(i);
				break;
			case CANSM_BOR_TXOFF_L1:
				CanSM_Internal_CANSM_BOR_TXOFF_L1(i);
				break;
			case CANSM_BOR_CHECK_L1:
				CanSM_Internal_CANSM_BOR_CHECK_L1(i);
				break;
			case CANSM_BOR_TXOFF_L2:
				CanSM_Internal_CANSM_BOR_TXOFF_L2(i);
				break;
			case CANSM_BOR_CHECK_L2:
				CanSM_Internal_CANSM_BOR_CHECK_L2(i);
				break;
			default:
				break;
			}
		}
	}
}

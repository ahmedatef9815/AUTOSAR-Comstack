 /******************************************************************************
 *
 * Module: PduR
 *
 * File Name: PduR_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for  PduR Module
 ******************************************************************************/

#ifndef  PDUR_CFG_H
#define  PDUR_CFG_H
/*                                 Pre-compile                                           */

/**************************************************************************************************
**
Name:                       PduRCancelReceive
Type:                       EcucBooleanParamDef
Description:                Specifies if the Transport protocol module supports the CancelReceive
                            API or not. Value true the API is supported.
                        		**
**************************************************************************************************/
#define PduRCancelReceive                STD_ON

/**************************************************************************************************
**
Name:                       PduRCancelTransmit
Type:                       EcucBooleanParamDef
Description:               Specifies if the BSW module supports the CancelTransmit API or not.
                            Value true the API is supported.
                        		**
**************************************************************************************************/
#define PduRCancelTransmit               STD_ON
/**************************************************************************************************
**
Name:                       PduRCopyRxData
Type:                       EcucBooleanParamDef
Description:               Specifies if the Transport protocol module supports the CopyRxData
                           API or not. Value true the API is supported.
                        		**
**************************************************************************************************/
#define PduRCopyRxData               STD_ON
/**************************************************************************************************
**
Name:                       PduRCopyTxData
Type:                       EcucBooleanParamDef
Description:                Specifies if the Transport protocol module supports the CopyTxData
                            API or not. Value true the API is supported.
                        		**
**************************************************************************************************/
#define PduRCopyTxData              STD_ON
/**************************************************************************************************
**
Name:                       PduRDevErrorDetect 
Type:                       EcucBooleanParamDef
Description:               Switches the development error detection and notification on or off.
                           • true: detection and notification is enabled.
                           • false: detection and notification is disabled.
                        		**
**************************************************************************************************/

#define PduRDevErrorDetect    STD_OFF

/**************************************************************************************************
**
Name:                       PduRLowerModule
Type:                       EcucBooleanParamDef
Description:                The PduRLowerModule will decide who will call the APIs and who will
                            implement the APIs.
                        		**
**************************************************************************************************/
#define PduRLowerModule              STD_ON
/**************************************************************************************************
**
Name:                       PduRRetransmission 
Type:                       EcucBooleanParamDef
Description:                If set to true this means that the destination transport protocol module
                            will use the retransmission feature. This parameter might be set to
                            false if the retransmission feature is not used, even though the
                            destination transport protocol is supporting it
                        		**
**************************************************************************************************/
#define PduRRetransmission               STD_ON
/**************************************************************************************************
**
Name:                       PduRRxIndication 
Type:                       EcucBooleanParamDef
Description:               Specifies if BSW module supports the RxIndication API or not. Value
                           true the API is supported..
                        		**
**************************************************************************************************/
#define PduRRxIndication               STD_ON

/**************************************************************************************************
**
Name:                       PduRStartOfReception
Type:                       EcucBooleanParamDef
Description:                Specifies if the Transport protocol module supports the
                            StartOfReception API or not. Value true the API is supported.
                        		**
**************************************************************************************************/
#define PduRStartOfReception              STD_ON
/**************************************************************************************************
**
Name:                       PduRTpTransmit
Type:                       EcucBooleanParamDef
Description:                Specifies if BSW module supports the TP Transmit API or not. Value
                            true the API is supported.

                        		**
**************************************************************************************************/
#define PduRTpTransmit              STD_ON
/**************************************************************************************************
**
Name:                       PduRTpTxConfirmation
Type:                       EcucBooleanParamDef
Description:                Specifies if the Transport protocol module supports the
                            TpTxConfirmation API or not. Value true the API is supported.
                        		**
**************************************************************************************************/
#define PduRTpTxConfirmation           STD_ON
/**************************************************************************************************
**
Name:                       PduRTransportProtocol
Type:                       EcucBooleanParamDef
Description:                The PDU Router module shall use the API parameters specified for
                            transport protocol interface.
                        		**
**************************************************************************************************/
#define PduRTransportProtocol          STD_ON
/**************************************************************************************************
**
Name:                       PduRUpperModule
Type:                       EcucBooleanParamDef
Description:                The PduRUpperModule will decide who will call the APIs and who will
                            implement the APIs.                        		**
**************************************************************************************************/
#define PduRUpperModule         STD_ON
/**************************************************************************************************
**
Name:                       PduRUseTag
Type:                       EcucBooleanParamDef
Description:                This parameter, if set to true, enables the usage of the tag (<up>) in the    
                            following API calls:
                            • PduR_<Up>CancelReceive
                            • PduR_<Up>CancelTransmit
                        		**
**************************************************************************************************/
#define  PduRUseTag         STD_ON

/**************************************************************************************************
**
Name:                       PduRDestPduHandleId
Type:                       EcucIntegerParamDef
Description:               PDU identifier assigned by PDU Router. Used by communication
                           interface and transport protocol modules for confirmation
                           (PduR_<Lo>TxConfirmation) and for TriggerTransmit
                           (PduR_<Lo>TriggerTransmit)													**
**************************************************************************************************/
#define PduRDestPduHandleId	uint16
/**************************************************************************************************
**
Name:                       PduRSrcPduUpTxConf 
Type:                       EcucBooleanParamDef
Description:                When enabled, the TxConfirmation will be forwarded to the upper layer.
                            Prerequisites: Lower layer and upper layer support TxConfirmation
                        		**
**************************************************************************************************/
//#define  PduRSrcPduUpTxConf          STD_ON

/**************************************************************************************************
**
Name:                       PduRSrcPduRef 
Type:                       EcucBooleanParamDef
Description:               Source PDU reference; reference to unique PDU identifier which shall
                           be used for the requested PDU Router operation.
                        		**
**************************************************************************************************/
#define   PduRSrcPduRef              (uint8*)
/**************************************************************************************************
**
Name:                       PduRTxConfirmation
Type:                       EcucIntegerParamDef
Description:                Maximum number of RoutingPaths in all RoutingTables. This parameter is
							needed only in case of post-build loadable implementation using static
							memory allocation.													**
**************************************************************************************************/
#define PduRMaxRoutingPathCnt	(uint16)2


#endif /* PDUR_CFG_H */

 /******************************************************************************
 *
 * Module:PduR
 *
 * File Name: PduR_PBcfg.c
 *
 * Description: Post Build Configuration Source file for  PduR module
 ******************************************************************************/

/******************************************************************************************************************************
 **                                                     Includes                                                             **
 ******************************************************************************************************************************/
 #include "PduR.h"

 /*****************************************************************************************************************************
  **                      					Post-Build Configuration                                        **
  *****************************************************************************************************************************/
/* routing table for PduR from upper layer to lower layer and vis */
  PduR_PBConfigType PduR =
{
	.PduRRoutingPaths=
	{
			.PduRRoutingPath=
				{
					{/*from com to cantp*/
						.PduRDestPdu=
						{
							
								
						    .PduRDestPduHandleId=0,
								
							
						},
						.PduRSrcPdu=
						{
							.PduRSourcePduHandleId=0,
							.PduRSrcPduUpTxConf=TRUE 
						}
					},
					{/*from cantp to com*/ 
						.PduRDestPdu=
						{
							
								
						    .PduRDestPduHandleId=1,
								
							
						},
						.PduRSrcPdu=
						{
								.PduRSourcePduHandleId=1,
								.PduRSrcPduUpTxConf=TRUE 
						}
					}
				}
			
		
	}
};
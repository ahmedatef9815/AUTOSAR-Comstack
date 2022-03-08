/******************************************************************************
 *
 * Module: Common - Platform
 *
 * File Name: ComStack_Types.h
 *
 * Description: General type definitions
 *
 *******************************************************************************/
#ifndef ComStack_TYPES_H
#define ComStack_TYPES_H
/***************************************************************************************************
**                                          Includes                                             **
***************************************************************************************************/
#include "Std_Types.h"
/***************************************************************************************************
**                                        Types  definitions                                 **
***************************************************************************************************/

/**************************************************************************************************
**
Name:                                    PduIdType
Type:                                     uint8, uint16
Description:  This type is used within the entire AUTOSAR Com Stack except for bus drivers
                     
																				                **
**************************************************************************************************/
typedef	uint16  PduIdType;
/**************************************************************************************************
**
Name:                                    PduLengthType
Type:                                     uint8, uint16, uint32
Description:  This type shall be used within the entire AUTOSAR Com Stack of an ECU except for  bus drivers.
					                                                                                                                   **
**************************************************************************************************/
typedef	uint16  PduLengthType;

/**************************************************************************************************
**
Name:                                     PduInfoType
Type:                                      Structure
Description:     Variables of this type shall be used to store the basic information about a PDU of any 
                 type, namely a pointer variable pointing to its SDU (payload), a pointer to Meta Data of 
                 the PDU, and the corresponding length of the SDU in bytes.
                   
																																				**
**************************************************************************************************/
typedef struct {
	PduLengthType                     SduLength;
	uint8*                            SduDataPtr;
        uint8*                            MetaDataPtr ;    
}PduInfoType;




/**************************************************************************************************
**
Name:                                     BufReq_ReturnType
Type:                                      Enumeration
Description:  Variables of this type shall be used to store the result of a buffer request.
                    
																																				**
**************************************************************************************************/	

typedef enum {
	BUFREQ_OK,
	BUFREQ_E_NOT_OK,
	BUFREQ_E_BUSY,
	BUFREQ_E_OVFL
}BufReq_ReturnType;


typedef struct {
//TpDataStateType      TpDataState
PduLengthType        TxTpDataCnt;
                      
}RetryInfoType;


#endif /* ComStack_TYPES_H */

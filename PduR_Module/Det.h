/*******************************************************************************************************************************
FileName:                    							  Det.h                                      
AUTOSAR Version:          								  20.11
******************************************************************************************************************************/
#ifndef DET_H
#define DET_H

/******************************************************************************************************************************
 **                                                                        Includes                                                                             **
 ******************************************************************************************************************************/
#include "Platform_Types.h"
#include "ComStack_Types.h"
/*******************************************************************************************************************************
**                                               						  Defines                                                                                **
********************************************************************************************************************************/



/*******************************************************************************************************************************
**                                               						   Variables                                                                             **
********************************************************************************************************************************/



/*******************************************************************************************************************************
**                                               				    Function prototypes                                                                       **
********************************************************************************************************************************/
Std_ReturnType Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId);


#endif /*DET_H*/
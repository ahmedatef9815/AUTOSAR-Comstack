/******************************************************************************
 *
 * Module: Common - Platform
 *
 * File Name: Std_Types.h
 *
 * Description: General type definitions
 *******************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H
#include "Platform_Types.h"
/*
 *  Describes the standard Return Type Definitions used in the project
 */
typedef uint8  Std_ReturnType;

#define E_OK            ((Std_ReturnType)0x00U)      /* Function Return OK */
#define E_NOT_OK        ((Std_ReturnType)0x01U)      /* Function Return NOT OK */
#define STD_ON          0x01U                        /* Standard ON */
#define STD_OFF         0x00U                       /* Standard OFF */
#endif /* STD_TYPES_H */
/******************************************************************************
 * Module: CanSM
 *
 * File Name: Std_Types.h
 *
 * Description: Header file for Standard Types.
 *
 * Author: Khaled Tarek
 ******************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H
/*
 * Module Version 1.0.0
 */

#define STD_TYPES_SW_MAJOR_VERSION                (1U)
#define STD_TYPES_SW_MINOR_VERSION                (0U)
#define STD_TYPES_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION        (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION        (0U)
#define STD_TYPES_AR_RELEASE_PATCH_VERSION        (3U)

#include "Platform_Types.h"

typedef enum
{
	E_OK,
    E_NOT_OK,
}Std_ReturnType ;

typedef struct
{
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
}Std_VersionInfoType;

#define STD_OFF                             (0U)
#define STD_ON                              (1U)

#endif

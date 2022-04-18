#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H
#include "Std_Types.h"

#define COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION                 (4U)
#define COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION                 (0U)
#define COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION                 (3U)

typedef uint8 NetworkHandleType;
typedef uint8 IcomConfigIdType;



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

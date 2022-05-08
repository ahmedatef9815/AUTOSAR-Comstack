/******************************************************************************
 * Module: CanDriver
 *
 * File Name: Can_PBcfg.h
 *
 * Description: Header file for Can driver post-build Configuration.
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */

#ifndef CAN_PBCFG_H_
#define CAN_PBCFG_H_



#define CAN_PBCFG_SW_MAJOR_VERSION                (1U)
#define CAN_PBCFG_SW_MINOR_VERSION                (0U)
#define CAN_PBCFG_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CAN_PBCFG_AR_RELEASE_MAJOR_VERSION        (4U)
#define CAN_PBCFG_AR_RELEASE_MINOR_VERSION        (0U)
#define CAN_PBCFG_AR_RELEASE_PATCH_VERSION        (3U)

#include "Can_Cfg.h"


#define NUMBER_OF_CANCONTROLLERS                   (2U)

typedef enum
{
    Can_Controller0,
    Can_Controller1,
}Can_Controllers;

/***************************MailBoxType************************************/
typedef struct
{
    uint8 mail1;
    uint8 mail2;
    uint8 mail3;
}MailBoxType;

/*********************CanControllerBaudrateConfig*******************************/

typedef struct
{
    uint16          CanControllerBaudRate        ;
    uint8           CanControllerBaudRateConfigID;
    uint8           CanControllerPropSeg         ;
    uint8           CanControllerSeg1            ;
    uint8           CanControllerSeg2            ;
    uint8           CanControllerSyncJumpWidth   ;
}CanControllerBaudrateConfig;

/***************************CanConfigType************************************/
typedef struct
{
    uint8 Can_Controller;
    MailBoxType* Can_MailBoxLengths;
    CanControllerBaudrateConfig* Can_Baudrate;
}Can_ConfigType;



extern MailBoxType mailBox[NUMBER_OF_CANCONTROLLERS];

extern CanControllerBaudrateConfig CanControllerBaudrate[NUMBER_OF_CANCONTROLLERS];

extern Can_ConfigType CanConfig[NUMBER_OF_CANCONTROLLERS];

#endif

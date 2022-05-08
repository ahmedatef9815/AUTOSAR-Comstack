/******************************************************************************
 * Module: CanDriver
 *
 * File Name: Can_GeneralTypes.h
 *
 * Description: Header file for Can general types.
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */
#ifndef CAN_GENERALTYPES_H_
#define CAN_GENERALTYPES_H_

#define CAN_GENERALTYPES_SW_MAJOR_VERSION         (1U)
#define CAN_GENERALTYPES_SW_MINOR_VERSION         (0U)
#define CAN_GENERALTYPES_SW_PATCH_VERSION         (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define CAN_CFG_AR_RELEASE_MAJOR_VERSION          (4U)
#define CAN_CFG_AR_RELEASE_MINOR_VERSION          (0U)
#define CAN_CFG_AR_RELEASE_PATCH_VERSION          (3U)

/*Needed Defines */
#define Max_BaudeRateIDs                          ((uint16)10)
/*Can_ReturnType*/
/*Overlayed return value of Std_ReturnType for CAN driver API Can_Write()*/
#define CAN_BUSY                                  0x02u


#if (CanIdType==STANDARD)
typedef uint16 Can_IdType;
/*Standard32Bit 0..0x400007FF*/
#elif  (CanIdType==EXTENDED)
typedef uint32 Can_IdType;
/*Extended32Bit 0..0xDFFFFFFF*/
#endif


/*Represents the hardware object handles of a CAN hardware unit.
 For CAN hardware units with more than 255 HW objects use extended range.
*/
typedef uint8 Can_HwHandleType;
/*typedef uint16 Can_HwHandleType;*/

typedef uint8 PduIdType;




/*Can_PduType*/
typedef struct {
    PduIdType	swPduHandle;
    uint8		length;
    Can_IdType	id;
    uint8*		sdu;
}Can_PduType;


/**********************************/

/*Can_HwType*/

/*This type defines a data structure which clearly provides an Hardware Object Handle
 including its corresponding CAN Controller and therefore CanDrv as well as the specific CanId*/

typedef struct{
    Can_IdType			CanId;
    Can_HwHandleType	Hoh;
    uint8				ControllerId;
}Can_HwType;




typedef enum
{
    CAN_ERRORSTATE_ACTIVE,/*The CAN controller takes fully part in communication.*/
    CAN_ERRORSTATE_PASSIVE,/*The CAN controller takes part in communication, but does not send active error frames.*/
    CAN_ERRORSTATE_BUSOFF,/*The CAN controller does not take part in communication.*/
}Can_ErrorStateType;




typedef enum
{
    CAN_CS_UNINIT,
    CAN_CS_STARTED,
    CAN_CS_STOPPED,
    CAN_CS_SLEEP,
}Can_ControllerStateType;




#endif

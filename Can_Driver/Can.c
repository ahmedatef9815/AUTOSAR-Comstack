/******************************************************************************
 * Module: CanDriver
 *
 * File Name: Can.c
 *
 * Description: Source file for Can driver.
 *
 * Author: Khaled Tarek
 ******************************************************************************/

#include "Can.h"
#include "UTILES.h"

#if(CanDevErrorDetect==STD_ON)
Std_ReturnType Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId)
{
    return E_OK;
}
#endif

#define CAN0_BASE_ADDRESS                  (*(volatile uint32*)(0x40006400))
#define CAN1_BASE_ADDRESS                  (*(volatile uint32*)(0x40006800))

#define RCC_AHB1ENR                        (*(volatile uint32*)(0x40023830))
#define RCC_APB1ENR                        (*(volatile uint32*)(0x40023840))

#define CAN0_MCR                           (*(volatile uint32*)(0x40006400))
#define CAN0_MSR                           (*(volatile uint32*)(0x40006404))
#define CAN0_BTR                           (*(volatile uint32*)(0x4000641C))
#define CAN0_TDT0R                         (*(volatile uint32*)(0x40006584))
#define CAN0_TDT1R                         (*(volatile uint32*)(0x40006594))
#define CAN0_TDT2R                         (*(volatile uint32*)(0x400065A4))
#define CAN0_TI0R                          (*(volatile uint32*)(0x40006580))
#define CAN0_TI1R                          (*(volatile uint32*)(0x40006590))
#define CAN0_TI2R                          (*(volatile uint32*)(0x400065A0))

#define CAN1_MCR                           (*(volatile uint32*)(0x40006800))
#define CAN1_MSR                           (*(volatile uint32*)(0x40006804))
#define CAN1_BTR                           (*(volatile uint32*)(0x4000681C))
#define CAN1_TDT0R                         (*(volatile uint32*)(0x40006984))
#define CAN1_TDT1R                         (*(volatile uint32*)(0x40006994))
#define CAN1_TDT2R                         (*(volatile uint32*)(0x400069A4))
#define CAN1_TI0R                          (*(volatile uint32*)(0x40006980))
#define CAN1_TI1R                          (*(volatile uint32*)(0x40006990))
#define CAN1_TI2R                          (*(volatile uint32*)(0x400069A0))

typedef enum
{
    CAN_UNINIT,
    CAN_READY,
}Module_StateType;

Can_ConfigType* Configuration;

static Can_ControllerStateType Can0_ControllerState = CAN_CS_UNINIT;

static Can_ControllerStateType Can1_ControllerState = CAN_CS_UNINIT;

static Module_StateType Can_ModuleState = CAN_UNINIT;


void Can_Init(Can_ConfigType* Config)
{
    #if(CanDevErrorDetect==STD_ON)
    if (Can_ModuleState != CAN_UNINIT)
    {
        Det_ReportError(CAN_MODULE_ID,CAN_INSTANCE_NUMBER,Can_Init_ID,CAN_E_TRANSITION);
    }
    #endif
    Configuration = Config;

    /*Enable clock for GPIOB, Can1 and Can2*/
    RCC_AHB1ENR   |= (1 <<  1);
    RCC_APB1ENR   |= (1 << 25) | (1 << 26);

    /**********************First Controller**********************/
    /*Reset values*/
    CAN0_MCR = 0x00010002;
    CAN0_MSR = 0x00000C02;
    /*setting the INIT bit in the CAN Master Control (CAN_MCR) register 0 stopping all bus activities */
    SET_BIT(CAN0_MCR,0);
    /*Wait for ack bit*/
    while(GET_BIT(CAN0_MSR,0)==0);

    /*Setting the Prescaler in the BRP section of the register, BRP= Baud rate prescaler - 1*/
    uint32 Prescaler = (CanCpuClockRef/(Configuration->Can_Baudrate->CanControllerBaudRate*1024));
    CAN0_BTR |= ((Prescaler - 1)&0x3F);
    /*Setting Time Segment after Sample Point TSEG2*/
    CAN0_BTR|= (uint32)((Configuration->Can_Baudrate->CanControllerSeg2-1)&0x70000);
    /*Setting Time Segment before Sample Point TSEG2*/
    CAN0_BTR|= (uint32)((Configuration->Can_Baudrate->CanControllerSeg1-1)&0xF000);
    /*Setting   (Re)Synchronization Jump Width*/
    CAN0_BTR|= (uint32)((Configuration->Can_Baudrate->CanControllerSyncJumpWidth-1)&0xC0);

    /*initialize transmit mailbox*/
    #if(CanIdType==STANDARD)
    CLEAR_BIT(CAN0_TI0R,2);
    CLEAR_BIT(CAN0_TI1R,2);
    CLEAR_BIT(CAN0_TI2R,2);
    #else
    SET_BIT(CAN0_TI0R,2);
    SET_BIT(CAN0_TI1R,2);
    SET_BIT(CAN0_TI2R,2);
    #endif

    /*Setting the number of data bytes*/
    CAN0_TDT0R |= Configuration->Can_MailBoxLengths->mail1;
    CAN0_TDT1R |= Configuration->Can_MailBoxLengths->mail2;
    CAN0_TDT2R |= Configuration->Can_MailBoxLengths->mail3;

    /*Exit initialization mode */
    CLEAR_BIT(CAN0_MCR,0);
    /*Wait for ack bit to be cleared*/
    while(GET_BIT(CAN0_MSR,0)==1);

    /*Entering Sleep MODE*/
    SET_BIT(CAN0_MCR,1);
    /*Wait for ack bit*/
    while(GET_BIT(CAN0_MSR,1)==0);
    /*Preforming the new state for can controller*/
    Can0_ControllerState = CAN_CS_SLEEP;

    /**********************Second Controller**********************/
    /*Reset values*/
    CAN1_MCR = 0x00010002;
    CAN1_MSR = 0x00000C02;
    /*setting the INIT bit in the CAN Master Control (CAN_MCR) register 1 stopping all bus activities */
    SET_BIT(CAN1_MCR,0);
    /*Wait for ack bit*/
    while(GET_BIT(CAN1_MSR,0)==0);

    /*Setting the Prescaler in the BRP section of the register, BRP= Baud rate prescaler - 1*/
    Prescaler = (CanCpuClockRef/(Configuration->Can_Baudrate->CanControllerBaudRate*1024));
    CAN1_BTR |= ((Prescaler - 1)&0x3F);
    /*Setting Time Segment after Sample Point TSEG2*/
    CAN1_BTR|=(uint32)((Configuration->Can_Baudrate->CanControllerSeg2-1)&0x70000);
    /*Setting Time Segment before Sample Point TSEG2*/
    CAN1_BTR|=(uint32)((Configuration->Can_Baudrate->CanControllerSeg1-1)&0xF000);
    /*Setting   (Re)Synchronization Jump Width*/
    CAN1_BTR|=(uint32)((Configuration->Can_Baudrate->CanControllerSyncJumpWidth-1)&0xC0);

    /*initialize transmit mailbox*/
    #if(CanIdType==STANDARD)
    CLEAR_BIT(CAN1_TI0R,2);
    CLEAR_BIT(CAN1_TI1R,2);
    CLEAR_BIT(CAN1_TI2R,2);
    #else
    SET_BIT(CAN1_TI0R,2);
    SET_BIT(CAN1_TI1R,2);
    SET_BIT(CAN1_TI2R,2);
    #endif

    /*Setting the number of data bytes*/
    CAN1_TDT0R |= Configuration->Can_MailBoxLengths->mail1;
    CAN1_TDT1R |= Configuration->Can_MailBoxLengths->mail2;
    CAN1_TDT2R |= Configuration->Can_MailBoxLengths->mail3;

    /*Exit initialization mode */
    CLEAR_BIT(CAN1_MCR,0);
    /*Wait for ack bit to be cleared*/
    while(GET_BIT(CAN1_MSR,0)==1);

    /*Entering Sleep Mode*/
    SET_BIT(CAN1_MCR,1);
    /*Wait for ack bit*/
    while(GET_BIT(CAN1_MSR,1)==0);

    /*Preforming the new state for can controller*/
    Can1_ControllerState = CAN_CS_SLEEP;

    Can_ModuleState = CAN_READY;

}

#if (CanVersionInfoApi == STD_ON)
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    #if(CanDevErrorDetect==STD_ON)
    if(versioninfo==NULL_PTR)
    {
        Det_ReportError(CAN_MODULE_ID,CAN_INSTANCE_NUMBER,Can_GetVersionInfo_ID,CAN_E_PARAM_POINTER);
    }
    #endif
    versioninfo->vendorID = CAN_VENDOR_ID;
    versioninfo->moduleID = CAN_MODULE_ID;
    versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;
}
#endif

void Can_DeInit(void)
{
    #if(CanDevErrorDetect==STD_ON)
    if (Can_ModuleState != CAN_READY)
    {
        Det_ReportError(CAN_MODULE_ID,CAN_INSTANCE_NUMBER,Can_DeInit_ID,CAN_E_TRANSITION);
    }
    #endif

    /**********************First Controller**********************/
    /*Exit sleep mode if it's in it*/
    CLEAR_BIT(CAN0_MCR,1);
    /*Wait for ack bit to be zero*/
    while(GET_BIT(CAN0_MSR,1)==1);

    /*Reset values*/
    CAN0_MCR = 0x00010002;
    CAN0_MSR = 0x00000C02;
    /*setting the INIT bit in the CAN Master Control (CAN_MCR) register 0 stopping all bus activities */
    SET_BIT(CAN0_MCR,0);
    /*Wait for ack bit*/
    while(GET_BIT(CAN0_MSR,0)==0);

    /*Delete/Reset initialization of Baudrate*/
    CAN0_BTR =  0x01230000;

    /*Delete/Reset initialization of mailbox identifier*/
    CAN0_TI0R = 0x00000000;
    CAN0_TI1R = 0x00000000;
    CAN0_TI2R = 0x00000000;

    /*Delete/Reset initialization of mailbox Lengths*/
    CAN0_TDT0R = 0x00000000;
    CAN0_TDT1R = 0x00000000;
    CAN0_TDT2R = 0x00000000;

    /*Exit initialization mode */
    CLEAR_BIT(CAN0_MCR,0);
    /*Wait for ack bit to be cleared*/
    while(GET_BIT(CAN0_MSR,0)==1);

    Can0_ControllerState = CAN_CS_UNINIT;

    /**********************Second Controller**********************/
    /*Exit sleep mode if it's in it*/
    CLEAR_BIT(CAN1_MCR,1);
    /*Wait for ack bit to be zero*/
    while(GET_BIT(CAN1_MSR,1)==1);

    /*Reset values*/
    CAN1_MCR = 0x00010002;
    CAN1_MSR = 0x00000C02;
    /*setting the INIT bit in the CAN Master Control (CAN_MCR) register 0 stopping all bus activities */
    SET_BIT(CAN1_MCR,0);
    /*Wait for ack bit*/
    while(GET_BIT(CAN1_MSR,0)==0);

    /*Delete/Reset initialization of Baudrate*/
    CAN1_BTR =  0x01230000;

    /*Delete/Reset initialization of mailbox identifier*/
    CAN1_TI0R = 0x00000000;
    CAN1_TI1R = 0x00000000;
    CAN1_TI2R = 0x00000000;

    /*Delete/Reset initialization of mailbox Lengths*/
    CAN1_TDT0R = 0x00000000;
    CAN1_TDT1R = 0x00000000;
    CAN1_TDT2R = 0x00000000;

    /*Exit initialization mode */
    CLEAR_BIT(CAN1_MCR,0);
    /*Wait for ack bit to be cleared*/
    while(GET_BIT(CAN1_MSR,0)==1);

    Can1_ControllerState = CAN_CS_UNINIT;

    Can_ModuleState = CAN_UNINIT;
}

#if (CanSetBaudrateApi==STD_ON)
Std_ReturnType Can_SetBaudrate(uint8 Controller,uint16 BaudRateConfigID)
{

}
#endif

void Can_DisableControllerInterrupts(uint8 Controller)
{

}

void Can_EnableControllerInterrupts(uint8 Controller)
{

}

/******************************************************************************
 * Module: CanDriver
 *
 * File Name: Can_PBCFG.c
 *
 * Description: Source file for Can driver post-build Configuration.
 *
 * Author: Khaled Tarek
 ******************************************************************************/



#include"Can_PBcfg.h"

MailBoxType mailBox[NUMBER_OF_CANCONTROLLERS] = {{2,5,7},{3,6,8},};

CanControllerBaudrateConfig CanControllerBaudrate[NUMBER_OF_CANCONTROLLERS]={{1300,1,2,3,1,1},{1800,2,4,4,2,1},};

Can_ConfigType CanConfig[NUMBER_OF_CANCONTROLLERS] = {
                                                        {0,&mailBox[0],&CanControllerBaudrate[0]}
                                                        ,{1,&mailBox[1],&CanControllerBaudrate[1]},
                                                     };

/******************************************************************************
 * Module: CanSM
 *
 * File Name: CanSM_PBcfg.c
 *
 * Description: Source file for Can State Manager Post-Build Parameters
 *
 * Author: Khaled Tarek
 ******************************************************************************/
#include "CanSM_PBcfg.h"

CanSMController controller[CANSM_NETWORK_COUNT]=
{
	{0},
	{1},
};

CanSMManagerNetwork CanSMNetwork[CANSM_NETWORK_COUNT] =
{
	{&controller[0],
	0,
	0,
	200,
	100,
	150,
	50,
	TRUE,
	TRUE,},
	{&controller[1],
		1,
		1,
		200,
		100,
		150,
		50,
		TRUE,
		TRUE,},
};

CanSM_ConfigType* configurationptr = {CanSMNetwork,};

CanSMConfiguration CanSMConfig =
{
    250,
    50,
    CanSMNetwork,
};

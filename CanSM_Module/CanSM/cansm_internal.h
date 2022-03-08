#ifndef CANSM_INTERNAL_H
#define CANSM_INTERNAL_H
#include"cansm.h"
typedef enum {
	CANSM_BOR_IDLE, /**< Idle state */
	CANSM_BOR_CHECK, /**<  Initial bus-off check at beginning of full-communication */
	CANSM_BOR_NO_BUS_OFF, /**<  Regular state during full-communication without detected bus-off events */
	CANSM_BOR_TXOFF_L1, /**<  Bus-off recovery level 1 state, TX disabled */
	CANSM_BOR_CHECK_L1, /**<  Bus-off recovery level 1 state, TX enabled again */
	CANSM_BOR_TXOFF_L2, /**<  Bus-off recovery level 2 state, TX disabled */
	CANSM_BOR_CHECK_L2 /**<  Bus-off recovery level 2 state, TX enabled again */
} CanSM_BusOffRecoveryStateType;
typedef struct {
	boolean busoffevent;
	ComM_ModeType requestedMode;
	uint16 counter;
	uint16 timer;
	CanSM_BusOffRecoveryStateType BusOffRecoveryState;
	CanSMManagerNetwork* NetworkManage;
} CanSM_Internal_NetworkType;

typedef struct {
	CanSM_StateType 		InitStatus;
	CanSM_Internal_NetworkType*		Networks;
} CanSM_InternalType;

#endif


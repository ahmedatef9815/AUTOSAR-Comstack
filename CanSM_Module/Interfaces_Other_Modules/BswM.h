#ifndef BSWM_H
#define BSWM_H
#include "ComStack_Types.h"
#include "CanSM_BswM.h"
#define BSWM_AR_RELEASE_MAJOR_VERSION               (4U)
#define BSWM_AR_RELEASE_MINOR_VERSION               (0U)
#define BSWM_AR_RELEASE_PATCH_VERSION               (3U)

void BswM_CanSM_CurrentState(NetworkHandleType Network,CanSM_BswMCurrentStateType CurrentState);
#endif

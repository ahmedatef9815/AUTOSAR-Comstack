#ifndef COMM_BUSSM_H
#define COMM_BUSSM_H
#include "ComM.h"
#include "ComStack_Types.h"

#define COMM_BUSSM_AR_RELEASE_MAJOR_VERSION                 (4U)
#define COMM_BUSSM_AR_RELEASE_MINOR_VERSION                 (0U)
#define COMM_BUSSM_AR_RELEASE_PATCH_VERSION                 (3U)
void ComM_BusSM_ModeIndication(NetworkHandleType Channel,ComM_ModeType* ComMode);

#endif

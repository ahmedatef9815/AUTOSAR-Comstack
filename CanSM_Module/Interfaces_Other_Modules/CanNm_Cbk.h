#ifndef CANNM_CBK_H
#define CANNM_CBK_H

#include "ComStack_Types.h"

#define CANNM_CBK_AR_RELEASE_MAJOR_VERSION                  (4U)
#define CANNM_CBK_AR_RELEASE_MINOR_VERSION                  (0U)
#define CANNM_CBK_AR_RELEASE_PATCH_VERSION                  (3U)

#define CanNmGlobalPnSupport                                STD_ON

#if (CanNmGlobalPnSupport==STD_ON)
void CanNm_ConfirmPnAvailability(NetworkHandleType nmChannelHandle);
#endif
#endif

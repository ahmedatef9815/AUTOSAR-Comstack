#ifndef DEM_H
#define DEM_H
#include "Std_Types.h"

#define DEM_AR_RELEASE_MAJOR_VERSION            (4U)
#define DEM_AR_RELEASE_MINOR_VERSION            (0U)
#define DEM_AR_RELEASE_PATCH_VERSION            (3U)

typedef uint8 Dem_EventIdType;

Std_ReturnType Dem_ReportErrorStatus(Dem_EventIdType EventID, uint8 EventStatus);

#endif

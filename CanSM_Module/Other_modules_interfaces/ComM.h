#ifndef COMM_H
#define COMM_H

#define COMM_AR_RELEASE_MAJOR_VERSION                   (4U)
#define COMM_AR_RELEASE_MINOR_VERSION                   (0U)
#define COMM_AR_RELEASE_PATCH_VERSION                   (3U)

#define ComMPncSupport                                  STD_OFF

typedef enum
{
	COMM_NO_COMMUNICATION,
	COMM_SILENT_COMMUNICATION,
	COMM_FULL_COMMUNICATION,
}ComM_ModeType;

typedef enum
{
    DEM_EVENT_STATUS_PASSED,
    DEM_EVENT_STATUS_FAILED,
    DEM_EVENT_STATUS_PREPASSED,
    DEM_EVENT_STATUS_PREFAILED
}Dem_ErrorType;
#endif

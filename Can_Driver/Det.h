#ifndef DET_H_
#define DET_H_

#define DET_SW_MAJOR_VERSION                (1U)
#define DET_SW_MINOR_VERSION                (0U)
#define DET_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DET_AR_RELEASE_MAJOR_VERSION        (4U)
#define DET_AR_RELEASE_MINOR_VERSION        (0U)
#define DET_AR_RELEASE_PATCH_VERSION        (3U)

Std_ReturnType Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId);

#endif

/******************************************************************************
 * Module: CanDriver
 *
 * File Name: UTILES.h
 *
 * Description: Header file for Macros.
 *
 * Author: Khaled Tarek
 ******************************************************************************/
/*
 * Module Version 1.0.0
 */
#ifndef utils_h
#define utils_h

#define UTILES_SW_MAJOR_VERSION                (1U)
#define UTILES_SW_MINOR_VERSION                (0U)
#define UTILES_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define UTILES_AR_RELEASE_MAJOR_VERSION        (4U)
#define UTILES_AR_RELEASE_MINOR_VERSION        (0U)
#define UTILES_AR_RELEASE_PATCH_VERSION        (3U)


#define CLEAR_ALL(reg) reg=0 ;
#define SET_ALL(reg)  reg=~0 ;
#define SET_BIT(reg,bit) reg|=(uint32)(1<<(bit))
#define CLEAR_BIT(reg,bit) reg&=~(uint32)(1<<(bit))
#define TOOGLE_BIT(reg,bit) reg^=(1<<(bit))
#define GET_BIT(reg,bit) (reg&(1<<(bit)))>>(bit)
#endif

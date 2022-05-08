/******************************************************************************
 * Module: CanDriver
 *
 * File Name: Platform_Types.h
 *
 * Description: Header file for Platform Types.
 *
 * Author: Khaled Tarek
 ******************************************************************************/
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_
/*
 * Module Version 1.0.0
 */

#define PLATFORM_TYPES_SW_MAJOR_VERSION                (1U)
#define PLATFORM_TYPES_SW_MINOR_VERSION                (0U)
#define PLATFORM_TYPES_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION        (4U)
#define PLATFORM_TYPES_AR_RELEASE_MINOR_VERSION        (0U)
#define PLATFORM_TYPES_AR_RELEASE_PATCH_VERSION        (3U)



typedef unsigned char boolean;

#define FALSE  0x00u
#define TRUE   0x01u

/*unsigned*/

typedef unsigned char 			uint8;				/* 0 =>255*/
typedef unsigned short int 	    uint16;				/*0=>65536*/
typedef unsigned long int       uint32;				/*0=>4294967296*/
typedef long long unsigned int 	uint64;  			/*0=>18446744073709551616*/

				/************************************************/

/*signed*/

typedef signed char 		    sint8;				/* -128 => +127*/
typedef signed short int        sint16;				/* -32768 => +32767*/
typedef signed long int         sint32;				/* -2147483648 => +2147483647*/
typedef long long int 			sint64;				/* -9223372036854775808 => +9223372036854775807*/

				/************************************************/

/*Float*/

typedef  float 					float32;
typedef double 					float64;
typedef long double 			float128;

				/************************************************/
#endif

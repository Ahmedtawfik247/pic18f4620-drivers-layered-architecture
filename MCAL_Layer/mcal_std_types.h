/* 
 * File:   mcal_std_types.h
 * Author: botsha
 *
 * Created on December 22, 2024, 12:11 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Inlcudes */

#include "std_libraries.h"
#include "compiler.h"

/* Section : Macro Declerations */

#define STD_HIGH            0x01
#define STD_LOW             0x00

#define STD_ON              0x01
#define STD_OFF             0x00

#define STD_ACTIVE          0x01
#define STD_IDLE            0x00

#define E_OK                (Std_ReturnType)0x01
#define E_NOT_OK            (Std_ReturnType)0x00

#define ZERO_INIT           0


/* Section : Macro Functions Declerations */

/* Section : Data Type Declerations */

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;

typedef signed char         int8;
typedef signed short        int16;
typedef signed int          int32;

typedef uint8               Std_ReturnType;

/* Section : Functions Declerations */


#endif	/* MCAL_STD_TYPES_H */


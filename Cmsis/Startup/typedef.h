#ifndef __TYPEDEF_H
#define __TYPEDEF_H

#ifndef NULL
#define NULL             ((void *)0)
#endif 

#ifndef TRUE 
#define TRUE  (1U)
#endif
#ifndef FALSE
#define FALSE (0U)
#endif 
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */
	
//#define bool _Bool

#ifndef _INT32_T_DECLARED
typedef signed int      				int32_t;
#define _INT32_T_DECLARED
#endif

#ifndef _UINT32_T_DECLARED
typedef unsigned int    				uint32_t;
#define _UINT32_T_DECLARED
#endif

typedef unsigned short  				uint16_t;
typedef signed short    				int16_t;
typedef unsigned char  			 		uint8_t;
typedef signed  char 					int8_t;
typedef char    						char_t;
typedef  unsigned char    				bool_t;
typedef unsigned long long int  		uint64_t;

/*typegene.h*/
typedef uint8_t	   T_UBYTE;
typedef uint16_t   T_UWORD;
typedef uint32_t 	 T_ULONG;

typedef int8_t     T_SBYTE;
typedef int16_t    T_SWORD;
typedef int32_t    T_SLONG;

typedef struct{
	uint16_t	Bit0:1;
	uint16_t	Bit1:1;
	uint16_t	Bit2:1;
	uint16_t	Bit3:1;
	uint16_t	Bit4:1;
	uint16_t	Bit5:1;
	uint16_t	Bit6:1;
	uint16_t	Bit7:1;
}T_BitFLD;

/* Carrier of 16 Bits */
typedef struct {
	uint16_t	Bit8:1;
	uint16_t	Bit9:1;
	uint16_t	Bit10:1;
	uint16_t	Bit11:1;
	uint16_t	Bit12:1;
	uint16_t	Bit13:1;
	uint16_t	Bit14:1;
	uint16_t	Bit15:1;
	uint16_t	Bit0:1;
	uint16_t	Bit1:1;
	uint16_t	Bit2:1;
	uint16_t	Bit3:1;
	uint16_t	Bit4:1;
	uint16_t	Bit5:1;
	uint16_t	Bit6:1;
	uint16_t	Bit7:1;
}T_BitFLD16;

/* Carrier of 8 bits with carrier handling */
typedef union {
	T_BitFLD Bits;
	T_UBYTE	 by;
}T_FLAG8;

/* Word with msb and lsb handling */
typedef struct	{
	T_UBYTE	msb;
	T_UBYTE	lsb;
}T_BYTEWORD;

typedef union	{
	T_BYTEWORD	by;
	T_UWORD		wo;
}T_BYTEFLD;

/* Carrier of 16 bits with word or byte (msb & lsb) carrier handling */
typedef union   {
	T_BitFLD16 Bits;
	T_BYTEFLD  cr;
}T_FLAG16;


#endif

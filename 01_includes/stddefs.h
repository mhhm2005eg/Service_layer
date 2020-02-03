/************************************************************************/
/* !File            : stddefs.h                                         * */
/*                                                                      *   */
/* !Scope           : Public                                            ******/
/*                                                                           */
/* !Component       : STD                                                    */
/*                                                                           */
/*****************************************************************************/

#ifndef STD_DEFS
#define STD_DEFS

/*****************************************************************************/
/*                          DEFINITION TYPES                                 */
/*****************************************************************************/
/* !Comment : Standard definition for the unsigned 8 bits                    */
/* !Range   : 0..255                                                         */
typedef unsigned char      u8  ;
typedef unsigned char      uint8  ;
/* !Comment : Standard definition for the signed 8 bits                      */
/* !Range   : -128..127                                                      */
typedef signed char        s8  ;
/* !Comment : Standard definition for the unsigned 16 bits                   */
/* !Range   : 0..65535                                                       */
typedef unsigned short u16 ;
typedef unsigned short uint16 ;
/* !Comment : Standard definition for the signed 16 bits                     */
/* !Range   : -32767..32768                                                  */
typedef signed short int   s16 ;
/* !Comment : Standard definition for the unsigned 32 bits                   */
/* !Range   : 0..4294967295                                                  */
typedef unsigned int      u32 ;
typedef unsigned int      uint32 ;

/* !Comment : Standard definition for the unsigned 64 bits                   */
typedef unsigned long      u64 ;
typedef unsigned long      uint64 ;
/* !Comment : Standard definition for the signed 32 bits                     */
/* !Range   : -2147483647..2147483648                                        */
typedef signed long        s32 ;

/* !Comment : Standard definition for BOOLEAN with the smaller size.         */
/* !Range   : 0 ou 1                                                         */
/* !Unit    : Sans unit�                                                     */
typedef unsigned char Bool ;
/* !Comment : Standard definition for BOOLEAN with a 16 bits size.           */
/* !Range   : 0 ou 1                                                         */
/* !Unit    : Sans unit�                                                     */
typedef unsigned short int u16Bool ;

/* !Comment : Define the list of status for all functions returns.           */
/* !Range   : STD_EXEC_OK..STD_EXEC_NOK                                      */
/* !Unit    : Sans unit�                                                     */
typedef enum:int{
  STD_EXEC_OK = 0, /* Status standard for the Architecture                       */
  STD_CONFIG_ERROR,
  STD_NO_INIT,
  STD_ID_ERROR,
  STD_SRV_BUSY,
  STD_RETURN_ERROR,
  STD_TIMEOUT,
  STD_PARAM_ERROR,
  STD_RUNNING_MODE,
  STD_WAITING_MODE,
  STD_SLEEP_MODE,
  STD_LOW_MODE,
  STD_BIT_ERROR, /* Status standard from the layer Processor (PSL)           */
  STD_LOSS_OF_MSG,
  STD_RISING_EDGE, /* Status standard from the layer Board (BSL)             */
  STD_FALLING_EDGE,
  STD_PULSE_MODE,
  STD_EXEC_NOK /* Last status standard for the Architecture                  */
} STD_tenuStatus ;

/*****************************************************************************/
#if defined( __BITFIELD_LSBIT_FIRST__ )
/* !Comment  : Define the 8 bits size (BYTE) structure to access bits.       */
typedef union 
{
  /* !Comment : Access using a mask.                                         */
  unsigned char u8Byte ;
  /* !Comment : Access bit by bit.                                           */
  struct 
  {
    unsigned int flgB00 : 1;
    unsigned int flgB01 : 1;
    unsigned int flgB02 : 1;
    unsigned int flgB03 : 1;
    unsigned int flgB04 : 1;
    unsigned int flgB05 : 1;
    unsigned int flgB06 : 1;
    unsigned int flgB07 : 1;
  } strBit ;
} tuniByteField ;

/* !Comment  : Define the 16 bits size (WORD) structure to access bits.      */
typedef union
{
  /* !Comment : Access using a mask.                                         */
  unsigned short int u16Word ;
  /* !Comment : Access using Bytes.                                          */
  struct
  {
    unsigned int u8MSB : 8 ;
    unsigned int u8LSB : 8 ;
  } strByte ;
  /* !Comment : Access bit by bit.                                           */
  struct
  {
    unsigned int flgB00 : 1;
    unsigned int flgB01 : 1;
    unsigned int flgB02 : 1;
    unsigned int flgB03 : 1;
    unsigned int flgB04 : 1;
    unsigned int flgB05 : 1;
    unsigned int flgB06 : 1;
    unsigned int flgB07 : 1;
    unsigned int flgB08 : 1;
    unsigned int flgB09 : 1;
    unsigned int flgB10 : 1;
    unsigned int flgB11 : 1;
    unsigned int flgB12 : 1;
    unsigned int flgB13 : 1;
    unsigned int flgB14 : 1;
    unsigned int flgB15 : 1;
  } strBit ;
} tuniWordField ;

/* !Comment  : Define the 32 bits size (LONG) structure to access bits.      */
typedef union
{
  /* !Comment : Access using a mask.                                         */
  unsigned long int u32Long ;
  /* !Comment : Access using Words.                                          */
  struct
  {
    unsigned int u16MSB : 16 ;
    unsigned int u16LSB : 16 ;
  } strWord ;
  /* !Comment : Access using Bytes.                                          */
  unsigned char u8Bytes[ sizeof(unsigned long int) ] ;
  /* !Comment : Access bit by bit.                                           */
  struct
  {
    unsigned int flgB00 : 1;
    unsigned int flgB01 : 1;
    unsigned int flgB02 : 1;
    unsigned int flgB03 : 1;
    unsigned int flgB04 : 1;
    unsigned int flgB05 : 1;
    unsigned int flgB06 : 1;
    unsigned int flgB07 : 1;
    unsigned int flgB08 : 1;
    unsigned int flgB09 : 1;
    unsigned int flgB10 : 1;
    unsigned int flgB11 : 1;
    unsigned int flgB12 : 1;
    unsigned int flgB13 : 1;
    unsigned int flgB14 : 1;
    unsigned int flgB15 : 1;
    unsigned int flgB16 : 1;
    unsigned int flgB17 : 1;
    unsigned int flgB18 : 1;
    unsigned int flgB19 : 1;
    unsigned int flgB20 : 1;
    unsigned int flgB21 : 1;
    unsigned int flgB22 : 1;
    unsigned int flgB23 : 1;
    unsigned int flgB24 : 1;
    unsigned int flgB25 : 1;
    unsigned int flgB26 : 1;
    unsigned int flgB27 : 1;
    unsigned int flgB28 : 1;
    unsigned int flgB29 : 1;
    unsigned int flgB30 : 1;
    unsigned int flgB31 : 1;
  } strBit ;
} tuniLongField ;

#elif defined( __BITFIELD_MSBIT_FIRST__ )

/* !Comment  : Define the 8 bits size (BYTE) structure to access bits.       */
typedef union 
{
  /* !Comment : Access using a mask.                                         */
  unsigned char u8Byte ;
  /* !Comment : Access bit by bit.                                           */
  struct 
  {
    unsigned int flgB07 : 1;
    unsigned int flgB06 : 1;
    unsigned int flgB05 : 1;
    unsigned int flgB04 : 1;
    unsigned int flgB03 : 1;
    unsigned int flgB02 : 1;
    unsigned int flgB01 : 1;
    unsigned int flgB00 : 1;
  } strBit ;
} tuniByteField ;

/* !Comment  : Define the 16 bits size (WORD) structure to access bits.      */
typedef union
{
  /* !Comment : Access using a mask.                                         */
  unsigned short int u16Word ;
  /* !Comment : Access using Bytes.                                          */
  struct
  {
    unsigned int u8MSB : 8 ;
    unsigned int u8LSB : 8 ;
  } strByte ;
  /* !Comment : Access bit by bit.                                           */
  struct
  {
    unsigned int flgB15 : 1;
    unsigned int flgB14 : 1;
    unsigned int flgB13 : 1;
    unsigned int flgB12 : 1;
    unsigned int flgB11 : 1;
    unsigned int flgB10 : 1;
    unsigned int flgB09 : 1;
    unsigned int flgB08 : 1;
    unsigned int flgB07 : 1;
    unsigned int flgB06 : 1;
    unsigned int flgB05 : 1;
    unsigned int flgB04 : 1;
    unsigned int flgB03 : 1;
    unsigned int flgB02 : 1;
    unsigned int flgB01 : 1;
    unsigned int flgB00 : 1;
  } strBit ;
} tuniWordField ;

/* !Comment  : Define the 32 bits size (LONG) structure to access bits.      */
typedef union
{
  /* !Comment : Access using a mask.                                         */
  unsigned long int u32Long ;
  /* !Comment : Access using Words.                                          */
  struct
  {
    unsigned int u16MSB : 16 ;
    unsigned int u16LSB : 16 ;
  } strWord ;
  /* !Comment : Access using Bytes.                                          */
  unsigned char u8Bytes[ sizeof(unsigned long int) ] ;
  /* !Comment : Access bit by bit.                                           */
  struct
  {
    unsigned int flgB31 : 1;
    unsigned int flgB30 : 1;
    unsigned int flgB29 : 1;
    unsigned int flgB28 : 1;
    unsigned int flgB27 : 1;
    unsigned int flgB26 : 1;
    unsigned int flgB25 : 1;
    unsigned int flgB24 : 1;
    unsigned int flgB23 : 1;
    unsigned int flgB22 : 1;
    unsigned int flgB21 : 1;
    unsigned int flgB20 : 1;
    unsigned int flgB19 : 1;
    unsigned int flgB18 : 1;
    unsigned int flgB17 : 1;
    unsigned int flgB16 : 1;
    unsigned int flgB15 : 1;
    unsigned int flgB14 : 1;
    unsigned int flgB13 : 1;
    unsigned int flgB12 : 1;
    unsigned int flgB11 : 1;
    unsigned int flgB10 : 1;
    unsigned int flgB09 : 1;
    unsigned int flgB08 : 1;
    unsigned int flgB07 : 1;
    unsigned int flgB06 : 1;
    unsigned int flgB05 : 1;
    unsigned int flgB04 : 1;
    unsigned int flgB03 : 1;
    unsigned int flgB02 : 1;
    unsigned int flgB01 : 1;
    unsigned int flgB00 : 1;
  } strBit ;
} tuniLongField ;

#else
/*  #error "Define __BITFIELD_MSBIT_FIRST__ or __BITFIELD_LSBIT_FIRST__" */
#endif

/*****************************************************************************/
/*                          DECLARATION CONSTANTES SYMBOLIQUES               */
/*****************************************************************************/
/* !Comment  : Definition to disable an implemented mode for the project.
   ATTENTION => Only used by the Pre-processor.                              */
#define STD_INACTIVATED   0
/* !Comment  : Definition to enable an implemented mode for the project.
   ATTENTION => Only used by the Pre-processor.                              */
#define STD_ACTIVATED     1

/* !MComment : Define various Standard definition for NULL.                  */
#define STD_NULL     0x0000
#define STD_pvidNULL (void *)0x0000
#define STD_u32NULL  (u32)0x00000000
#define STD_u16NULL  (u16)0x0000 
#define STD_u8NULL   (u8)0x00

/* !MComment : Define various Standard definition for FULL.                  */
#define STD_u32FULL 0xFFFFFFFF
#define STD_u16FULL (u16)0xFFFF 
#define STD_u8FULL  (u8)0xFF

/* !MComment : Define various Standard definition for FALSE.                 */
#define STD_u32FALSE  (u32)0x00000000
#define STD_u16FALSE  (u16)0x0000
#define STD_bu16FALSE (u16Bool)0x0000
#define STD_u8FALSE   (u8)0x00
#define STD_bFALSE    (Bool)0

/* !MComment : Define various Standard definition for TRUE.                  */
#define STD_u32TRUE  (u32)0x00000001
#define STD_u16TRUE  (u16)0x0001
#define STD_bu16TRUE (u16Bool)0x0001
#define STD_u8TRUE   (u8)0x01
#define STD_bTRUE    (Bool)1

/* !MComment : Define various Standard definition for the High Level.        */
#define STD_u32HIGH_LEVEL  (u32)0x00000001
#define STD_u16HIGH_LEVEL  (u16)0x0001
#define STD_bu16HIGH_LEVEL (u16Bool)0x0001
#define STD_u8HIGH_LEVEL   (u8)0x01
#define STD_bHIGH_LEVEL    (Bool)1

/* !MComment : Define various Standard definition for the Low Level.         */
#define STD_u32LOW_LEVEL  (u32)0x00000000
#define STD_u16LOW_LEVEL  (u16)0x0000
#define STD_bu16LOW_LEVEL (u16Bool)0x0000
#define STD_u8LOW_LEVEL   (u8)0x00
#define STD_bLOW_LEVEL    (Bool)0

/* !MComment : Define various Standard definition for the LSB and MSB masks. */
#define STD_u32LSB_MASK    (u32)0x0000FFFF
#define STD_u32MSB_MASK    (u32)0xFFFF0000
#define STD_u16LSB_MASK    (u16)0x00FF
#define STD_u16MSB_MASK    (u16)0xFF00
#define STD_u8LSB_MASK     (u8)0x0F
#define STD_u8MSB_MASK     (u8)0xF0

/* !MComment : Define various Standard definition for Byte shifting.         */
#define STD_u8SHIFT_WORD     (u8)16
#define STD_u8SHIFT_BYTE     (u8)8
#define STD_u8SHIFT_NIBBLE   (u8)4
#define STD_u8SHIFT_BIT      (u8)1

/* !MComment : Define various Standard definition for masks to access all bits
   in variables. Size change from 8 bits to 32 bits according to site of bit.*/
#define STD_u8BIT_0_MASK  (u8)0x01
#define STD_u8BIT_1_MASK  (u8)0x02
#define STD_u8BIT_2_MASK  (u8)0x04
#define STD_u8BIT_3_MASK  (u8)0x08
#define STD_u8BIT_4_MASK  (u8)0x10
#define STD_u8BIT_5_MASK  (u8)0x20
#define STD_u8BIT_6_MASK  (u8)0x40
#define STD_u8BIT_7_MASK  (u8)0x80

#define STD_u16BIT_0_MASK   (u16)0x0001
#define STD_u16BIT_1_MASK   (u16)0x0002
#define STD_u16BIT_2_MASK   (u16)0x0004
#define STD_u16BIT_3_MASK   (u16)0x0008
#define STD_u16BIT_4_MASK   (u16)0x0010
#define STD_u16BIT_5_MASK   (u16)0x0020
#define STD_u16BIT_6_MASK   (u16)0x0040
#define STD_u16BIT_7_MASK   (u16)0x0080
#define STD_u16BIT_8_MASK   (u16)0x0100
#define STD_u16BIT_9_MASK   (u16)0x0200
#define STD_u16BIT_10_MASK  (u16)0x0400
#define STD_u16BIT_11_MASK  (u16)0x0800
#define STD_u16BIT_12_MASK  (u16)0x1000
#define STD_u16BIT_13_MASK  (u16)0x2000
#define STD_u16BIT_14_MASK  (u16)0x4000
#define STD_u16BIT_15_MASK  (u16)0x8000

#define STD_u32BIT_0_MASK   (u32)0x00000001
#define STD_u32BIT_1_MASK   (u32)0x00000002
#define STD_u32BIT_2_MASK   (u32)0x00000004
#define STD_u32BIT_3_MASK   (u32)0x00000008
#define STD_u32BIT_4_MASK   (u32)0x00000010
#define STD_u32BIT_5_MASK   (u32)0x00000020
#define STD_u32BIT_6_MASK   (u32)0x00000040
#define STD_u32BIT_7_MASK   (u32)0x00000080
#define STD_u32BIT_8_MASK   (u32)0x00000100
#define STD_u32BIT_9_MASK   (u32)0x00000200
#define STD_u32BIT_10_MASK  (u32)0x00000400
#define STD_u32BIT_11_MASK  (u32)0x00000800
#define STD_u32BIT_12_MASK  (u32)0x00001000
#define STD_u32BIT_13_MASK  (u32)0x00002000
#define STD_u32BIT_14_MASK  (u32)0x00004000
#define STD_u32BIT_15_MASK  (u32)0x00008000
#define STD_u32BIT_16_MASK  (u32)0x00010000
#define STD_u32BIT_17_MASK  (u32)0x00020000
#define STD_u32BIT_18_MASK  (u32)0x00040000
#define STD_u32BIT_19_MASK  (u32)0x00080000
#define STD_u32BIT_20_MASK  (u32)0x00100000
#define STD_u32BIT_21_MASK  (u32)0x00200000
#define STD_u32BIT_22_MASK  (u32)0x00400000
#define STD_u32BIT_23_MASK  (u32)0x00800000
#define STD_u32BIT_24_MASK  (u32)0x01000000
#define STD_u32BIT_25_MASK  (u32)0x02000000
#define STD_u32BIT_26_MASK  (u32)0x04000000
#define STD_u32BIT_27_MASK  (u32)0x08000000
#define STD_u32BIT_28_MASK  (u32)0x10000000
#define STD_u32BIT_29_MASK  (u32)0x20000000
#define STD_u32BIT_30_MASK  (u32)0x40000000
#define STD_u32BIT_31_MASK  (u32)0x80000000

/*****************************************************************************/
/*                          DECLARATION DES MACROS                           */
/*****************************************************************************/
/* !Description : Function to concatenate two parameters without pre-process 
   of them before to do it. Non recursive function.                          */
#define STD_CAT( a, b )  a##b
/* !Description : Function to concatenate two parameters with pre-process of 
    them before to do it. Recursive function.                                */
#define STD_XCAT( a, b ) STD_CAT(a,b)

#define STD_u8TILDE(a) ((u8)(STD_u8FULL - (a)))

#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#define MAX(x,y) (((x) < (y)) ? (y) : (x))

/*****************************************************************************/
/*                          DECLARATION VARIABLES                            */
/*****************************************************************************/

/*****************************************************************************/
/*                          DECLARATION CONSTANTES                           */
/*****************************************************************************/
#define STD_OK 0
#define STD_NOK 1
/*****************************************************************************/
/*                          DECLARATION PROTOTYPES                           */
/*****************************************************************************/

#endif


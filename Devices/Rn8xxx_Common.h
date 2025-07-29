
#ifndef  _DATA_TYPES_H
#define  _DATA_TYPES_H

#ifndef NULL
#define NULL          0
#endif

#ifndef CONST
#define CONST          const
#endif

#ifndef VOID
#define VOID          void
#endif

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
typedef enum {false = 0, true = !false} bool;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {CTLSTAR = 0x5a, CTLSTOP = !CTLSTAR} FunctionalControl;
typedef enum {LESSTH = 1, GREATTH = 2, EQUAL = 3} CmpResult;
typedef enum {BCDType = 1, HEXType = 2} DATATYPE;

typedef unsigned char       u8;
typedef signed char         s8;
typedef unsigned short      u16;
typedef signed short        s16;
typedef unsigned long int   u32;
typedef signed long int     s32;
typedef unsigned short      WORD;
typedef unsigned long long  u64;
typedef signed long long    s64;

typedef volatile unsigned char      vu8;
typedef volatile signed char        vs8;
typedef volatile unsigned short     vu16;
typedef volatile signed short       vs16;
typedef volatile unsigned long int  vu32;
typedef volatile signed long int    vs32;
typedef unsigned char   BOOL;

/* data type defintion */
typedef unsigned long   ULONG;
typedef unsigned int    UINT;
typedef unsigned short  USHORT;
typedef unsigned char   UCHAR;
//typedef   unsigned char   BOOL;

/* dyf 增加南瑞中天特有数据类型定义 */
typedef unsigned char  BOOLEAN;
typedef signed char    INT8;
typedef unsigned char  UINT8;
typedef signed short   INT16;
typedef unsigned short UINT16;
typedef signed int     INT32;
typedef unsigned int   UINT32;
typedef long long      INT64;
typedef unsigned long long      UINT64;
typedef float          FLOAT32;
typedef double         FLOAT64;

typedef void (*funcPointer)(void);

#define RE_ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

/* "*******************************************************
**检测结构体数据大小:
**t-数据类型
**n-成员名
**l-预留数据长度,
**如果预留过小,会编译错误
**********************************************************"*/
#define StructureSpaceCheck(t,n,l)                  \
    union                                       \
    {                                           \
        t n;                                        \
        uint8 n##_buf[l*((l/sizeof(t))/(l/sizeof(t)))]; \
    }

#define BIT0                     0x01
#define BIT1                     0x02
#define BIT2                     0x04
#define BIT3                     0x08
#define BIT4                     0x10
#define BIT5                     0x20
#define BIT6                     0x40
#define BIT7                     0x80
#define BIT8                     0x100
#define BIT9                     0x200
#define BIT10                    0x400
#define BIT11                    0x800
#define BIT12                    0x1000
#define BIT13                    0x2000
#define BIT14                    0x4000
#define BIT15                    0x8000
#define BIT16                    0x10000
#define BIT17                    0x20000
#define BIT18                    0x40000
#define BIT19                    0x80000
#define BIT20                    0x100000
#define BIT21                    0x200000
#define BIT22                    0x400000
#define BIT23                    0x800000
#define BIT24                    0x1000000
#define BIT25                    0x2000000
#define BIT26                    0x4000000
#define BIT27                    0x8000000
#define BIT28                    0x10000000
#define BIT29                    0x20000000
#define BIT30                    0x40000000
#define BIT31                    0x80000000

#define FLASH_MEMORY_BASE               ((uint32_t )0x00000000             )

extern void SystemDelayUs(uint32_t i);
extern uint8_t fnRegState_Detect(uint32_t reg_addr, uint32_t position, uint32_t sign, uint32_t timeout);

#endif  //_DATA_TYPES_H

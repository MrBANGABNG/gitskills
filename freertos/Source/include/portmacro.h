/****
    *********************************************************************
    * @file     portmacro.h 
    * @date     2021-06-18
    * @brief    数据类型重定义
    *
    *********************************************************************
****/
#ifndef PORTMACRO_H
#define PORTMACRO_H

/*
*********************************************************************
*                        包含头文件
*********************************************************************
*/
#include "stdint.h"
#include "stddef.h"
/* include */
#include "FreeRTOSConfig.h"

/*
*********************************************************************
*                      数据类型重定义
*********************************************************************
*/
/* 数据类型重定义 */
#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  uint32_t
#define portBASE_TYPE   long

typedef portSTACK_TYPE  StackType_t;
typedef long            BaseType_t;
typedef unsigned long   UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
typedef uint16_t        TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffff
#else
typedef uint32_t        TickType_t;
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#endif

/* 中断寄存器 */
#define portNVIC_INT_CTRL_REG       ( *(( volatile uint32_t )0xe000ed04) )
#define portNVIC_PENDSVSET_BIT      ( 1UL << 28UL )

#define portSY_FULL_READ_WRITE      ( 15 )

#define portYIELD()                             \               
{                                               \
    /* 触发PendSV， 产生上下文切换 */               \
    portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; \
    __dsb( portSY_FULL_READ_WRITE );                \
    __isb( portSY_FULL_READ_WRITE );                \
}                                   
                                    
#endif
/* PORTMACRO_H */

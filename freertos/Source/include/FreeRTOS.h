/****
    *********************************************************************
    * @file     FreeRTOS.h 
    * @date     2021-06-18
    * @brief    相关全局任务结构声明
    *
    *********************************************************************
****/
#ifndef INC_FREERTOS_H
#define INC_FREERTOS_H

/*
*********************************************************************
*                      包含头文件
*********************************************************************
*/
#include "list.h"
#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "portable.h"
#include "portmacro.h"

/*
*********************************************************************
*                    任务控制块类型声明
*********************************************************************
*/
typedef struct tskTaskControlBlock
{
    volatile StackType_t *pxTopOfStack;     /* 栈顶 */
    
    ListItem_t xStateListItem;              /* 任务节点 */
    
    StackType_t *pxStack;                   /* 任务栈起始地址 */
    
    /* 任务名称，字符串形式 */
    char pcTaskName[ configMAX_TASK_NAME_LEN ];
} tskTCB;

typedef tskTCB TCB_t;

#endif
/* INC_FREERTOS_H */

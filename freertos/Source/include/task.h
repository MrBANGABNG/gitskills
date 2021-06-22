/****
    *********************************************************************
    * @file     task.h 
    * @date     2021-06-18
    * @brief    任务定义结构体及函数声明
    *
    *********************************************************************
****/
#ifndef TASK_H
#define TASK_H

/*
*********************************************************************
*                      包含头文件
*********************************************************************
*/
#include "list.h"

/*
*********************************************************************
*                       结构类型定义
*********************************************************************
*/
/* 任务句柄定义 */
typedef void * Task_Handle_t;

#define taskYIELD()             portYIELD()

/*
*********************************************************************
*                       函数声明
*********************************************************************
*/
                                
/* 静态创建任务 */
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )

Task_Handle_t xTaskCreateStatic(   TaskFunction_t pxTaskCode,           /* 任务入口 */
                                   const char * const pcName,           /* 任务名称 */
                                   const uint32_t ulStackDepth,         /* 任务栈大小，单位为字 */
                                   void * const pvParameters,           /* 任务形参 */
                                   StackType_t * const puxStackBuffer,  /* 任务栈起始地址 */
                                   TCB_t * const pxTaskBuffer );        /* 任务控制块指针 */
#endif /* configSUPPORT_STATIC_ALLOCATION */

/* 就绪列表初始化 */                                  
void prvInitialiseTaskLists( void );

/* 启动任务调度器 */                                    
void vTaskStartScheduler( void );                                   

void vTaskSwitchContext( void );
                                   
#endif
/* TASK_H */

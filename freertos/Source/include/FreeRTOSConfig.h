/****
    *********************************************************************
    * @file     FreeRTOSConfig.h 
    * @date     2021-06-18
    * @brief    相关配置定义
    *
    *********************************************************************
****/
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/* 重定义中断服务函数名 */
#define xPortPendSVHandler                  PendSV_Handler
#define xPortSysTickHandler                 SysTick_Handler
#define vPortSVCHandler                     SVC_Handler


/* 定义任务配置限制 */
#define configUSE_16_BIT_TICKS              0      /* 数据类型选择16位或32位 */
#define configMAX_TASK_NAME_LEN             ( 16 )    /* 最长字符串任务名 */
#define configSUPPORT_STATIC_ALLOCATION     1      /* 是否静态创建，1为是 */
#define configMAX_PRIORITIES                ( 5 )     /* 最大任务优先级，最多为256个 */

#define configKERNEL_INTERRUPT_PRIORITY     255      /* 内核中断优先级；高四位有效，即等于0xff =15*/
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 191     /* 高四位有效，即等于0xb0 =11 */

#endif
/* FREERTOS_CONFIG_H */

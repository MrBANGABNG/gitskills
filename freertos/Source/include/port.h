/****
    *********************************************************************
    * @file     port.h 
    * @date     2021-06-18
    * @brief    port相关M3内核的处理
    *
    *********************************************************************
****/
#ifndef PORT_H
#define PORT_H


 /*
*********************************************************************
*                      包含头文件
*********************************************************************
*/
#include "portmacro.h"
#include "projdefs.h"


/*
*********************************************************************
*                         函数声明
*********************************************************************
*/
/* 初始化任务栈 */
StackType_t * pxPortInitialiseStack( StackType_t *pxTopOfStack, 
                                     TaskFunction_t pxTaskCode, 
                                     void * pvParameters );  

/* 启动调度器 */
BaseType_t xPortStartScheduler( void );

/* 开始第一个任务,采用汇编编写 */
void prvStartFirstTask( void ) ;

#endif
/* PORT_H */

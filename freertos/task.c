/****
    *********************************************************************
    * @file     task.c 
    * @date     2021-06-18
    * @brief    任务定义及实现
    *
    *********************************************************************
****/

/*
*********************************************************************
*                      包含头文件
*********************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"

/*
*********************************************************************
*                      全局变量
*********************************************************************
*/
/* 定义任务就绪列表；同一优先级的任务统一插入就绪列表的同一链表中 */
List_t pxReadyTasksLists[ configMAX_PRIORITIES ];

static volatile UBaseType_t uxCurrentNumberOfTasks 	= ( UBaseType_t ) 0U;


/* 当前正在运行的任务的任务控制块指针，默认初始化为NULL */
TCB_t * volatile pxCurrentTCB = NULL;

/*
*********************************************************************
*                       函数声明
*********************************************************************
*/
/* 创建新任务 */
static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,            /* 任务入口 */
                                  const char * const pcName,            /* 任务名称 */
                                  const uint32_t ulStackDepth,          /* 任务栈大小，单位为字 */
                                  void * const pvParameters,            /* 任务形参 */
                                  Task_Handle_t * const pxCreateTask,   /* 任务句柄，指向任务TCB */
                                  TCB_t * pxNewTCB );                   /* 任务栈起始地址 */
                                  

/*
*********************************************************************
*                     创建新任务
*********************************************************************
*/
static void prvInitialiseNewTask( TaskFunction_t pxTaskCode,            /* 任务入口 */
                                  const char * const pcName,            /* 任务名称 */
                                  const uint32_t ulStackDepth,          /* 任务栈大小，单位为字 */
                                  void * const pvParameters,            /* 任务形参 */
                                  Task_Handle_t * const pxCreateTask,   /* 任务句柄，指向任务TCB */
                                  TCB_t * pxNewTCB )                    /* 任务栈起始地址 */
{
    StackType_t * pxTopOfStack;
    UBaseType_t x;
    
    /* 获取栈顶指针,数组的最后一个 */
    pxTopOfStack = pxNewTCB->pxStack + (ulStackDepth - ( uint32_t ) 1 );
    /* 向下做8字节对齐=64位，为浮点数运算 */
    pxTopOfStack = ( ( StackType_t * ) \
                    (  ( ( uint32_t )pxTopOfStack ) & ( ~( uint32_t )0x0007 ) ) );
    
    /* 将任务名存储在TCB中 */
    for ( x = ( UBaseType_t )0; x < ( UBaseType_t )configMAX_TASK_NAME_LEN; x++ )
    {
        pxNewTCB->pcTaskName[ x ] = pcName[ x ];
        if( pcName[ x ] == 0x00 )
        {
            break;
        }
    }
    /* 长度限制 */
    pxNewTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = '\0';
    
    /* 初始化TCB中的listitem */
    vListInitialiseItem( & ( pxNewTCB->xStateListItem ) );
    /* 设置节点拥有者 */
    listSET_LIST_ITEM_OWNER( &( pxNewTCB->xStateListItem ), pxNewTCB );
    
    /* 初始化任务栈 */
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack, 
                                pxTaskCode, 
                                pvParameters );
    
    /* 处理句柄，指向控制块 */
    if( ( void * )pxCreateTask != NULL )
    {
        *pxCreateTask = (Task_Handle_t) pxNewTCB;    
    }
}    
                                  
                                  
/*
*********************************************************************
*                     静态创建任务
*********************************************************************
*/
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )

Task_Handle_t xTaskCreateStatic(   TaskFunction_t pxTaskCode,           /* 任务入口 */
                                   const char * const pcName,           /* 任务名称 */
                                   const uint32_t ulStackDepth,         /* 任务栈大小，单位为字 */
                                   void * const pvParameters,           /* 任务形参 */
                                   StackType_t * const puxStackBuffer,  /* 任务栈起始地址 */
                                   TCB_t * const pxTaskBuffer )         /* 任务控制块指针 */
{
    TCB_t *pxNewTCB;                                               
    Task_Handle_t xReturn;
    
    if( ( pxTaskBuffer != NULL ) && ( puxStackBuffer != NULL ) )
    {
        pxNewTCB = ( TCB_t * ) pxTaskBuffer;
        pxNewTCB->pxStack = ( StackType_t * ) puxStackBuffer;
        
        /* 创建新任务 */
        prvInitialiseNewTask( pxTaskCode,       /* 任务入口 */
                              pcName,           /* 任务名称 */
                              ulStackDepth,     /* 任务栈大小，单位为字 */
                              pvParameters,     /* 任务形参 */
                              &xReturn,         /* 任务句柄，指向任务TCB */
                              pxNewTCB );       /* 任务栈起始地址 */
    }
    else
    {
        xReturn = NULL;
    }
    
    /* 返回任务句柄，若创建成功，返回任务控制块 */
    return xReturn;
}

/*
*********************************************************************
*                        就绪列表初始化
*********************************************************************
*/                                 
void prvInitialiseTaskLists( void )
{
    UBaseType_t uxpriority;
    
    for( uxpriority = ( UBaseType_t )0;
         uxpriority < ( UBaseType_t )configMAX_PRIORITIES; 
         uxpriority++ )
    {
        vListInitialise( &( pxReadyTasksLists[ uxpriority ] ) );                       
    } 
}

/*
*********************************************************************
*                        启动任务调度器
*********************************************************************
*/                                 
extern TCB_t Task1TCB;
extern TCB_t Task2TCB;

void vTaskStartScheduler( void )
{
    /* 手动指定第一个运行的任务 */
    pxCurrentTCB = &Task1TCB;
    
    /* 启动调度器 */
    if( xPortStartScheduler() != pdFALSE )
    {
        /* 调度器启动成功，则不会返回，即不会来到这里 */
    }
}

/*
*********************************************************************
*                        启动任务切换
*********************************************************************
*/
void vTaskSwitchContext( void )
{    
    /* 两个任务轮流切换 */
    if( pxCurrentTCB == &Task1TCB )
    {
        pxCurrentTCB = &Task2TCB;
    }
    else
    {
        pxCurrentTCB = &Task1TCB;
    }
}

#endif 
/* configSUPPORT_STATIC_ALLOCATION */

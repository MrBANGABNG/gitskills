/****
    *********************************************************************
    * @file     projdefs.h 
    * @date     2021-06-18
    * @brief    项目定义
    *
    *********************************************************************
****/
#ifndef PROJDEFS_H
#define PROJDEFS_H


/* 任务函数指针，此为空指针 */
typedef void ( *TaskFunction_t )( void * );     

#define pdFALSE             ( ( BaseType_t ) 0 )
#define pdTRUE              ( ( BaseType_t ) 1 )

#define pdFAIL              ( pdFALSE )
#define pdPASS              ( pdTRUE )


#endif
/* PROJDEFS_H */

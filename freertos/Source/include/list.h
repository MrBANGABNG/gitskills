#ifndef LIST_H
#define LIST_H

/*
*********************************************************************
*                      包含头文件
*********************************************************************
*/
#include "portmacro.h"



/*
*********************************************************************
*                      链表节点数据结构定义
*********************************************************************
*/
struct xLIST_ITEM
{
    TickType_t xItemValue;              /* 辅助值，帮助节点顺序排列 */
    struct xLIST_ITEM * pxNext;         /* 指向下一个节点 */
    struct xLIST_ITEM * pxPrevious;     /* 指向上一个节点 */
    void * pvOwner;                     /* 指向拥有该节点的内核对象，通常是TCB */
    void * pvContainer;                 /* 指向节点所在的链表根节点 */
};
typedef struct xLIST_ITEM ListItem_t;   /* 数据类型重定义 */

/*
*********************************************************************
*                      链表精简节点结构定义
*********************************************************************
*/
struct xMINI_LIST_ITEM
{
    TickType_t xItemValue;              /* 链表节点计数器 */
    struct xLIST_ITEM * pxNext;         /* 指向下一个节点 */
    struct xLIST_ITEM * pxPrevious;     /* 指向上一个节点 */
};  
typedef struct xMINI_LIST_ITEM MiniListItem_t;   /* 数据类型重定义 */

/*
*********************************************************************
*                      链表根节点数据结构定义
*********************************************************************
*/
struct xLIST
{
    UBaseType_t uxNumberOfItems;        /* 链表节点计数器 */
    ListItem_t * pxIndex;               /* 链表节点索引指针 */
    MiniListItem_t xListEnd;            /* 链表最后一个节点，也可以算第一个，类似于循环数组 */
};  
typedef struct xLIST List_t;   /* 数据类型重定义 */

/*
*********************************************************************
*                             宏函数声明
*********************************************************************
*/
/* 初始化节点拥有者 */
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )\
        ( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )

/* 获取节点拥有者 */
#define listGET_LIST_ITEM_OWNER( pxListItem )\
        ( ( pxListItem )->pvOwner )

/* 初始化节点排序辅助值 */
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )\
        ( ( pxListItem )->xItemValue =  ( xValue ) )

/* 获取节点排序辅助值 */
#define listGET_LIST_ITEM_VALUE( pxListItem, pxOwner )\
        ( ( pxListItem )->xItemValue )

/* 获取链表根节点的节点计数器的值 */
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )\
        ( ( ( pxList )->xListEnd ).pxNext->xItemValue )

/* 获取链表的入口节点 */
#define listGET_HEAD_ENTRY( pxList )\
        ( ( ( pxList )->xListEnd ).pxNext )

/* 获取节点的下一个节点 */
#define listGET_NEXT( pxListItem )\
        ( ( pxListItem )->pxNext  )       

/* 获取链表的最后一个节点 */
#define listGET_END_MARKER( pxList )\
        ( ( listItem_t * ) ( &( ( pxList )->xListEnd ) ) )
        
/* 获取链表是否为空 */
#define listGET_HEAD_ENTRY( pxList )\
        ( ( ( pxList )->xListEnd ).pxNext )        
        
/*
*********************************************************************
*                         链表处理函数声明
*********************************************************************
*/
/* 链表节点初始化 */
void vListInitialiseItem( ListItem_t * const pxItem ); 

/* 链表根节点初始化 */
void vListInitialise( List_t * const pxList );    

/* 将节点插入链表的尾部 */
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNextListItem);                 

/* 将节点按照升序插入链表 */
void vListInsert( List_t * const pxList, ListItem_t * const pxNextListItem);

/* 将节点从链表中删除 */
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove );

#endif
/* LIST_H */

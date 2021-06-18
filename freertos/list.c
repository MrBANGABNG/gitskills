/*
*********************************************************************
*                      包含头文件
*********************************************************************
*/
#include "list.h"


/*
*********************************************************************
*                      链表节点初始化
*********************************************************************
*/
void vListInitialiseItem( ListItem_t * const pxItem )
{
    /* 初始化该节点所在链表为空，即未插入任何链表 */
    pxItem->pvContainer = NULL;
}

/*
*********************************************************************
*                      链表根节点初始化
*********************************************************************
*/
void vListInitialise( List_t * const pxList )
{
    /* 将链表索引指针指向最后一个节点(或者第一个) */
    pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );
    
    /* 将链表最后一个节点的辅助值设为最大，确保为最后一个节点 */
    pxList->xListEnd.xItemValue = portMAX_DELAY;
    
    /* 将最后一个节点的前后指针都指向自己，代表链表为空 */
    pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );
    pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );
    
    /* 初始化链表节点计数器的值为0，代表链表为空 */
    pxList->uxNumberOfItems  = ( UBaseType_t ) 0U;
}

/*
*********************************************************************
*                      将节点插入链表的尾部
*********************************************************************
*/
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNextListItem)
{
    ListItem_t * const pxIndex = pxList->pxIndex;
    
    pxNextListItem->pxNext = pxIndex;
    pxNextListItem->pxPrevious = pxIndex->pxPrevious;
    pxIndex->pxPrevious = pxNextListItem;
    
    /* 记住该节点所在的链表 */
    pxNextListItem->pvContainer = ( void *) pxList;
    
    /* 计数器++ */
    ( pxList->uxNumberOfItems ) ++ ;
}

/*
*********************************************************************
*                      将节点按照升序插入链表
*********************************************************************
*/
void vListInsert( List_t * const pxList, ListItem_t * const pxNextListItem)
{
    ListItem_t * pxIterator;
    
    /* 获取节点的排序辅助值 */
    const TickType_t xValueOfInsertion = pxNextListItem->xItemValue;
    
    /* 寻找插入位置 */
    if( xValueOfInsertion == portMAX_DELAY )
    {
        pxIterator = pxList->xListEnd.pxPrevious;
    }
    else
    {
        for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd); \
                pxIterator->pxNext->xItemValue <= xValueOfInsertion; \
                pxIterator = pxIterator->pxNext )
        {
            /* NULL，只为了找到要插入的位置 */
        }
    }
    
    /* 插入寻找到的点的后面 */
    pxNextListItem->pxNext = pxIterator->pxNext;
    pxNextListItem->pxNext->pxPrevious = pxNextListItem;
    pxNextListItem->pxPrevious = pxIterator;
    pxIterator->pxNext = pxNextListItem;
    
    /* 记住该节点所在的链表 */
    pxNextListItem->pvContainer = ( void *) pxList;
    
    /* 计数器++ */
    ( pxList->uxNumberOfItems ) ++ ;
}

/*
*********************************************************************
*                      将节点从链表中删除
*********************************************************************
*/
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
    /* 获取所在链表 */
    List_t * const pxList = ( List_t * ) pxItemToRemove->pvContainer;
    
    /* 删除节点 */
    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;
    
    /* 调整索引指针 */
    if ( pxList->pxIndex == pxItemToRemove )
    {
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }
    
    /* 初始化链表为空 */
    pxItemToRemove->pvContainer = NULL;
    
    /* 计数器-- */
    ( pxList->uxNumberOfItems ) -- ;
    
    /* 返回链表剩余节点个数 */
    return pxList->uxNumberOfItems;
}

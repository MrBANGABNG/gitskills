/*
*********************************************************************
*                           包含头文件
*********************************************************************
*/
#include "list.h"

/*
*********************************************************************
*                           全局变量
*********************************************************************
*/

/* 定义链表根节点 */
struct xLIST        List_Test;

/* 定义节点 */
struct xLIST_ITEM   List_Item1;
struct xLIST_ITEM   List_Item2;
struct xLIST_ITEM   List_Item3;


/*
*********************************************************************
*                           main()函数
*********************************************************************
*/
int main(void)
{
    /* 初始化根节点 */
    vListInitialise( &List_Test );
    
    /* 初始化节点1/2/3 */
    vListInitialiseItem( &List_Item1 );
    List_Item1.xItemValue = 1;
    
    vListInitialiseItem( &List_Item2 );
    List_Item2.xItemValue = 2;
    
    vListInitialiseItem( &List_Item3 );
    List_Item3.xItemValue = 3;
    
    /* 插入列表 */
    vListInsert( &List_Test, &List_Item2 );
    vListInsert( &List_Test, &List_Item1 );
    vListInsert( &List_Test, &List_Item3 );
    
    for(;;)
    {
         /* 无操作 */
    } 
}

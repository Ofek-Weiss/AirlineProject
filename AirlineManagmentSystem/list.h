/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "def.h"


/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);

NODE* L_insert_sorted(LIST* pList, DATA Value, int (*compare)(const void*, const void*));

BOOL L_delete(NODE* pNode, void (*freeKey)(void*));// erase node after *pNode

NODE* L_find(NODE* pNode, DATA Value, int (*compare)(const void*, const void*));// return a pointer to the node 

BOOL L_free(LIST* pList, void (*freeKey)(void*));// free list memory

int L_print(LIST* pList, void (*printer)(void*));// print the list content

NODE* find_sorted_location(NODE* pNode, DATA Value, int (*compare)(const void*, const void*));

int L_count(const LIST* lst);

#endif

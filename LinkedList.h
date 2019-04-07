#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "Basic.h"


// algorithms:

#define LIST_FORALL_BEGIN(LIST,ELEMENT,DATA,pList,index,pEl) \
{ \
	ELEMENT* pEl = LIST##_get_first( pList ); \
	for( unsigned int index=0; index<LIST##_get_size( pList ); index++ ) \
	{

#define LIST_FORALL_END(LIST,ELEMENT,DATA,pList,index,pEl) \
		pEl = LIST##_get_next( pList, pEl ); \
	} \
}

#define LIST_FORALL_REV_BEGIN(LIST,ELEMENT,DATA,pList,index,pEl) \
{ \
	ELEMENT* pEl = LIST##_get_last( pList ); \
	for( unsigned int index=0; index<LIST##_get_size( pList ); index++ ) \
	{

#define LIST_FORALL_REV_END(LIST,ELEMENT,DATA,pList,index,pEl) \
		pEl = LIST##_get_prev( pList, pEl ); \
	} \
}

/* -----------------------------------*/
// list:
/* -----------------------------------*/

// declare list

#define DECL_LIST(LIST,ELEMENT,DATA,MALLOC,FREE,DELDATA)\
struct S##ELEMENT\
{\
    struct S##ELEMENT* pPrev;\
    struct S##ELEMENT* pNext;\
    DATA* pData;\
};\
\
typedef struct S##ELEMENT ELEMENT;\
\
struct S##LIST\
{\
	unsigned int size;\
	ELEMENT* pHead;\
};\
\
typedef BOOL (*LIST##PCompareFunction) (DATA* pInList, DATA* p);\
typedef struct S##LIST LIST;

// define list:

#define DEF_LIST(LIST,ELEMENT,DATA,MALLOC,FREE,DELDATA)\
INLINE void LIST##_init(LIST* pList);\
INLINE void LIST##_exit(LIST* pList);\
\
INLINE int LIST##_is_empty(LIST* pList);\
INLINE unsigned int LIST##_get_size(LIST* pList);\
\
INLINE ELEMENT* LIST##_get_first(LIST* pList) ;\
INLINE ELEMENT* LIST##_get_last(LIST* pList) ;\
INLINE int LIST##_has_next(LIST* pList, ELEMENT* element);\
INLINE int LIST##_has_prev(LIST* pList, ELEMENT* element);\
INLINE ELEMENT* LIST##_get_element_from_pointer(LIST* pList, DATA* pData);\
INLINE ELEMENT* LIST##_get_element(LIST* pList, DATA* pData, LIST##PCompareFunction pCompareFunction);\
INLINE ELEMENT* LIST##_get_next(LIST* pList, ELEMENT* element) ;\
INLINE ELEMENT* LIST##_get_prev(LIST* pList, ELEMENT* element);\
\
INLINE void LIST##_clear(LIST* pList);\
INLINE ELEMENT* LIST##_append(LIST* pList, DATA* pData);\
INLINE ELEMENT* LIST##_prepend(LIST* pList, DATA* pData);\
INLINE ELEMENT* LIST##_insert(LIST* pList, DATA* pData, ELEMENT* pElement);\
INLINE void LIST##_del(LIST* pList, ELEMENT* element);\
\
INLINE void LIST##_init(LIST* pList)\
{\
    pList->size= 0;\
    pList->pHead= NULL;\
}\
INLINE void LIST##_exit(LIST* pList)\
{ \
	LIST##_clear(pList); \
} \
\
INLINE void LIST##_clear(LIST* pList)\
{\
	if(! LIST##_is_empty(pList))\
	{\
		ELEMENT* pCurrent= pList->pHead->pPrev;\
		pList->pHead->pPrev = NULL;\
		while(pCurrent->pPrev)\
		{\
			DELDATA(pCurrent->pData, sizeof( DATA ) ); \
			pCurrent = pCurrent -> pPrev;\
			FREE(pCurrent->pNext,sizeof(ELEMENT));\
			pCurrent->pNext = NULL;\
		}\
		DELDATA(pCurrent->pData, sizeof( DATA )); \
		FREE(pCurrent,sizeof(ELEMENT));\
	}\
	LIST##_init(pList); \
}\
\
INLINE int LIST##_is_empty(LIST* pList)\
{\
    return pList->pHead == NULL;\
}\
INLINE unsigned int LIST##_get_size(LIST* pList)\
{\
    return pList->size;\
}\
\
INLINE ELEMENT* LIST##_get_first(LIST* pList)\
{\
    if(!LIST##_is_empty(pList))\
        return pList->pHead;\
    return NULL;\
}\
INLINE ELEMENT* LIST##_get_last(LIST* pList)\
{\
    if(!LIST##_is_empty(pList))\
        return pList->pHead->pPrev;\
    return NULL;\
}\
INLINE int LIST##_has_next(LIST* pList, ELEMENT* element)\
{\
    return (element->pNext != pList-> pHead);\
}\
INLINE int LIST##_has_prev(LIST* pList, ELEMENT* element)\
{\
    return (element != pList-> pHead);\
}\
\
INLINE ELEMENT* LIST##_get_element_from_pointer(LIST* pList,DATA* pData)\
{\
	if(!LIST##_is_empty(pList))\
	{\
		ELEMENT* pCurrent= pList-> pHead;\
		do\
		{\
			if( (pCurrent-> pData) == pData)\
				return pCurrent;\
			pCurrent = pCurrent-> pNext;\
		}\
		while(pCurrent!= pList-> pHead);\
	}\
	return NULL;\
}\
INLINE ELEMENT* LIST##_get_element(LIST* pList, DATA* pData, LIST##PCompareFunction pCompareFunction)\
{\
	if(!LIST##_is_empty(pList))\
	{\
		ELEMENT* pCurrent= pList-> pHead;\
		do\
		{\
			if( pCompareFunction((pCurrent-> pData), pData) )\
				return pCurrent;\
			pCurrent = pCurrent-> pNext;\
		}\
		while(pCurrent!= pList-> pHead);\
	}\
	return NULL;\
}\
INLINE ELEMENT* LIST##_get_next(LIST* pList, ELEMENT* element)\
{\
    if(LIST##_has_next(pList,element))\
        return element->pNext;\
    return NULL;\
}\
INLINE ELEMENT* LIST##_get_prev(LIST* pList, ELEMENT* element)\
{\
    if(LIST##_has_prev(pList,element))\
        return element->pPrev;\
    return NULL;\
}\
\
INLINE ELEMENT* LIST##_append(LIST* pList, DATA* pData)\
{\
    ELEMENT* e= (ELEMENT* )MALLOC(sizeof(ELEMENT));\
    e -> pData = pData;\
	if( LIST##_is_empty(pList))\
	{\
		pList->pHead = e;\
		e-> pPrev = e -> pNext = e;\
	}\
	else\
	{\
		ELEMENT* prev = pList->pHead->pPrev;\
		prev->pNext = e;\
		e-> pPrev = prev;\
		pList->pHead->pPrev = e;\
		e-> pNext = pList-> pHead;\
	}\
	pList->size++;\
	return e;\
}\
\
INLINE ELEMENT* LIST##_prepend(LIST* pList, DATA* pData)\
{\
	ELEMENT* e = LIST##_append( pList, pData ); \
	pList -> pHead = pList-> pHead -> pPrev; \
	return e;\
}\
\
INLINE ELEMENT* LIST##_insert(LIST* pList, DATA* pData, ELEMENT* pElement)\
{\
    ELEMENT* e= (ELEMENT* )MALLOC(sizeof(ELEMENT));\
    e-> pData = pData;\
        ELEMENT* pPrev= pElement;\
        ELEMENT* pNext= pElement->pNext;\
		pPrev->pNext = e;\
		e-> pPrev= pPrev;\
		pNext->pPrev = e;\
		e-> pNext = pNext;\
		pList->size++;\
	return e;\
}\
\
INLINE void LIST##_del(LIST* pList, ELEMENT* element)\
{\
	if( pList->size == 0 ) { \
		return; \
	} \
	else if( pList-> pHead-> pNext != pList-> pHead ) {\
		DELDATA(element->pData, sizeof( DATA )); \
		if( element == pList-> pHead )\
			pList-> pHead = pList-> pHead-> pNext;\
		element-> pPrev->pNext = element-> pNext;\
		element-> pNext-> pPrev = element-> pPrev;\
		FREE(element,sizeof(ELEMENT));\
	}\
	else\
	{\
		DELDATA(element->pData, sizeof( DATA )); \
		FREE(element,sizeof(ELEMENT));\
		pList->pHead = NULL;\
	}\
	pList->size--;\
}

#endif

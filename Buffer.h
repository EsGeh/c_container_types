#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Basic.h"


#define DECL_BUFFER(BUF_TYPE,EL_TYPE,MALLOC,FREE) \
 \
typedef struct S##BUF_TYPE{ \
	unsigned int size; \
	EL_TYPE* array; \
} BUF_TYPE;

#define DEF_BUFFER(BUF_TYPE,EL_TYPE,MALLOC,FREE) \
 \
INLINE void BUF_TYPE##_init( \
	BUF_TYPE* buf, \
	unsigned int size \
) \
{ \
	buf -> size = size; \
	buf->array = MALLOC( sizeof( EL_TYPE ) * size ); \
} \
 \
INLINE void BUF_TYPE##_exit( \
	BUF_TYPE* buf \
) \
{ \
	FREE( buf->array, sizeof( EL_TYPE ) * buf->size ); \
	buf -> array = NULL; \
	buf -> size = 0; \
} \
INLINE unsigned int BUF_TYPE##_get_size( \
	BUF_TYPE* buf \
) \
{ \
	return buf->size; \
} \
 \
INLINE EL_TYPE* BUF_TYPE##_get_array( \
	BUF_TYPE* buf \
) \
{ \
	return buf->array; \
} \
 \
INLINE void BUF_TYPE##_resize( \
	BUF_TYPE* buf, \
	unsigned int size \
) \
{ \
	EL_TYPE* newA; \
	newA = MALLOC( sizeof( EL_TYPE ) * size ); \
	memcpy( newA, buf->array, sizeof( EL_TYPE ) * min( buf->size, size ) ); \
	FREE( buf->array, sizeof( EL_TYPE ) * buf->size ); \
	buf -> size = size; \
	buf->array = newA; \
} \
INLINE void BUF_TYPE##_double_size( \
	BUF_TYPE* buf \
) \
{ \
	BUF_TYPE##_resize( buf, buf->size * 2 ); \
}

#endif

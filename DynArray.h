#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_

#include "Buffer.h"


#define DECL_DYN_ARRAY(ARRAY_TYPE,EL_TYPE,MALLOC,FREE) \
	DECL_BUFFER(ARRAY_TYPE##Buf,EL_TYPE,MALLOC,FREE) \
	DECL_DYN_ARRAY_IMPL(ARRAY_TYPE,EL_TYPE,ARRAY_TYPE##Buf)

#define DEF_DYN_ARRAY(ARRAY_TYPE,EL_TYPE,MALLOC,FREE) \
	DEF_BUFFER(ARRAY_TYPE##Buf,EL_TYPE,MALLOC,FREE) \
	DEF_DYN_ARRAY_IMPL(ARRAY_TYPE,EL_TYPE,ARRAY_TYPE##Buf)


#define DECL_DYN_ARRAY_IMPL(ARRAY_TYPE,EL_TYPE,BUF_TYPE) \
 \
typedef struct S##ARRAY_TYPE { \
	int size; \
	BUF_TYPE buffer; \
} ARRAY_TYPE;


#define DEF_DYN_ARRAY_IMPL(ARRAY_TYPE, EL_TYPE, BUF_TYPE) \
\
INLINE void ARRAY_TYPE##_init( \
	ARRAY_TYPE* array \
) \
{ \
	BUF_TYPE##_init( &array->buffer, 2); \
	array -> size = 0; \
} \
\
INLINE void ARRAY_TYPE##_exit( \
	ARRAY_TYPE* array \
) \
{ \
	BUF_TYPE##_exit( &array->buffer); \
} \
\
INLINE int ARRAY_TYPE##_get_size( \
	ARRAY_TYPE* array \
) \
{ \
	return array->size; \
} \
 \
INLINE EL_TYPE* ARRAY_TYPE##_get_array( \
	ARRAY_TYPE* array \
) \
{ \
	return BUF_TYPE##_get_array( & array->buffer ); \
} \
\
INLINE int ARRAY_TYPE##_get_alloc_size( \
	ARRAY_TYPE* array \
) \
{ \
	return BUF_TYPE##_get_size( & array->buffer ); \
} \
 \
INLINE void ARRAY_TYPE##_set_size( \
	ARRAY_TYPE* array, \
	int size \
) \
{ \
	if( size > ARRAY_TYPE##_get_alloc_size( array ) ) \
	{ \
		BUF_TYPE##_resize( & array->buffer, size ); \
	} \
	array->size = size; \
} \
 \
INLINE void ARRAY_TYPE##_append( \
	ARRAY_TYPE* array, \
	EL_TYPE el \
) \
{ \
	if( ARRAY_TYPE##_get_size( array ) + 1 > ARRAY_TYPE##_get_alloc_size( array ) ) \
	{ \
		BUF_TYPE##_double_size( & array->buffer ); \
	} \
	BUF_TYPE##_get_array( & array->buffer )[array->size] = el; \
	array->size ++; \
} \
\
INLINE void ARRAY_TYPE##_clear( \
	ARRAY_TYPE* array \
) \
{ \
	array->size = 0; \
}

#endif

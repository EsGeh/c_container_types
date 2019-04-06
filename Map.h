#ifndef _MAP_H_
#define _MAP_H_

#include "LinkedList.h"

#define MAP_FORALL_KEYS_BEGIN(MAP,KEY,map,key) \
	LIST_FORALL_BEGIN(MAP##_KeyList,MAP##_KeyListEl,KEY, MAP##_get_keys( map),i,keyEl) \
	KEY key = *keyEl->pData;

#define MAP_FORALL_KEYS_END(MAP,KEY,map,key) \
	LIST_FORALL_END(MAP##_KeyList,MAP##_KeyListEl,KEY, MAP##_get_keys( map),i,keyEl)

#define DECL_MAP(MAP,KEY,TYPE,MALLOC,FREE,DEL_TYPE,HASH, COMPARE_KEYS) \
typedef struct \
{ \
	KEY key; \
	TYPE* value; \
}  MAP##_Entry; \
\
INLINE void MAP##_free_entry( \
	MAP##_Entry* entry, \
	int size \
) \
{ \
	DEL_TYPE( entry->value, sizeof( TYPE ) ); \
	FREE( entry, sizeof( MAP##_Entry ) );\
} \
\
DECL_LIST(MAP##_Bucket, MAP##_BucketEl, MAP##_Entry, MALLOC,FREE,MAP##_free_entry) \
DEF_LIST(MAP##_Bucket, MAP##_BucketEl, MAP##_Entry, MALLOC,FREE,MAP##_free_entry) \
 \
DECL_BUFFER(MAP##_Buckets,MAP##_Bucket, MALLOC, FREE) \
DEF_BUFFER(MAP##_Buckets,MAP##_Bucket, MALLOC, FREE) \
 \
DECL_LIST(MAP##_KeyList, MAP##_KeyListEl, KEY, MALLOC,FREE,FREE) \
DEF_LIST(MAP##_KeyList, MAP##_KeyListEl, KEY, MALLOC,FREE,FREE) \
 \
struct S##MAP \
{ \
	MAP##_Buckets buckets; \
	MAP##_KeyList keys; \
} ; \
 \
typedef struct S##MAP MAP;


#define DEF_MAP(MAP,KEY,TYPE,MALLOC,FREE,DEL_TYPE,HASH,COMPARE_KEYS ) \
INLINE void MAP##_init( MAP* map, int size) \
{ \
	MAP##_Buckets##_init( & map->buckets, size ); \
	for( int i=0; i<size; i++ ) \
	{ \
		MAP##_Bucket##_init( \
			& MAP##_Buckets_get_array( & map->buckets )[i]  \
		); \
	} \
	MAP##_KeyList##_init( & map->keys ); \
} \
 \
INLINE void MAP##_exit( MAP* map ) \
{ \
	for( int i=0; i< MAP##_Buckets_get_size( & map->buckets ); i++ ) \
	{ \
		MAP##_Bucket##_exit( \
			& MAP##_Buckets_get_array( & map->buckets )[i]  \
		); \
	} \
	MAP##_Buckets##_exit( & map->buckets ); \
	MAP##_KeyList##_exit( & map->keys ); \
} \
 \
INLINE MAP##_Bucket* MAP##_priv_find_bucket( \
	MAP* map, \
	KEY key \
) \
{ \
	int size = MAP##_Buckets_get_size( & map->buckets ); \
	int hash = HASH( key ) % size ; \
	return & MAP##_Buckets_get_array( & map -> buckets )[ hash ]; \
} \
 \
INLINE MAP##_BucketEl* MAP##_priv_find_bucket_el( \
	MAP##_Bucket* bucket, \
	KEY key \
) \
{ \
	LIST_FORALL_BEGIN(MAP##_Bucket,MAP##_BucketEl,Entry,bucket,index,pEl) \
		if( pEl->pData->key == key ) \
			return pEl; \
	LIST_FORALL_END(MAP##_Bucket,MAP##_BucketEl,Entry,bucket,index,pEl) \
	return NULL; \
} \
 \
INLINE int MAP##_get_size( MAP* map ) \
{ \
	return MAP##_KeyList##_get_size( & map->keys ); \
} \
 \
INLINE void MAP##_delete( \
	MAP* map, \
	KEY key \
) \
{ \
	MAP##_Bucket* bucket = MAP##_priv_find_bucket( map, key ); \
	MAP##_BucketEl* bucketEl = MAP##_priv_find_bucket_el( bucket, key ); \
	if( bucketEl != NULL ) \
	{ \
		MAP##_Bucket##_del( bucket, bucketEl ); \
	} \
	MAP##_KeyListEl* pKeyEl = MAP##_KeyList##_get_element( & map->keys, & key, &COMPARE_KEYS); \
	MAP##_KeyList##_del( & map->keys, pKeyEl ); \
} \
 \
INLINE void MAP##_insert( \
	MAP* map, \
	KEY key, \
	TYPE* x \
) \
{ \
	KEY* new_key = MALLOC( sizeof( KEY ) ); \
	(*new_key) = key; \
	MAP##_KeyList##_append( & map->keys, new_key ); \
	MAP##_Bucket* bucket = MAP##_priv_find_bucket( map, key ); \
	MAP##_BucketEl* bucketEl = MAP##_priv_find_bucket_el( bucket, key ); \
	if( bucketEl != NULL ) \
		MAP##_Bucket##_del( bucket, bucketEl ); \
 \
	MAP##_Entry* entry = MALLOC( sizeof( MAP##_Entry ) ); \
	entry->key = key; \
	entry->value = x; \
	MAP##_Bucket##_append( bucket, entry ); \
} \
 \
INLINE TYPE* MAP##_get( \
	MAP* map, \
	KEY key \
) \
{ \
	MAP##_Bucket* bucket = MAP##_priv_find_bucket( map, key ); \
	MAP##_BucketEl* bucketEl = MAP##_priv_find_bucket_el( bucket, key ); \
	if( bucketEl == NULL ) \
		return NULL; \
	return bucketEl->pData->value; \
} \
 \
INLINE MAP##_KeyList* MAP##_get_keys( \
	MAP* map \
) \
{ \
	return & map->keys; \
} \
 \
INLINE void MAP##_clear( \
	MAP* map \
) \
{ \
	for( int i=0; i< MAP##_Buckets_get_size( & map->buckets ); i++ ) \
	{ \
		MAP##_Bucket##_clear( \
			& MAP##_Buckets_get_array( & map->buckets )[i]  \
		); \
	} \
	MAP##_KeyList##_clear( & map->keys ); \
}

#endif



#include "Buffer.h"
#include "DynArray.h"
#include "LinkedList.h"
#include "Map.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int mem_count = 0;


void* MALLOC(int size)
{
	#ifdef DB_PRINT_MEM
	printf("MALLOC(%i)\n",size);
	#endif
	mem_count += size;
	return malloc(size);
}

void FREE(void* x, int size)
{
	#ifdef DB_PRINT_MEM
	printf("FREE(%i)\n",size);
	#endif
 	mem_count -= size;
	free(x);
}

DECL_BUFFER(TestBuf,int, MALLOC, FREE)
DEF_BUFFER(TestBuf,int, MALLOC, FREE)

DECL_DYN_ARRAY(DynA, int, MALLOC, FREE)
DEF_DYN_ARRAY(DynA, int, MALLOC, FREE)

DECL_LIST(List, El, int, MALLOC, FREE, FREE)
DEF_LIST(List, El, int, MALLOC, FREE, FREE)

#define HASH_INT(key) (key)
BOOL compare_ints( int* x, int* y ) { return *x == *y; }

DECL_MAP(Map, int, char, MALLOC, FREE, FREE, HASH_INT, compare_ints)
DEF_MAP(Map, int, char, MALLOC, FREE, FREE, HASH_INT, compare_ints)

void test_buffer();
void test_dynarray();
void test_linkedlist(); /* TODO: test all functions: */
void test_map(); /* TODO: test all functions: */

int main()
{

	printf("****************************\n");
	printf("testing buffer:\n");
	printf("****************************\n");
	test_buffer();
	printf("\n");

	printf("****************************\n");
	printf("testing dynamic array:\n");
	printf("****************************\n");
	test_dynarray();
	printf("\n");

	printf("****************************\n");
	printf("testing linked list:\n");
	printf("****************************\n");
	test_linkedlist();
	printf("\n");

	printf("****************************\n");
	printf("testing map:\n");
	printf("****************************\n");
	test_map();
	printf("\n");

	printf("all tests passed :-)\n");
}

#define SHOW_BUFFER(CONT_TYPE,cont) \
{ \
	printf("content: "); \
	for(int i=0; i< CONT_TYPE##_get_size( cont ); i++ ) \
	{ \
		printf("%i", CONT_TYPE##_get_array( cont )[i] ); \
		if( i+1 < CONT_TYPE##_get_size( cont ) ) \
			printf( " " ); \
	} \
	printf( "\n" ); \
}

#define SHOW_LIST(CONT_TYPE,EL_TYPE,cont) \
{ \
	printf("content: "); \
	LIST_FORALL_BEGIN( CONT_TYPE, EL_TYPE, DATA, cont, i, el ) \
		printf("%i", *(el->pData) ); \
		if( el != CONT_TYPE##_get_last( cont ) ) \
			printf( " " ); \
	LIST_FORALL_END( CONT_TYPE, EL_TYPE, DATA, cont, i, el ) \
	printf( "\n" ); \
}

void test_buffer()
{
	TestBuf container;
	printf( "init container (with 1 el)...\n" );
	TestBuf_init( &container, 1);
	{
		SHOW_BUFFER( TestBuf, &container )

		printf( "set size = 2...\n" );
		TestBuf_resize( &container, 2 );
		assert( TestBuf_get_size( &container ) == 2);
		SHOW_BUFFER( TestBuf, &container )

		printf( "doubling...\n" );
		TestBuf_double_size( &container );
		assert( TestBuf_get_size( &container ) == 4);
		SHOW_BUFFER( TestBuf, &container )
	}
	TestBuf_exit( &container );
	printf( "mem_count: %i\n", mem_count);
	assert( mem_count == 0 );
}

void test_dynarray()
{
	DynA container;
	printf( "init container...\n" );
	DynA_init( &container );
	{
		SHOW_BUFFER( DynA, &container )

		printf( "append(1)...\n" );
		DynA_append( &container, 1 );
		assert( DynA_get_size( &container ) == 1);
		SHOW_BUFFER( DynA, &container )

		printf( "append(2)...\n" );
		DynA_append( &container, 2 );
		assert( DynA_get_size( &container ) == 2);
		SHOW_BUFFER( DynA, &container )

		printf( "append(3)...\n" );
		DynA_append( &container, 3 );
		assert( DynA_get_size( &container ) == 3);
		SHOW_BUFFER( DynA, &container )

	}
	DynA_exit( &container );
	printf( "mem_count: %i\n", mem_count);
	assert( mem_count == 0 );
}

// TODO: test all list functions:
void test_linkedlist()
{
	List container;
	printf( "init container...\n" );
	List_init( &container );
	{
		int size = List_get_size( &container );
		printf( "size: %i\n", size );

		printf( "append(1)...\n" );
		{
			int* new = MALLOC( sizeof( int ) );
			*new = 1;
			List_append( &container, new );
			SHOW_LIST( List, El, &container )
		}

		printf( "append(2)...\n" );
		{
			int* new = MALLOC( sizeof( int ) );
			*new = 2;
			List_append( &container, new );
			SHOW_LIST( List, El, &container )
		}

		printf( "prepend(0)...\n" );
		{
			int* new = MALLOC( sizeof( int ) );
			*new = 0;
			List_prepend( &container, new );
			SHOW_LIST( List, El, &container )
		}

		printf( "del(first->next)...\n" );
		{
			El* el = List_get_first( &container );
			el = List_get_next( &container, el );
			List_del( &container, el );
			SHOW_LIST( List, El, &container )
		}

	}
	List_exit( &container );
	printf( "mem_count: %i\n", mem_count);
	assert( mem_count == 0 );
}

void test_map() /* TODO: test all functions: */
{
	Map container;
	printf( "init container...\n" );
	Map_init( &container, 4);
	{

		{
			assert( Map_get( &container, 1 ) ==  NULL );
			assert( Map_KeyList_get_size( Map_get_keys( &container ) ) == 0 );
		}

		printf( "append(1 -> 'a')...\n" );
		{
			char* new = MALLOC( sizeof( char ) );
			*new = 'a';
			Map_insert( &container, 1, new );
			assert( *Map_get( &container, 1 ) ==  'a' );
			assert( Map_KeyList_get_size( Map_get_keys( &container ) ) == 1 );
		}

		printf( "append(2 -> 'b')...\n" );
		{
			char* new = MALLOC( sizeof( char ) );
			*new = 'b';
			Map_insert( &container, 2, new );
			assert( *Map_get( &container, 2 ) ==  'b' );
			assert( Map_KeyList_get_size( Map_get_keys( &container ) ) == 2 );
		}

		printf( "append(3 -> 'c')...\n" );
		{
			char* new = MALLOC( sizeof( char ) );
			*new = 'c';
			Map_insert( &container, 3, new );
			assert( *Map_get( &container, 3 ) ==  'c' );
			assert( Map_KeyList_get_size( Map_get_keys( &container ) ) == 3 );
		}

		printf( "delete(2)...\n" );
		{
			Map_delete( &container, 2 );
			assert( Map_get( &container, 2 ) ==  NULL );
			assert( Map_KeyList_get_size( Map_get_keys( &container ) ) == 2 );
		}
		
		printf( "keys:\n" );
		MAP_FORALL_KEYS_BEGIN(Map,int,&container,key)
			printf( "key: %i\n", key );
		MAP_FORALL_KEYS_END(Map,int,&container,key)
		/*
		Map_KeyList* keys = Map_get_keys( &container );
		LIST_FORALL_BEGIN(Map_KeyList,Map_KeyListEl,int,keys,i,pKeyEl)
			printf( "key: %i\n", * pKeyEl->pData );
		LIST_FORALL_END(Map_KeyList,Map_KeyListEl,int,keys,i,pKeyEl)
		*/

	}
	Map_exit( &container );
	printf( "mem_count: %i\n", mem_count);
	assert( mem_count == 0 );
}

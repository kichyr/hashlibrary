#ifndef _HASH_LIB_H_
#define _HASH_LIB_H_
#include <stdio.h>

typedef enum {
	STERR_SUCCESS = 0,
	STERR_OOM,
	STERR_FULL,
	STERR_EMPTY,
	STERR_INVSIZE,
	STERR_INVPTR,
} STERR;


typedef struct Data {
    size_t size;
    void* arr;
} Data;

typedef struct Linked_List {
	Data data;
	struct Linked_List* next;
	struct Linked_List* prev;
} LList;


LList** TABLE; //

int get_hash_BLOB(Data data);

void create_hash_table(size_t table_size);

void  htable_search();

void  htable_insert();

void htable_print();

void hash_table_remove();

#endif //_HASH_LIB_H_
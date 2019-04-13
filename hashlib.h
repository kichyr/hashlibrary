#ifndef _HASH_LIB_H_
#define _HASH_LIB_H_
#include <stdio.h>

typedef enum {
	HTERR_SUCCESS = 0,
	HTERR_NO_SUCH_ELEM,
	HTERR_INVPTR,
} HTERR;


typedef struct Data {
    size_t size;
    void* arr;
} Data;

typedef struct Linked_List {
	Data data;
	struct Linked_List* next;
	struct Linked_List* prev;
} LList;

typedef struct TABLE
{
	LList** table;
	size_t table_size;
	int number_collisions;
} TABLE;



//LList** TABLE; //

int get_hash_BLOB(Data data, size_t table_size);

TABLE* create_hash_table(size_t table_size); //возвращает указатель на созданную

//Возвращает указатель на сохраненные в таблице данные и NULL в случае, если в таблице таких данных нет
Data*  htable_search(TABLE* TABLE, Data d, HTERR* err);

 //удаляет элемент из таблицы, возвращает 0 в случае успеха
int htable_remove_element(TABLE* TABLE, Data d, HTERR *err);

void  htable_insert(TABLE* TABLE, Data d, HTERR *err);

void htable_print(TABLE* TABLE, HTERR *err);

void htable_remove(TABLE* TABLE, HTERR *err);

#endif //_HASH_LIB_H_
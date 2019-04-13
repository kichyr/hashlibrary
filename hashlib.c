#include <stdlib.h>
#include"hashlib.h"



//---------------------------------hash function-----------------------------------

int get_hash_BLOB(Data data, size_t table_size/*, HT_ERR* err*/) {
    int hash = 0;
    size_t iterator = data.size/table_size+1;
    char* c_data = (char*)data.arr;

    for (int i = 0; i < data.size; i+=iterator) {
        hash = (hash+(i+3)*c_data[i])%table_size;
    }
    return hash;
}



//---------------------------------insert_element-----------------------------------
// Копирует из ptr1 в ptr2 и выделяет память
void copy(void* ptr1, void** ptr2, size_t size){
    *ptr2 = malloc(size);
    char* c_ptr1 = (char*)ptr1;
    char* c_ptr2 = (char*)*ptr2;
    for(int i = 0; i < size; i++)
        c_ptr2[i] = c_ptr1[i]; 
}

void htable_insert(TABLE* TABLE, Data d, HTERR *err) {
    *err = HTERR_SUCCESS;
    if(TABLE == NULL) {
        *err = HTERR_INVPTR;
        return;
    }
    int hash = get_hash_BLOB(d, TABLE->table_size);
    LList* list = TABLE->table[hash];
    LList* new = (LList*)malloc(sizeof(LList));
    copy(d.arr, &(new->data.arr), d.size);

    while(list != NULL && list->next != NULL)
        list = list->next;
    if(list != NULL) {
        list->next = new;
        list->next->prev = list;
        list = list->next;
        list->next = NULL;
    } else {
        TABLE->table[hash] = new;
        list = new;
        list->next = NULL;
        list->prev = NULL;
    }    
    list->data.size = d.size;
}

//-------------------------------printing table--------------------------------

//выводит хеш таблицу
void htable_print(TABLE* TABLE, HTERR *err) {
    *err = HTERR_SUCCESS;
    if(TABLE == NULL) {
        *err = HTERR_INVPTR;
        return;
    }
    LList* x;
    for(int i = 0; i < TABLE->table_size; i++) {
        x = TABLE->table[i];
        printf("for hash %i:\n", i);
        while(x != NULL) {
            printf("    ");
            char* test_print = (char*)x->data.arr;
            for(int i = 0; i < x->data.size; i++) {
                printf("%i, ",((char *)x->data.arr)[i]);
            }
            x = x->next;
            printf("\n");
        }
    }
}

//-------------------------------Creating Table---------------------------------

// Выделяется память под основной массив/фиксируется размер таблицы
TABLE* create_hash_table(size_t table_size) {
    TABLE* T = (TABLE*)malloc(sizeof(TABLE));
    T->table_size = table_size;
    T->number_collisions = 0;
    T->table = (LList**) malloc(table_size*sizeof(LList*));
    for(int i = 0; i < table_size; i++)
        T->table[i] = NULL;
    return T;
}

//-----------------------------Searching Element---------------------------------
//Сравнивает data1, data2 возвращает 0 в случае равенства -1 в противном случае
int compare_data(Data d1, Data d2) {
    if(d1.size != d2.size)
        return -1;
    char* arr1 = (char*)d1.arr;
    char* arr2 = (char*)d2.arr;
    for(size_t i = 0; i < d1.size; i++)
        if(arr1[i] != arr2[i])
            return -1;
    return 0;
}

LList** htable_search_List(TABLE* TABLE, Data d) {
    LList** candidate = &TABLE->table[get_hash_BLOB(d, TABLE->table_size)];
    while(*candidate != NULL) {
        if(compare_data((*candidate)->data, d) == 0)
            return candidate;
        *candidate = (*candidate)->next;
    }
    return NULL;
}

//Возвращает указатель на сохраненные в таблице данные и NULL в случае, если в таблице таких данных нет
Data* htable_search(TABLE* TABLE, Data d, HTERR* err) {
    *err = HTERR_SUCCESS;
    if(TABLE == NULL) {
        *err = HTERR_INVPTR;
        return NULL;
    }

    LList** l = htable_search_List(TABLE, d);
    if(l != NULL)
        return &((*l)->data);
    return NULL;
}

//------------------------------Removing element---------------------------------
//not tested
int htable_remove_element(TABLE* TABLE, Data d, HTERR *err) {
    *err = HTERR_SUCCESS;
    if(TABLE == NULL) {
        *err = HTERR_INVPTR;
        return -1;
    }

    LList** l = htable_search_List(TABLE, d);

    if( l == NULL ) {
        *err = HTERR_NO_SUCH_ELEM;
        return -1;
    }
    if((*l)->prev != NULL)
        (*l)->prev->next = (*l)->next;
    if((*l)->next != NULL)
        (*l)->next->prev = (*l)->prev;
    free((*l)->data.arr);
    free((*l));
    (*l) = NULL;
    return 0;
}


//------------------------------Removing Table-----------------------------------
void htable_remove(TABLE* TABLE, HTERR *err) {
    *err = HTERR_SUCCESS;
    if(TABLE == NULL) {
        *err = HTERR_INVPTR;
        return;
    }

    LList *x, *y;
    for(int i = 0; i < TABLE->table_size; i++) {
        x = TABLE->table[i];
        while(x != NULL) {
            free(x->data.arr);
            y = x;
            x = x->next;
            free(y);
        }
    }
    free(TABLE->table);
    free(TABLE);
}
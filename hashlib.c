#include <stdlib.h>

#include"hashlib.h"
/*Храним

*/

int TABLE_SIZE = 50; // по умолчанию

int get_hash_BLOB(Data data/*, HT_ERR* err*/) {
    int hash = 0;
    size_t iterator = data.size/TABLE_SIZE+1;
    char* c_data = (char*)data.arr;

    for (int i = 0; i < data.size; i+=iterator) {
        hash = (hash+(i+3)*c_data[i])%TABLE_SIZE;
    }
    return hash;
}

// Копирует из ptr1 в ptr2 и выделяет память
void copy(void* ptr1, void** ptr2, size_t size){
    *ptr2 = malloc(size);
    char* c_ptr1 = (char*)ptr1;
    char* c_ptr2 = (char*)*ptr2;
    for(int i = 0; i < size; i++)
        c_ptr2[i] = c_ptr1[i]; 
}

void htable_insert(Data d) {
    int hash = get_hash_BLOB(d);
    printf("%i\n", hash);
    LList* list = TABLE[hash];
    LList* new = (LList*)malloc(sizeof(LList));

    copy(d.arr, &(new->data.arr), d.size);

    while(list != NULL && list->next != NULL)
        list = list->next;
    if(list != NULL) {
        list->next = new;
        list->next->prev = list;
        list = list->next;
        list->next = NULL;
    }
    else {
        TABLE[hash] = new;
        list = new;
        list->next = NULL;
        list->prev = NULL;
    }    
    list->data.size = d.size;


    printf("%i", (TABLE[1]->data.arr));
}



//выводит хеш таблицу
void htable_print() {
    LList* x;
    for(int i = 0; i < TABLE_SIZE; i++) {
        x = TABLE[i];
        printf("for hash %i:\n", i);
        while(x != NULL) {
            printf("%i\n", (TABLE[1]->data.arr));
            char* test_print = (char*)x->data.arr;
            for(int i = 0; i < x->data.size; i++) {
                printf("%i, ",((char *)x->data.arr)[i]);
            }
            x = x->next;
            //printf("\n");
        }
    }
}

//tested
void create_hash_table(size_t table_size) {
    TABLE_SIZE = table_size;
    TABLE = (LList**) malloc(table_size*sizeof(LList*));
    for(int i = 0; i < table_size; i++)
        TABLE[i] = NULL;

}


//not tested
void hash_table_remove() {
    LList* x;
    for(int i = 0; i < TABLE_SIZE; i++) {
        x = TABLE[i];
        while(x!= NULL) {
            free(x->data.arr);
            x = x->next;
        }
    }
}


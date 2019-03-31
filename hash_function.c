#include <stdint.h>
#include <stdio.h>

//rко-во коллизий
//get_size table
//создать табличку
//почистить табличку
//количество элементов c ключем
//поиск по ключю

//Возвращает hash принятого файла
int hash_function_iterator = 2; // образующий в мультипликативной группе

#define TABLE_SIZE 50// 


typedef struct data
{
    /* data */
    size_t elem_size;
    size_t size;
    void* data;
} Data;

int get_hash_BLOB(Data data/*, HT_ERR* err*/) {
    int hash = 0;
    size_t iterator = data.size/TABLE_SIZE+1;

    char* c_data = (char*)data.data;

    for (int i = 0; i < data.size; i+=iterator) {
        hash = (hash+(i+3)*c_data[i])%TABLE_SIZE;
    }
    return hash;
}


//возвращает дескриптор откопированного файла
int copy_data(Data data) {
        
}

int main() {
    char a[] = {2,5,4,2,5,4,4};
    Data test_data;
    test_data.size = 7;
    test_data.data = a;
    printf("%i", get_hash_BLOB(test_data));
}
#include"hashlib.h"
#include <stdlib.h>
#include <string.h>

void cover_test(TABLE* t) {
    HTERR err;
    Data d;
    // inv ptr
    htable_insert(NULL, d, &err);
    if(err != HTERR_INVPTR) {
        printf("cover_test_inv_ptr: test1 failed!");
        exit(1);
    }

    htable_print(NULL, &err);
    if(err != HTERR_INVPTR) {
        printf("cover_test_inv_ptr: test2 failed!");
        exit(1);
    }

    htable_search(NULL, d, &err);
    if(err != HTERR_INVPTR) {
        printf("cover_test_inv_ptr: test3 failed!");
        exit(1);
    }

    htable_remove_element(NULL, d, &err);
    if(err != HTERR_INVPTR) {
        printf("cover_test_inv_ptr: test4 failed!");
        exit(1);
    }

    htable_remove(NULL, &err);
    if(err != HTERR_INVPTR) {
        printf("cover_test_inv_ptr: test5 failed!");
        exit(1);
    }
    //

    int a3[] = {1,4,3,3,2,2,2,6,7,8,9,0};
    Data test_data3;
    test_data3.size = 12*4;
    test_data3.arr = a3;
    if(htable_remove_element(t, test_data3, &err) == 0 || err != HTERR_NO_SUCH_ELEM) {
        printf("cover_test_ no_such_elem: test6 failed!");
        exit(1);
    }

    //
    char a5[] = {1,4,3,3,2,2,4,4,4,4,44,4,5,6,7,2,5,17,70,10,1,1,1,1,1,1,1,1,1};
    Data test_data5;
    test_data5.size = 29;
    test_data5.arr = a5;


    if(htable_search(t, test_data5, &err) != NULL)
       printf("cover_test_ no_such_elem: test7 failed!");
}

void full_table_trash(TABLE* t) {
    for(int i = 0; i < 10; i++) {
        
        size_t size = 15;
        Data* d = (Data*)malloc(sizeof(Data));
        
        d->size = 12;
        
        d->arr = malloc(size*sizeof(char));
        char* temp = (char*)d->arr;
        for(int j = 0; j < size; j++) {
            temp[j] = i*j+i;
        }
        htable_insert(t, *d, NULL);
        free(temp);
        free(d);
    }
}


int main() {
    HTERR err = HTERR_SUCCESS;
    TABLE* t = create_hash_table(4, &err);

    //generate data
    char a1[] = {2,5,4,2,5,4,4};
    Data test_data1;
    test_data1.size = 7;
    test_data1.arr = a1;


    char a2[] = {1,1,1,1,1,2,2};
    Data test_data2;
    test_data2.size = 7;
    test_data2.arr = a2;


    int a3[] = {1,4,3,3,2,2,2};
    Data test_data3;
    test_data3.size = 7*4;
    test_data3.arr = a3;

    char a4[] = {1,4,3,3,2,2,2,5,6,7,8,9,10,20,10};
    Data test_data4;
    test_data4.size = 15;
    test_data4.arr = a4;

    char a5[] = {1,4,3,3,2,2,4,4,4,4,44,4,5,6,7,2,5,10,20,10};
    Data test_data5;
    test_data5.size = 20;
    test_data5.arr = a5;


    Data *data_massive = (Data*)malloc(3*sizeof(Data));
    data_massive[0] = test_data1;
    data_massive[1] = test_data2;
    data_massive[2] = test_data3;

    htable_insert(t, test_data1, &err);
    htable_insert(t, test_data2, &err);
    htable_insert(t, test_data3, &err);
    htable_insert(t, test_data4, &err);
    htable_insert(t, test_data5, &err);
    htable_insert(t, test_data5, &err);
    //full_table_trash(t);
    //
    //Data *data_massive = generate_data(t);
    
    //cover errors
    cover_test(t);
    //
    htable_print(t, &err);
    printf("\n\n ---some print----\n%i\n", ((char*)(htable_search(t,test_data5, &err)->arr))[0]);
    printf("\n number collisions: %i\n", t->number_collisions);
    printf("%i\n ----some print----\n\n", ((char*)(htable_search(t,test_data3, &err)->arr))[0]);
    htable_remove_element(t, test_data3, &err);
    //htable_insert(t, test_data3, &err);
    //printf("kok %i", ((char*)(htable_search(t,test_data3, &err)->arr))[0]);
    htable_remove_element(t, test_data3, &err);

    htable_insert(t, test_data3, &err);


    htable_remove_element(t, test_data3, &err);
    htable_print(t, &err);
    printf("\n number collisions: %i", t->number_collisions);
    htable_remove_element(t, test_data2, &err);
    
    htable_print(t, &err);

    htable_remove(t, &err);
    free(data_massive);
    return 0;
}
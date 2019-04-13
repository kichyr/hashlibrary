#include"hashlib.h"
#include <stdlib.h>

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

}

Data* generate_data(TABLE* t) {
    HTERR err;
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

    Data *data_massive = (Data*)malloc(3*sizeof(Data));
    data_massive[0] = test_data1;
    data_massive[1] = test_data2;
    data_massive[2] = test_data3;

    htable_insert(t, test_data1, &err);
    htable_insert(t, test_data2, &err);
    htable_insert(t, test_data3, &err);
    return data_massive;
}

int main() {
    TABLE* t = create_hash_table(4);

    HTERR err;
    Data *data_massive = generate_data(t);
    
    htable_print(t, &err);

    printf("kok %i", ((char*)(htable_search(t,test_data2, &err)->arr))[0]);
    htable_remove_element(t, data_massive[2], &err);
    htable_insert(t, data_massive[2], &err);

    htable_print(t, &err);

    htable_remove(t, &err);
    free(data_massive);
    return 0;
}
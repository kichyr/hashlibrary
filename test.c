#include"hashlib.h"



int main() {
    char a1[] = {2,5,4,2,5,4,4};
    Data test_data1;
    test_data1.size = 7;
    test_data1.arr = a1;


    char a2[] = {1,1,1,1,1,2,2};
    Data test_data2;
    test_data2.size = 7;
    test_data2.arr = a2;


    char a3[] = {1,1,1,1,1,2,2};
    Data test_data3;
    test_data3.size = 7;
    test_data3.arr = a3;

    create_hash_table(4);

    htable_insert(test_data1);

    htable_print();

    

    return 0;
}
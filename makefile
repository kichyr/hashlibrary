all: utest

utest: hashlib.o test.o
	gcc hashlib.o test.o -o utest
hashlib.o: hashlib.c
	gcc -c hashlib.c -o hashlib.o
test.o:
	gcc -c test.c -o test.o
clean:
	rm -rf *.o utest *.gcno *.gcda *.gcov
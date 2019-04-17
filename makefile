all: utest
CFLAGS=-Wall -g -fprofile-arcs -ftest-coverage
LDFLAGS="-lgcov"
utest: hashlib.o test.o
	gcc hashlib.o test.o -o utest ${CFLAGS}
hashlib.o: hashlib.c
	gcc -c hashlib.c -o hashlib.o ${CFLAGS}
test.o:
	gcc -c test.c -o test.o ${CFLAGS}
	gcc -c test.c -o test.o ${CFLAGS}
clean:
	rm -rf *.o utest *.gcno *.gcda *.gcov
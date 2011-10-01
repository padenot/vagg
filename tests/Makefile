CFLAGS=-Wall -Wextra -g
FLAGS=${CFLAGS} -DVAGG_DEBUG -DVAGG_COUNT_ALLOC -DVAGG_PRINT_ALLOC -DVAGG_TEST

all:
	gcc -I ../ vagg_tests.c ../vagg.c ${CFLAGS} -o vagg_notest
	gcc -I ../ vagg_tests.c ../vagg.c ${FLAGS} -o vagg_test

clean:
	rm -f vagg_notest
	rm -f vagg_test

check: all
	./vagg_notest
	./vagg_test

CFLAGS=-Wall -Wextra -g -fPIC
FLAGS=${CFLAGS} -DVAGG_DEBUG -DVAGG_COUNT_ALLOC -DVAGG_PRINT_ALLOC -DVAGG_TEST

all: static dynamic
	ln -sf libvagg.so.1.0 libvagg.so
	ln -sf libvagg.so.1.0 libvagg.so.1

build:
	gcc -c vagg.c ${FLAGS} -o vagg.o

static: build
	ar -cvq libvagg.a vagg.o

dynamic: build
	gcc -shared -Wl,-soname,libvagg.so.1 ${FLAGS} vagg.o -o libvagg.so.1.0

clean:
	rm -f vagg.o
	rm -f libvagg.so
	rm -f libvagg.a
	make -C tests clean

check:
	make -C tests

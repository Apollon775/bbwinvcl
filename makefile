CC=gcc
CFLAGS=
CLIBS=
TARGET=release/bbwinvcl
INCLUDE=include/

.PHONY=all bbwinvcl clean

cl.o: include/cl.o
	${CC} -c include/cl.c -o cl.o

bbwinvcl: src/client.c cl.o
	${CC} -I${INCLUDE} -g src/client.c cl.o -o ${TARGET}

clean: 
	rm *.o

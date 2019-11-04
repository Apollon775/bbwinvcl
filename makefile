CC=gcc
CFLAGS=
CLIBS=
TARGET=release/bbwinvcl
INCLUDE=include/

.PHONY=all bbwinvcl clean

object: include/cl.o
	${CC} -c include/cl.c include/ifdata.c 

bbwinvcl: src/client.c object
	${CC} -I${INCLUDE} -g src/client.c  cl.o ifdata.o -o ${TARGET}

clean: bbwinvcl
	rm *.o

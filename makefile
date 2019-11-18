CC=g++
SOURCE=include/cl.cpp include/ifdata.cpp include/MainFrame.cpp
OBJECT= *.o
TARGET=release/bbwinvcl
INCLUDE=-Iinclude/ `wx-config --cxxflags`
LIBS=`wx-config --libs`


.PHONY=all bbwinvcl clean

object: include/cl.o
	${CC} -c ${SOURCE} ${INCLUDE}

bbwinvcl: src/client.c object
	${CC} ${INCLUDE} ${LIBS} -g src/client.c  ${OBJECT} -o ${TARGET}

clean: bbwinvcl
	rm *.o

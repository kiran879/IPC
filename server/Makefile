#!/bin/bash
CC=gcc
CF=-c -Wall
DF=-DDEBUG
output: server.o init.o createInfra.o createPipe.o createFifo.o
	${CC} -o output server.o init.o createInfra.o createPipe.o createFifo.o

server.o: server.c ../header.h declaration.h dataStructures.h
	${CC} ${CF} ${DF} server.c
init.o: init.c ../header.h declaration.h dataStructures.h
	${CC} ${CF} ${DF} init.c
createInfra.o: createInfra.c ../header.h declaration.h dataStructures.h
	${CC} ${CF} ${DF} createInfra.c
createPipe.o: createPipe.c ../header.h declaration.h dataStructures.h
	${CC} ${CF} ${DF} createPipe.c
createFifo.o: createFifo.c ../header.h declaration.h dataStructures.h
	${CC} ${CF} ${DF} createFifo.c

clean:
	-rm *.o
	-rm -f output

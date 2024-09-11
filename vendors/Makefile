#!/bin/bash
CC=gcc
CF=-c -Wall
DF=-DDEBUG
vendorOperations: vendorMain.o init.o vendorsHandler.o vendor1.o vendor2.o vendor3.o vendor4.o
	${CC} -o vendorOperations vendorMain.o init.o vendorsHandler.o vendor1.o vendor2.o vendor3.o vendor4.o

vendorMain.o: vendorMain.c ../header.h declaration.h
	${CC} ${CF} ${DF} vendorMain.c
init.o: init.c ../header.h declaration.h ../client/dataStructures.h
	${CC} ${CF} ${DF} init.c
vendorsHandler.o: vendorsHandler.c ../header.h declaration.h ../client/dataStructures.h
	${CC} ${CF} ${DF} vendorsHandler.c
vendor1.o: vendor1.c ../header.h declaration.h
	${CC} ${CF} ${DF} vendor1.c
vendor2.o: vendor2.c ../header.h declaration.h 
	${CC} ${CF} ${DF} vendor2.c
vendor3.o: vendor3.c ../header.h declaration.h 
	${CC} ${CF} ${DF} vendor3.c
vendor4.o: vendor4.c ../header.h declaration.h 
	${CC} ${CF} ${DF} vendor4.c

clean:
	-rm *.o
	-rm -f vendorOperations

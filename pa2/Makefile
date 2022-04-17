#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

SELENE   = Graph.c List.c
HELIOS   = Graph.o List.o
ADONIS   = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

GraphClient : GraphClient.o $(HELIOS)
	$(LINK) GraphClient GraphClient.o $(HELIOS)

GraphClient.o : GraphClient.c $(ADONIS)
	$(COMPILE) GraphClient.c

$(HELIOS) : $(SELENE) $(ADONIS)
	$(COMPILE) $(SELENE)

clean :
	$(REMOVE) FindPath GraphClient FindPath.o GraphClient.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in7 junk7

checkClient : GraphClient
	$(MEMCHECK) GraphClient

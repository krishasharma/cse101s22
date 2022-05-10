#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 5
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17 -Wall
REMOVE = rm -f

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXECS = ListClient

.PHONY: all clean debug GDB

all: $(EXECS)

clean:
	$(REMOVE) $(OBJ) $(EXECS)

GDB: CFLAGS += -g
GDB: clean all
	gdb --args ./$(EXECS)


$(EXECS): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

cleanScript:
	$(REMOVE) *.txt

CC = g++
CFLAGS = -std=c++17 -Wall
REMOVE = rm -f

ALL_SOURCE = $(wildcard *.cpp)
COMMON_SOURCE = ${shell grep -L "int main(" ${ALL_SOURCE}}
COMMON_OBJECT = $(COMMON_SOURCE:%.cpp=%.o)
EXECS = DictionaryClient

.PHONY: all clean debug GDB

all: $(EXECS)

clean:
	$(REMOVE) $(EXECS) *.o

GDB: CFLAGS += -g
GDB: clean all

$(EXECS): %: %.o $(COMMON_OBJECT)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

cleanScript:
	$(REMOVE) *.txt·

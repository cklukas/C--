CC=g++
CFLAGS=-c -Wall -std=c++17 
LDFLAGS=-lncurses
SOURCES=searchui.cpp ui.cpp ui.hpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=searchui

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) 
	mv a.out $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) $< 

install:
	cp $(EXECUTABLE) /usr/local/bin

clean:
	rm -f *.o ${EXECUTABLE}

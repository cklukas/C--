CC=g++
CFLAGS=-c -Wall -std=c++17
LDFLAGS=
SOURCES=search.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=search

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

install:
	cp $(EXECUTABLE) /usr/local/bin

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
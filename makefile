CC=g++
CFLAGS=-c -Wall
#CFLAGS=-o
LDFLAGS=
SOURCES=main.cpp num.cpp im.cpp jm.cpp EasyBMP.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=SOR3

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@




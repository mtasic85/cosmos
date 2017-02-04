CC=gcc
CFLAGS=-c -Wall -O0 -g
LDFLAGS=-lpthread
SOURCES=cosmos.c ctx.c value.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=cosmos

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE)

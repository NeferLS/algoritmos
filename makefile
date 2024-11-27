EXECUTABLE = heap

SOURCES = p4.c aux.c

HEADERS = p4.h

CC = gcc
CFLAGS = -Wall -Wextra -lm

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

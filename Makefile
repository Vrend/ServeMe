TARGET = server

CC = gcc

CFLAGS = -g -Wall -pthread

OBJ = server.o requests.o utility.o response.o headers.o

DEPS = dependencies.h server.h requests.h utility.h response.h headers.h

all: $(TARGET)

%o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(TARGET) *.o

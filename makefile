OBJECTS= main.o draw.o display.o matrix.o parser.o
HEADERS= ml6.h display.h draw.h matrix.h parser.h
CFLAGS= -Wall
LDFLAGS= -lm
CC= gcc

all: $(OBJECTS)
	$(CC) -o main $(OBJECTS) $(LDFLAGS)
	./main

main.o: main.c $(HEADERS)
	$(CC) -c main.c

draw.o: draw.c $(HEADERS)
	$(CC) $(CFLAGS) -c draw.c

dsiplay.o: display.c $(HEADERS)
	$(CC) $(CFLAGS) -c display.c

matrix.o: matrix.c $(HEADERS)
	$(CC) $(CFLAGS) -c matrix.c

parser.o: parser.c $(HEADERS)
	$(CC) $(CFLAGS) -c parser.c

run: main
	./main
clean:
	rm *.o *~

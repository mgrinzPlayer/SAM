CC = gcc

OBJ = main.o reciter.o sam.o render.o

CFLAGS = -Wall -O2
LFLAGS =

sam32: $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -shared -o sam-i686.dll

sam64: $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -shared -o sam-x86_64.dll

%.o: src/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	del *.o

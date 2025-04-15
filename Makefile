CC=gcc
CFLAGS=-I.
DEPS = tp.h bruteforce.h
OBJ = main.o bruteforce.o
EXEC = tp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(EXEC) *.o *~ core
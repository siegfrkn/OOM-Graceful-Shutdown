CC := gcc

SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))

all: $(OBJ_FILES)

%.o: %.c
	$(CC) -o $@ $<

clean:
	rm -f *.o

CC := gcc

SRC_FILES := $(wildcard *.c)
PROGS := $(patsubst %.c,%,$(SRC_FILES))

all: $(PROGS)

%.o: %.c
	$(CC) -o $@ $<

clean:
	rm -f $(PROGS)
	sudo rm -f write_to_test.txt
	sudo rm -f graceful_shutdown_output.txt
	sudo rm -f ping_output_gs.txt

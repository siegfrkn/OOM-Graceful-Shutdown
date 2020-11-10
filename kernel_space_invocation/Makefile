obj-m := lkm.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o read_from_lkm.o read_from_lkm.c
	gcc -o example_program.o example_program.c


clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo insmod lkm.ko
remove:
	sudo rmmod lkm.ko
	make clean

CONFIG_MODULE_SIG=n
CONFIG_MODULE_SIG_ALL=n

KBUILD_EXTRA_SYMBOLS := Module.symvers
EXTRA_CFLAGS += $(CFLAGS_EXTRA) -fno-pie

obj-m += proc_create_module.o

all:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	sudo insmod proc_create_module.ko
remove:
	sudo rmmod proc_create_module

clean:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

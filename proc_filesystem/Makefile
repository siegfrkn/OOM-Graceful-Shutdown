CONFIG_MODULE_SIG=n
CONFIG_MODULE_SIG_ALL=n

KBUILD_EXTRA_SYMBOLS := Module.symvers
EXTRA_CFLAGS += $(CFLAGS_EXTRA) -fno-pie

obj-m += proc_create_module.o

all:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install: remove
	sudo insmod proc_create_module.ko

# && true supresses errors from the remove rule. Useful in top level
# make file so that we can always try to remove the module before loading it.
remove:
	sudo rmmod proc_create_module && true

clean:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

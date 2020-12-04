LINUX_SOURCE_DIR:=/usr/src/linux-5.4.1/

.PHONY: all proc tests

all: proc tests linux_built.txt

linux_built.txt: oom_kill.c
	/bin/bash -c "sudo ./copy_oom_kill_file_and_build.sh $(LINUX_SOURCE_DIR)"
	rm -f "linux_built.txt"
	touch "linux_built.txt"

tests:
	$(MAKE) -C test_programs

proc:
	$(MAKE) -C proc_filesystem
	$(MAKE) install -C proc_filesystem

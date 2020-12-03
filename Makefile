LINUX_SOURCE_DIR:=/usr/src/linux-5.4.1/

.PHONY: all proc tests

all: proc tests
	/bin/bash -c "sudo ./copy_oom_kill_file_and_build.sh $(LINUX_SOURCE_DIR)"

tests:
	$(MAKE) -C test_programs

proc:
	$(MAKE) -C proc_filesystem
	$(MAKE) install -C proc_filesystem

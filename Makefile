LINUX_SOURCE_DIR:=/usr/src/linux-5.4.1/

.PHONY: all proc tests

all: proc tests linux_built.txt

setup_new_vm:
	/bin/bash -c "sudo ./setup_new_vm.sh"


linux_built.txt:  setup_new_vm oom_kill.c
	/bin/bash -c "sudo ./copy_oom_kill_file_and_build.sh $(LINUX_SOURCE_DIR)"
	rm -f "linux_built.txt"
	touch "linux_built.txt"

tests:
	$(MAKE) -C test_programs

proc: linux_built.txt
	$(MAKE) -C proc_filesystem
	$(MAKE) install -C proc_filesystem

clean:
	rm -r linux-5.4.1*
	sudo rm -r $(LINUX_SOURCE_DIR)
	$(MAKE) -C proc_filesystem
	$(MAKE) clean -C test_programs
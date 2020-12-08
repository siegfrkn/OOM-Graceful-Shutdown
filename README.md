# Graceful Shutdown from OOM Conditions
This repo allows you to run a user space shutdown procedure before a process is killed by the OOM killer. This could be useful to save data to disk before shutdown, send a message out over the internet, or perform some other operation before a process is killed. Effectively any user space process could be run as a graceful shutdown process. The shutdown procedures are specified at a per process level, so all processes need not have the same graceful shutdown procedure, nor any graceful shutdown process at all.

## Graceful Shutdown Process Requirements 
The memory footprint cannot be large and care should be taken to avoid long running processes. The OOM killer cannot reap any processes until the graceful shutdown process completes, so infinite loops or long running graceful shutdown processes will result in your system remaining in an OOM state.


## System Requirements
This has only been tested on ubuntu 20.04 using kernel version 5.4.x. Kernel versions of 4.x will not work as large portions of the OOM killer changed between the two versions. Versions 6.x haven't been tested. Additionally you must have sudoer capabilities.

## Installation
If you are installing this on a fresh VM, run ```make all```. If your kernel will be located at a different location than ```/usr/src/```, change the file path in the first line of the top level makefile.

The ```make all``` command will use the shell script ```setup_new_vm.sh``` to download the kernel source and install necessary packages and create a directory at ```/usr/src/linux-5.4.1/``` with the source code of the kernel in it. This makefile then patches the oom_kill.c source code into the kernel and the re-compiles the kernel. It auto-detects how many cores you have on your machine and uses all of them for the compilation of the kernel. Since this is recompiling the entire linux kernel, it may take a while. On a 6 core VM with 12 gbs of RAM and an SSD, it takes a minute or two, but on a single core machine with small amounts of ram it may take an hour or more.

After the kernel recompiles, restart you machine and select the new kernel from the GRUB menu while you are restarting. Assuming 5.4.1 is newer than your current kernel, it will become the new default kernel on reboot.

Once the kernel has been launched, the following script will need to be executed only once to set the cgroups and the proc file system to run at boot.

```./setup_initial_running_env.sh```

Additional information about verifying /proc file system setup and cgroup setup can be found in the "proc_filesystem" and "cgroup" subdirectories respectively.

## Usage
To use the graceful shutdown, you must have already completed the setup steps above. To use the system, simply add the pid of a process and the path to a graceful shutdown executable to /proc/graceful_shutdown. The simplest way to do this is with the echo command (that's a space seperating the two):

```echo "<pid> <full_path_to_graceful_shutdown_executable>" >> /proc/graceful_shutdown```

If a process with the pid specified is killed by the OOM killer, the executable specified in the path you provided will be run *before* that process is killed. The path for the graceful shutdown executable must be a full unqualified path. There is currently no support for passing arguments to the graceful shutdown executables

There is a shell script located in the ```test_programs``` that can help you add the pid and graceful shutdown path of a specific process to the proc file. It's usage is: ```./run_program_with_gs.sh <path_to_program_to_execute> <path_to_graceful_shutdown_executable>```.

## Testing
Run the ```run_program_with_gs``` shell script to run an executable with a graceful shutdown procedure. There is an executable that causes an OOM condition intentionally named ```oom_condition_creator.c``` that can be run with a graceful shutdown procedure to test. See the "test_programs" subdirectory README for more information.

# Graceful Shutdown from OOM Conditions
This repo allows you to run a user space shutdown procedure before a process is killed by the OOM killer. This could be useful to save data to disk before shutdown, send a message out over the internet, or perform some other operation before a process is killed. Effectively any user space process could be run as a graceful shutdown process. The shutdown procedures are specified at a per process level, so all processes need not have the same graceful shutdown procedure.

## Graceful Shutdown Process Requirements 
The memory footprint cannot be large and care should be taken to avoid long running processes. The OOM killer cannot reap any processes until the graceful shutdown process completes, so infinite loops or long running graceful shutdown processes will result in your system remaining in an OOM state.

## Usage
To use the graceful shutdown, you must have the update OOM killer compiled into your kernel, and an lkm that creates a proc file system entry installed. See instalation below. To use the system, simply add the pid of a process and the path to a graceful shutdown executable to /proc/graceful_shutdown. If a process with the pid specified is killed by the OOM killer, the executable specified in the path you provided will be run before that process is killed. The proc/graceful_shutdown file has a format of ```<pid> <full_path_to_graceful_shutdown_executable>```. That's a space seperating the two. The path for the graceful shutdown executable must be a full unqualified path. There is currently no support for passing arguments to the graceful shutdown executables. There is a shell script located in the ```test_examples``` that can help you add the pid and graceful shutdown path of a specific process to the proc file. It's usage is: ```./run_program_with_gs.sh <path_to_program_to_execute> <path_to_graceful_shutdown_executable>```.

## System Requirements
This has only been tested on ubuntu 20.04 using kernel version 5.4.x. Kernel versions of 4.x will not work as large portions of the OOM killer changed between the two versions. Versions 6.x haven't been tested.

## Installation
If you are installing this on a fresh VM, use the shell script ```setup_new_vm.sh``` to download the kernel source and install necessary packages. After runningthis script, you should have a directory at ```/usr/src/linux-5.4.1/``` with the source code of the kernel in it. Then run the make file in the top level directory. If your kernel is located at a different location than ```/usr/src/linux-5.4.1/```, change the file path in the first line of the top level makefile. This makefile patches the oom_kill.c source code into the kernel and the re-compiles the kernel. It auto-detects how many cores you have on your machine and uses all of them for the compilation of the kernel. Since this is recompiling the entire linux kernel, it may take a while. On a 6 core VM with 12 gbs of RAM and an SSD, it takes a minute or two, but on a single core machine with small amounts of ram it may take an hour or more. After the kernel recompiles, restart you machine and select the new kernel from the GRUB menu while you are restarting.

Once the kernel has been launched, the following script will need to be executed only once to set the cgroups and the proc file system to run at boot.
```./setup_initial_running_env.sh```
We will need to decide where this gets copied over and then run.

## Testing
Run the ```run_program_with_gs``` shell script to run an executable with a graceful shutdown procedure. There is an executable that causes an OOM condition intentionally named ```oom_condition_creator.c``` that can be run with a graceful shutdown procedure to test.

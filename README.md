# Graceful Shutdown from OOM Conditions
This repo allows you to run a user space shutdown procedure before a process is killed by the OOM killer. This could be useful to save data to disk before shutdown, send a message out over the internet, or perform some other operation before a process is killed. Effectively any user space process could be run as a graceful shutdown process. The shutdown procedures are specified at a per process level, so all processes need not have the same graceful shutdown procedure.

## Graceful Shutdown Process Requirements 
The memory footprint cannot be large and care should be taken to avoid long running processes. The OOM killer cannot reap any processes until the graceful shutdown process completes, so infinite loops or long running graceful shutdown processes will result in your system remaining in an OOM state.

## Usage
To use the graceful shutdown, you must have the update OOM killer compiled into your kernel, and an lkm that creates a proc file system entry installed. See instalation below. To use the system, simply add the pid of a process and the path to a graceful shutdown executable to /proc/graceful_shutdown. If a process with the pid specified is killed by the OOM killer, the executable specified in the path you provided will be run before that process is killed.




kernel 5.4.0-48-generic Ubuntu 18.04 LTS

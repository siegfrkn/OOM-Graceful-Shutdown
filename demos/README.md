# Explanation of Demo Files
The demo videos are screen recordings which do not have accompanying audio. To enhance understanding of what is being performed in the demo, detailed descriptions have been added here. There are known issues attempting to play the demo videos directly on github. Please download the project repo, extract, and play the video from there. If there are issues viewing the demo recordings, please contact the authors for a copy.

### Simple Graceful Shutdown Demo
The simple graceful shutdown video demonstrates the basic functionality of the graceful shutdown implementation.

The demo begins in the main project directory ```../csci5573-project``` (0:00). The contents of the directory are listed (0:05), and then enters the ```test_programs``` subdirectory where the demo will be carried out (0:08).

The contents of the ```test_programs``` subdirectory is listed to show the initial file contents (0:10), as an additional file will be created in this directory as an output of the graceful shutdown. The current contents are:
- Makefile - used to create the test programs
- oom_condition_creator - executable to create oom condition
- oom_condition_creator.c - source file for creating oom condition
- run_program_with_gs.sh - script to carry out testing and demonstrations
- write_to_file_gs_test - example graceful shutdown executable, creates new file
- write_to_file_gs_test - source file for example graceful shutdown

The script ```run_program_with_gs.sh``` script is then run. The script takes arguments in the following format (0:20):

```./run_program_with_gs <file to cause oom> <graceful shutdown file>```

where the file that causes the oom in the demonstration is a file which just infinitely allocates very large chunks of memory, and the graceful shutdown file for this demonstration is a simple C program which creates a file, graceful_shutdown_output.txt in the same directory upon the killing of the oom condition causing program. The ```run_program_with_gs.sh``` script will initiate the oom causing program, and echo the PID of that process and the path of the graceful shutdown process into the /proc/graceful_shutdown directory, which will be used by the kernel to invoke that process upon killing the oom causing process with that PID.

The ```oom_condition_creator``` will pause and wait for user input so that the PID of the process can be compared by the user to the /proc/graceful_shutdown file, as shown in the demo (0:32).

```sudo cat /proc/graceful_shutdown```

The demo then waits while the memory is over-allocated and the OOM killer is eventuall invoked (2:03).

Switching tabs, dmesg is called to show all kernel commands (2:13). The actual top of the dmesg output is found (2:32) which shows the reading of the PID of the process and the graceful shutdown process called, ```write_to_file_gs_test```, a timer is started when the OOM PID matching the oom condition causing program is chosen for kill. Additional kernel output highlighted in red is from the customized OOM killer where the graceful shutdown process is noted and then called by the kernel as a user space process. In this case, as mentioned above, the ```write_to_file_gs_test``` creates a file with some text in the test_programs directory. When this process is finished, a timer notes the elapsed time from when the graceful shutdown was called to when it was completed - 2265528 ns or 0.002265528 seconds. At the bottom of the dmesg output the cgroup oom killer output is given, as the oom condition creating process was running inside of a memory limited cgroup, which allows memory to be reserved to the graceful shutdown process.

Switching tabs again, the contents of the ```test_programs``` directory is shown again. This time there is an additional file, ```graceful_shutdown_output.txt``` which was created by the graceful shutdown process when the oom killer was called on the oom condition creating program. The file contents are cat'ed out and read:

"The oom killer was invoked, and this is a file generated as a result of the graceful shutdown."

### Connecting to Server Demo

### Read and Write to File Demo

### Accessing Shared Memory Demo

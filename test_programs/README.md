# Test Programs for Graceful Shutdown
The files in this directory are used to exercise and demonstrate the capabilities of the Graceful Shutdown implementation. These files will be built into executables by the initial ```make all``` command, and executed by running the ```run_program_with_gs.sh``` script.

If any files need to be edited and rebuilt, the commands

```make clean```

will clean all generated files (executables and text files ouput from running tests) in the ```test_programs``` directory. To rebuild the files in the directory, run

```make all```

## Using the script to execute test programs
The script ```run_program_with_gs.sh``` is used to execute each of the test programs. This script automates all of the steps a user would need to take to assign a graceful shutdown process to a running process.

Usage of the script is as follows:

```./run_program_with_gs.sh <oom watch file> <graceful shutdown file>```

where both the ```<oom watch file>``` and the ```<graceful shutdown file``` are full file paths. The script will then start the file which will be tagged as the process to watch for the oom condition, grab it's PID, and echo the PID and the path of the graceful shutdown program into the /proc/graceful_shutdown file, just as a user would need to do in actual use.

```<PID> <graceful shutdown file>```

Finally, the script will execute the ```<oom watch file>``` in the limited memory cgroup, which contains large memory leaks so that there is still memory for the graceful shutdown file to run in.

## OOM Condition Creator Program
This is the file that is used for the test programs to create out of memory conditions. This file begins and then waits for the user to press the ```Enter``` key so that during testing there is enough time for the user to inspect the PID of the created process. Once the user presses the ```Enter``` key, the file will allocate very large blocks of memory infinitely. This will eventually cause the OOM condition to occur.

## Testing File Create/Write
This test uses the program ```write_to_file_gs``` as the graceful shutdown program. When called, it creates a file named "graceful_shutdown_output.txt" in the ```test_programs``` directory with a simple sentence within. The path and name of the file are hardcoded inside of the test file, so in order to change this path to match your own user directory you must open the source file, edit, close, and re-make before executing. The command to execute this file will need to look something like the following:

```./run_program_with_gs.sh /<full>/<file>/<path>/Project/csci5573-project/test_programs/oom_condition_creator /<full>/<file>/<path>/Project/csci5573-project/test_programs/write_to_file_gs_test```

The program will start the ```oom_condition_creator``` program and pause and wait for the user to press ```Enter```. After that, the program will start allocating large blocks of memory until an OOM condition is created and the program is marked for shutdown. It will then call and execute the ```write_to_file_gs``` program which will create a file, "graceful_shutdown_output.txt" in the ```test_programs``` directory, which contains the following text:

"The oom killer was invoked, and this is a file generated as a result of the graceful shutdown"


## Testing File Read and Write

## Testing Server Connectivity

## Testing Access to Shared Data

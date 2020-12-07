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

## Testing File Create/Write

## Testing File Read and Write

## Testing Server Connectivity

## Testing Access to Shared Data

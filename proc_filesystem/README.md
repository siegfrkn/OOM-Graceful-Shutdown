# Creating the Directory /proc/graceful_shutdown
This project builds a lkm named "proc_create_module" which creates a new proc filesystem entry /proc/graceful_shutdown. This new directory is used by the modified oom killer to map a process marked for killing to its graceful shutdown process if it exists. This Makefile is called by the main setup scripts.

## Usage
To insert make the module and assocaited files:
       ```make all```
       
To clean the directory:
       ```make clean```

To insert the module:
        ```sudo insmod proc_create_module.ko```

To remove the module:
        ```sudo rmmod proc_create_module```

To view the new file system:
        ```sudo ls /proc```

To write to the file system (demo functionality at the moment not working):
        ```sudo echo "message" > /proc/graceful_shutdown```

To read the file system:
        ```sudo cat /proc/graceful_shutdown```

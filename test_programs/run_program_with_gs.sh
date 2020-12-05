#set -x
CGROUP_NAME="memlimit"

if [ "$#" -ne 2 ]
  then
    echo "Usage ./run_program_with_gs.sh <program_path> <gs_executable_path>"
    echo "Ex. ./run_program_with_gs.sh ./test.o /home/user/Desktop/graceful_shutdown.o"
    echo "ERROR: More or less than two parameters supplied."
    exit 1
  fi
if [ "${2:0:1}" != "/" ]
  then
    echo "${2:0:1}"
    echo "Warning! Graceful Shutdown paths must be absolute!"
    echo "The first character of your input isn't a \"/\", so it probably isn't an absolute path."
    echo "Continuing, but if the gs path isn't absolute it won't work."
  fi

echo "Starting process ${1} with oom graceful shutdown procedure of: ${2}"
sudo /bin/bash -c 'echo "$(echo $$) ${0}"  >> /proc/graceful_shutdown && cgexec -g memory:${1} ${2}' $2 $CGROUP_NAME $1

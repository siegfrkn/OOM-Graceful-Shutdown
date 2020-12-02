if [ "$#" -ne 2 ]
  then
    echo "Usage ./copy_oom_kill_file_and_build.sh <linux_source_path> <number_of_processes_to_build_with>"
    echo "Ex. ./copy_oom_kill_file_and_build.sh usr/src/linux-5.4/ 9"
    echo "ERROR: More or less than two parameters supplied."
  fi

mkdir -p old_oom_kill/
sudo mv "${1}/mm/oom_kill.c" ./old_oom_kill/ &>/dev/null
sudo cp oom_kill.c "${1}/mm/"

cd "${1}/" && sudo make "-j${2}" && sudo make modules_install install

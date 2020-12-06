set -x
if [ "$#" -ne 1 ]
  then
    echo "Usage ./copy_oom_kill_file_and_build.sh <linux_source_path>"
    echo "Ex. ./copy_oom_kill_file_and_build.sh usr/src/linux-5.4/"
    echo "ERROR: More or less than one parameters supplied."
    exit 1
  fi

mkdir -p old_oom_kill/

num_old_files=$(ls -1 old_oom_kill/ | wc -l)
sudo mv "${1}/mm/oom_kill.c" "./old_oom_kill/oom_kill.c-${num_old_files}" || true

sudo cp oom_kill.c "${1}/mm/"

num_processors=$(grep -c ^processor /proc/cpuinfo)
cd "${1}/" && sudo make "-j${num_processors}" && sudo make modules_install install

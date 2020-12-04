#!/bin/bash

LINUX_SRC_DIR='/usr/src/linux-5.4.1'

# remove old log files
rm -f sys_install.log install.log

# get kernel source in background while installing stuff.
(wget https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.4.1.tar.gz \
&& sudo tar -xvf linux-5.4.1.tar.gz -C/usr/src) > install.log 2>&1 &

#packages for kernel compilation and sshing into vm.
(sudo apt-get install gcc make libncurses5-dev bison flex libssl-dev libelf-dev openssh-server cgroup-tools -y &&
sudo apt-get update -y &&
sudo apt-get upgrade -y &&
sudo systemctl enable ssh) > sys_install.log 2>&1 &

# wait for both to finish, then setup config.
echo "Waiting for both jobs to finish!"
wait $(jobs -p)
cd "$LINUX_SRC_DIR" && sudo make defconfig
cd - && sudo cp kernel.config $LINUX_SRC_DIR/.config

#!/bin/bash

LINUX_SRC_DIR='/usr/src/linux-5.4.1'

# get kernel source in background while installing stuff.
(wget https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.4.1.tar.gz \
&& sudo tar -xvf linux-5.4.1.tar.gz -C/usr/src) > install.log 2>&1 &

#packages for kernel compilation and sshing into vm.
sudo apt-get install gcc make libncurses5-dev bison flex libssl-dev libelf-dev openssh-server cgroup-tools &&
sudo apt-get update &&
sudo apt-get upgrade &&
sudo systemctl enable ssh

sudo cp kernel.config $LINUX_SRC_DIR/.config &&
cd "$LINUX_SRC_DIR" &&
sudo make defconfig

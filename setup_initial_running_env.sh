#!/bin/bash

# this script must be run as root
if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "ERROR: Script must be run as root user, sudo is not sufficient"
    exit
fi

# empty the files so we aren't appending infinitely
echo "Clearing out systemd files....."
echo "" > /etc/systemd/system/cgconfigparser.service
echo "" > /etc/systemd/system/cgrulesengd.service

# insert the proc module
echo "Create the /proc/graceful_shutdown dir....." &&
cd proc_filesystem &&
make all &&
make install &&
cd - &&

# add the lkm for the proc directory to run at boot every time
echo "Setting /proc/graceful_shutdown to initialize on every boot....." &&
echo 'proc_create_module ' >> /etc/modules-load.d/modules.conf &&

# enable the memory management if not already enabled
echo "Setting up graceful_shutdown cgroups....." &&
echo '# Uncomment to enable memory management' >> /etc/default/grub &&
echo 'GRUB_CMDLINE_LINUX="cgroup_enable=memory swapaccount=1"' >> /etc/default/grub &&
sudo update-grub &&
sudo touch /etc/default/grub.d/mem_cgroup
echo cgroup/cgroup_grub >> /etc/default/grub.d/mem_group

#use template for global config to create a global config
sudo cp /usr/share/doc/cgroup-tools/examples/cgred.conf /etc/ &&

#create file to specify groups
sudo touch /etc/cgconfig.conf &&
cat cgroup/cgroup_cgconfig.conf >> /etc/cgconfig.conf &&

# create file to allocate programs to groups
sudo touch /etc/cgrules.conf &&
cat cgroup/cgroup_cgrules.conf >> /etc/cgrules.conf &&

# apply the rules, this needs to happen after all the above
sudo cgconfigparser -l /etc/cgconfig.conf &&
sudo cgrulesengd

# create the systemd files for config and rules
echo "Setting up cgroups to start at boot....." &&
sudo touch /etc/systemd/system/cgconfigparser.service &&
cat cgroup/cgroup_systemd_config >> /etc/systemd/system/cgconfigparser.service &&
sudo touch /etc/systemd/system/cgrulesparser.service &&
cat cgroup/cgroup_systemd_rules >> /etc/systemd/system/cgrulesengd.service &&

# restart systemctl to apply the changes above
sudo systemctl daemon-reload &&
sudo systemctl enable cgconfigparser --now &&
sudo systemctl enable cgrulesengd --now


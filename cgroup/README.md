# Memory Limited CGroup
This directory contains all the information needed by the system to implement a memory limited cgroup in which the user can run any processes they would like to mark for graceful shutdown. By constraining the memory a potential OOM-causing program can consume, we can ensure there will be enough memory to run any graceful shutdown process, which runs outside of that cgroup.

First, the cgroup_grub file contents are added to the grub menu to enable memory management. The implementation of memory management can be verified with the following command by noting the presence of the group "memory":

```ls /sys/fs/cgroup/```

Next, both of the .conf files, "cgroup_cgconfig.conf" and "cgroup_cgrules.conf", are used to create the ```/etc``` directories needed to implement the cgroup. Namely, the config file contains the memory limit for the cgroup and the rules file contains any app specific constraints if they exist. The rules are applied using the following:

```sudo cgconfigparser -l /etc/cgconfig.conf && sudo cgrulesengd```

You can verify the configuration has been applied using the following command:

```sudo cgget -g memory:memlimit```

Next, the systemd files, "cgroup_systemd_config" and "cgroup_systemd_rules", are used to create systemd entries so that the cgroup will be persistently created on subsequent reboots. Once the files are created the systemctl is restarted to apply the settings.

```sudo systemctl daemon-reload && sudo systemctl enable cgconfigparser --now && sudo systemctl enable cgrulesgend --now```

If any further changes are made to these files once they are implemented and the user does not wish to reboot for them to take effect, the following command can be used:

```sudo systemctl restart cgconfigparser && sudo systemctl restart cgrulesgend```

### Resources
https://www.lesbonscomptes.com/recoll/faqsandhowtos/cgroups_instructions.html

http://www.fernandoalmeida.net/blog/how-to-limit-cpu-and-memory-usage-with-cgroups-on-debian-ubuntu/

https://linuxmedium.com/how-to-enable-etc-rc-local-with-systemd-on-ubuntu-20-04/

https://unix.stackexchange.com/questions/34334/how-to-create-a-user-with-limited-ram-usage

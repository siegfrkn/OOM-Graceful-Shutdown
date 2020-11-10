
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/fs.h>                   /* file ops struct*/


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dylan Fox");

#define SUCCESS 0
#define DEVICE_NAME "call_usr_example"

static int Major;
static int Device_Open = 0;

static int device_open(struct inode *inode, struct file *file) {
  if (Device_Open) {
    return -EBUSY;
  }
  Device_Open++;
  try_module_get(THIS_MODULE);
  return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
  Device_Open--;
  module_put(THIS_MODULE);
  return SUCCESS;
}

static ssize_t device_read(struct file *filp,char *buffer, size_t length, loff_t * offset) {
// see https://developer.ibm.com/technologies/linux/articles/l-user-space-apps/
  char *argv[] = { "/home/dylan/Desktop/OS_project_examples/example_program.o", NULL };
  static char *envp[] = {
    "SHELL=/bin/bash",
    "HOME=/home/dylan",
    "USER=dylan",
    "TERM=xterm-256color",
    "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
    "DISPLAY=:0",
    "GNOME_SHELL_SESSION_MODE=ubuntu",
    "USERNAME=dylan",
    "PWD=/home/dylan/",
    NULL };
  // can wait for process to complete, go with waiting, or wait for it to be invoked
  // change UMH_WAIT_PROC to UMH_NO_WAIT or UMH_WAIT_EXEC
  int return_val = call_usermodehelper( argv[0], argv, envp, UMH_WAIT_PROC );
  printk(KERN_ALERT "return val: %d", return_val);
  return SUCCESS;
}

static struct file_operations fops = {
  .read = device_read,
  .write = NULL,
  .open = device_open,
  .release = device_release
};

int init_module() {
  // register as chr device
  Major = register_chrdev(0, DEVICE_NAME, &fops);
  if (Major < 0) {
    printk(KERN_ALERT "Registering device failed with %d\n", Major);
  }
  printk(KERN_INFO "mknod /dev/%s c %d 0.\n",DEVICE_NAME, Major);
  return SUCCESS;
}

void cleanup_module() {
  unregister_chrdev(Major, DEVICE_NAME);
}

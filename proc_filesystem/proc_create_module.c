
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
// #include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define BUFSIZE  100

#define PROCFS_MAX_SIZE		1024
#define PROCFS_NAME 		"graceful_shutdown"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Katrina Siegfried");

// Holds info about proc dir
static struct proc_dir_entry *graceful_shutdown_file;

static char* pid_p="";
static char* fpath_p="";

char pid[100];
char fpath[100];


// Create a write function that is called every time a proc write is made
static ssize_t mywrite(struct file *file, const char __user *ubuf,size_t count, loff_t *ppos)
{
	int c;
	char buf[BUFSIZE];
  printk( KERN_DEBUG "write handler\n");
  printk("user buffer: %s\n", ubuf);

	if(*ppos > 0 || count > BUFSIZE)
	{
		return -EFAULT;
	}

	if(copy_from_user(buf, ubuf, count))
	{
		return -EFAULT;
	}
	sscanf(buf,"%s %s",pid, fpath);

	pid_p = pid;
	fpath_p = fpath;
	c = strlen(buf);
	printk("ode output: %s %s\n", pid_p, fpath_p);
	*ppos = c;
	return c;
}

static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos)
{
	char buf[BUFSIZE];
	int len=0;
  printk( KERN_DEBUG "read handler\n");
	if(*ppos > 0 || count < BUFSIZE)
		return 0;

	len += sprintf(buf,"%s %s\n",pid_p, fpath_p);

	if(copy_to_user(ubuf,buf,len))
		return -EFAULT;
	printk("user buffer: %s\n", ubuf);

	*ppos = len;
	return len;
}

// Overwrite the default struct parameters for file_operations for this proc dir
static struct file_operations proc_fops =
{
	.owner = THIS_MODULE,
	.read = myread,
	.write = mywrite,
};

// Create a new entry in the proc file system
void create_new_proc_entry(void)
{
	graceful_shutdown_file = proc_create(PROCFS_NAME,0660,NULL,&proc_fops);
	if (graceful_shutdown_file == NULL)
	{
		proc_remove(graceful_shutdown_file);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
      PROCFS_NAME);
	}
}

// Init module for creating the new proc directory
static int proc_init(void)
{
	printk( KERN_DEBUG "\n\n\nmodule begin\n");
	create_new_proc_entry();
	return 0;
}

// Exit module for creating the new proc directory
static void proc_cleanup(void)
{
	proc_remove(graceful_shutdown_file);
	printk( KERN_DEBUG "module end\n");
}

module_init(proc_init);
module_exit(proc_cleanup);

/*
RESOURCES:
https://devarea.com/linux-kernel-development-creating-a-proc-file-and-interfacing-with-user-space/#.X6nKzIBKhhE
https://tuxthink.blogspot.com/2013/10/creating-read-write-proc-entry-in.html?m=1
https://linux.die.net/lkmpg/x769.html
https://elixir.bootlin.com/linux/latest/source/fs/proc/internal.h#L30
*/

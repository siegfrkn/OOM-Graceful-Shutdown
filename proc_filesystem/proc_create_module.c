
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
// #include <linux/slab.h> 
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>
#include <linux/types.h>
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
//set file path here
char *directory = "/home/rav2/Documents/test.txt";
 
// Create a write function that is called every time a proc write is made
static ssize_t mywrite(struct file *file, const char __user *ubuf,size_t count, loff_t *ppos) 
{
	printk(KERN_DEBUG "%d\n", file->f_flags);
	printk( KERN_DEBUG "write handler\n");
	printk("user buffer: %s\n", ubuf);
	int c;
	char num[100];
	char buf[BUFSIZE];
	
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

static char * read_file(void){
	struct file *f;
	void *buffer;
       	loff_t max_size = 0x1000, size = 0;

	f = filp_open(directory, O_RDONLY, 0);

	if(IS_ERR(f)){
			printk(KERN_INFO "Error opening file.\n");
			return NULL;
	}
	else{
		kernel_read_file_from_path(directory, &buffer, &size, max_size, READING_MODULE);
		char *file_contents = (char *)buffer;
		filp_close(f, NULL);
		return file_contents;
		
	}
	
		
}

static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
/*	printk( KERN_DEBUG "read handler\n");
	char *file_contents = read_file();
	printk(KERN_INFO "C %s\n", file_contents);
	char buf[BUFSIZE];
	int len=0;
	if(*ppos > 0 || count < BUFSIZE)
		return 0;

	len += sprintf(buf,"%s %s\n",pid_p, fpath_p);
	
	if(copy_to_user(ubuf,file_contents,100))
		return -EFAULT;
	printk("user buffer: %s\n", ubuf);

	*ppos = len;
	return len;*/
	static int finished=0; if(finished) {finished=0;return 0;} finished=1;
	char *file_contents = read_file();
	sprintf(ubuf, "%s", file_contents);
	return strlen(ubuf);
}

// Overwrite the default struct parameters for file_operations for this proc dir
static struct file_operations proc_fops = 
{
	.owner = THIS_MODULE,
	.read = myread,
	.write = mywrite,
	.llseek = seq_lseek,
};

// Create a new entry in the proc file system
void create_new_proc_entry(void) 
{
	graceful_shutdown_file = proc_create(PROCFS_NAME,0666,NULL,&proc_fops);
	if (graceful_shutdown_file == NULL)
	{
		proc_remove(graceful_shutdown_file);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		PROCFS_NAME);
		return -ENOMEM;
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
	remove_proc_entry("graceful_shutdown_file", NULL);
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


#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h> 
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define BUFSIZE  100
 
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Katrina Siegfried");

int len,temp;
char *msg;
 
// Create a write function that is called every time a proc write is made
static ssize_t mywrite(struct file *file, const char __user *ubuf,size_t count, loff_t *ppos) 
{
	raw_copy_from_user(msg,ubuf,count);
	printk( KERN_DEBUG "write handler\n");
	len=count;
	temp=len;
	return count;
}

// Create a read function that is called every time a proc read is made
static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	printk( KERN_DEBUG "read handler\n");
	if(count>temp)
	{
		count=temp;
	}
	temp=temp-count;
	raw_copy_to_user(ubuf,msg, count);
	if(count==0)
	{
		temp=len;
	}
	   
	return count;
}

// Overwrite the default struct parameters for file_operations for this proc dir
static struct file_operations proc_fops = 
{
	.read = myread,
	.write = mywrite,
};

// Create a new entry in the proc file system
void create_new_proc_entry(void) 
{
	// TODO: There is currently a permissions issue with this new proc dir, working it out
	proc_create("hello",0666,NULL,&proc_fops);
	msg=kmalloc(GFP_KERNEL,10*sizeof(char));
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
	// Uncomment the line below to remove the proc entry on exit of this module
	// remove_proc_entry("hello",NULL);

	printk( KERN_DEBUG "module end\n");
}
 
module_init(proc_init);
module_exit(proc_cleanup);

/*
RESOURCES:
https://devarea.com/linux-kernel-development-creating-a-proc-file-and-interfacing-with-user-space/#.X6nKzIBKhhE
https://tuxthink.blogspot.com/2013/10/creating-read-write-proc-entry-in.html?m=1
*/
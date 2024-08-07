/* **************** LDD:1.0 s_14/lab2_proc.c **************** */
/*
 * The code herein is: Copyright Jerry Cooperstein, 2009
 *
 * This Copyright is retained for the purpose of protecting free
 * redistribution of source.
 *
 *     URL:    http://www.coopj.com
 *     email:  coop@coopj.com
 *
 * The primary maintainer for this code is Jerry Cooperstein
 * The CONTRIBUTORS file (distributed with this
 * file) lists those known to have contributed to the source.
 *
 * This code is distributed under Version 2 of the GNU General Public
 * License, which you should have received with the source.
 *
 */
/*

* Using the /proc filesystem. (/proc/driver solution)
*
* Write a module that creates a /proc filesystem entry and can read
* and write to it.
*
* When you read from the entry, you should obtain the value of some
* parameter set in your module.
*
* When you write to the entry, you should modify that value, which
* should then be reflected in a subsequent read.
*
* Make sure you remove the entry when you unload your module.  What
* happens if you don't and you try to access the entry after the
* module has been removed?
*
* There are two different solutions given, one which creates the entry
* in the /proc directory, the other in /proc/driver.
@*/

#include "linux/fs.h"
#include "linux/types.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#if 0
#define NODE "my_proc"
#else
#define NODE "driver/my_proc"
#endif

static int param = 100;
static struct proc_dir_entry *my_proc;
void *my_seq_start(struct seq_file *s, loff_t *pos)
{
	if (*pos >= 1)
		return NULL;
	else
		return &asgn2_dev_count + *pos;
}
void *my_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	(*pos)++;

	if (*pos >= 1)
		return NULL;
	else
		return &asgn2_dev_count + *pos;
}
void my_seq_stop(struct seq_file *s, void *v)
{
	/* There's nothing to do here! */
}

int my_seq_show(struct seq_file *s, void *v)
{
	seq_printf(s, "Pages: %i\nMemory: %i\n", asgn2_device.num_pages,
		   asgn2_device.data_size);
	return 0;
}

static ssize_t my_proc_read(struct file *fd, char *__user u_buffer, size_t len,
			    loff_t *offset)
{
	/* *eof = 1; */
	return 1;
	/* return sprintf(page, "%d\n", param); */
}
struct seq_operations my_seq_ops = { .start = my_seq_start,
				     .next = my_seq_next,
				     .stop = my_seq_stop,
				     .show = my_seq_show };

static ssize_t my_proc_write(struct file *fd, const char *__user u_buffer,
			     size_t len, loff_t *offset)
{
	/* char *str; */
	/* str = kmalloc((size_t)count, GFP_KERNEL); */
	/* if (copy_from_user(str, buffer, count)) { */
	/*   kfree(str); */
	/*   return -EFAULT; */
	/* } */
	/* sscanf(str, "%d", &param); */
	/* printk(KERN_INFO "param has been set to %d\n", param); */
	/* kfree(str); */
	ssize_t count = 0;
	return count;
}

static int __init my_init(void)
{
	struct proc_ops ops = {
		.proc_read = my_proc_read,
		.proc_write = my_proc_write,
	};

	my_proc = proc_create("myproc", 0660, NULL, &ops);

	/**
   * create a proc entry with global read access and owner write access
   *  if fails, print an error message and return -1
   *
   * register my_proc_read to my_proc->read_proc
   * register my_proc_write to my_proc->write_proc
   */
	return 0;
}

static void __exit my_exit(void)
{
	/* COMPLETE ME */
	/**
   * remove the proc entry
   */
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein");
MODULE_DESCRIPTION("LDD:1.0 s_14/lab2_proc.c");
MODULE_LICENSE("GPL v2");

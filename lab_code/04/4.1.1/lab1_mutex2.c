/* **************** LDD:1.0 s_12/lab1_mutex2.c **************** */
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
 * Semaphore Contention
 *
 * second and third module to test semaphores
 @*/

#include <asm/atomic.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/semaphore.h>

extern struct mutex my_mutex;
extern struct semaphore my_sem;

static char *modname = __stringify(KBUILD_BASENAME);

static int __init my_init(void)
{
	printk(KERN_INFO "Trying to load module %s\n", modname);
	printk(KERN_INFO "\nStarting with semaphore state:  %u\n",
	       my_sem.count);

	if (down_interruptible(&my_sem)) {
		printk(KERN_INFO "semaphore unlocked - wake up \n");
		return -1;
	}
	printk(KERN_INFO "\nsemaphore state:  %u\n", my_sem.count);

	return 0;
}

static void __exit my_exit(void)
{
	up(&my_sem);
	printk(KERN_INFO "\n%s Semaphore end state:  %u\n", modname,
	       my_sem.count);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Tatsuo Kawasaki");
MODULE_DESCRIPTION("LDD:1.0 s_12/lab1_mutex2.c");
MODULE_LICENSE("GPL v2");

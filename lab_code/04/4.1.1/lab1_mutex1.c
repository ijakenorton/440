/* **************** LDD:1.0 s_12/lab1_mutex1.c **************** */
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
 * Mutex Contention
 *
 * Now do the same thing using semaphores instead of mutexes
 @*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/semaphore.h>

DEFINE_MUTEX(my_mutex);
DEFINE_SEMAPHORE(my_sem, 2);
EXPORT_SYMBOL(my_sem);

static int __init my_init(void)
{
	printk(KERN_INFO "\nStarting with semaphore state:  %u\n",
	       my_sem.count);
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "\nEnding with semaphore state:  %u\n", my_sem.count);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Tatsuo Kawasaki");
MODULE_DESCRIPTION("LDD:1.0 s_12/lab1_mutex1.c");
MODULE_LICENSE("GPL v2");

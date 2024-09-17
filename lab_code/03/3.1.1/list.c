/* **************** LDD:1.0 s_07/lab1_list.c **************** */
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
/* Linked lists
 *
 * Write a module that sets up a doubly-linked circular list of data
 * structures.  The data structure can be as simple as an integer
 * variable.
 *
 * Test inserting and deleting elements in the list.
 *
 * Walk through the list (using list_entry()) and print out values to
 * make sure the insertion and deletion processes are working.
 @*/

#include <linux/module.h>
#include "linux/gfp_types.h"
#include "linux/moduleparam.h"
#include "linux/printk.h"
#include <asm/atomic.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>

static LIST_HEAD(my_list);
static struct kmem_cache *my_cache;
static int size = PAGE_SIZE;
module_param(size, int, S_IRUGO);

typedef struct {
	struct list_head clist;
	int val;
} my_entry;

typedef struct {
	struct list_head head;
	void *read;
	void *write;
} d_list_t;

static int __init my_init(void)
{
	if (!(my_cache = kmem_cache_create("mycache", size, 0,
					   SLAB_HWCACHE_ALIGN, NULL))) {
		printk(KERN_ERR "kmem_cache_create failed\n");
		return -ENOMEM;
	}
	printk(KERN_INFO "successfully created cache");
	my_entry *ce;
	int k;

	for (k = 0; k < 5; k++) {
		ce = kmem_cache_alloc(my_cache, GFP_ATOMIC);
		/* ce = kmalloc(sizeof(my_entry), GFP_KERNEL); */
		ce->val = k;
		list_add(&ce->clist, &my_list);
	}
	printk(KERN_INFO "cache size %u", kmem_cache_size(my_cache));

	list_for_each_entry(ce, &my_list, clist) {
		printk(KERN_INFO "(entry): val %d", ce->val);
	}

	return 0;
}

static void __exit my_exit(void)
{
	my_entry *curr;
	my_entry *tmp;
	list_for_each_entry_safe(curr, tmp, &my_list, clist) {
		list_del(&curr->clist);
		printk(KERN_INFO "(exit): val %d removed\n", curr->val);
		kmem_cache_free(my_cache, curr);
	}
	kmem_cache_destroy(my_cache);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jake Norton");
/* many modifications by Jerry Cooperstein */
MODULE_DESCRIPTION("LDD:1.0 s_07/lab1_list.c");
MODULE_LICENSE("GPL v2");

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
#include <asm/atomic.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>

static LIST_HEAD(my_list);

typedef struct  {
	struct list_head clist;	
	int val;
}my_entry;


static int __init my_init(void)
{
	my_entry *ce;
	int k;

	for( k = 0; k < 5; k++){
		ce = kmalloc(sizeof(my_entry), GFP_KERNEL);
		ce->val = k;
		list_add(&ce->clist, &my_list); 
	}

	list_for_each_entry(ce, &my_list, clist){
		printk(KERN_INFO "(entry): val %d", ce->val);
	}


	/* COMPLETE ME
	 *
	 * add five nodes to my_list, and set the val of each node
	 *
	 * traverse list ce and print value of each node
	 */

	return 0;
}

static void __exit my_exit(void)
{
	my_entry *curr;
	my_entry *tmp;
	list_for_each_entry_safe(curr, tmp, &my_list, clist) {
		list_del(&curr->clist);
		printk(KERN_INFO "(exit): val %d removed\n", curr->val);
		kfree(curr);

	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jake Norton");
/* many modifications by Jerry Cooperstein */
MODULE_DESCRIPTION("LDD:1.0 s_07/lab1_list.c");
MODULE_LICENSE("GPL v2");

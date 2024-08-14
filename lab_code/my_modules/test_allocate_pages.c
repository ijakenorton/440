

#include <linux/module.h>
#include "linux/gfp.h"
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

typedef struct {
	struct list_head clist;
	int val;
} my_entry;

static int __init my_init(void)
{
	unsigned long addr;
	int k = 1;

	while (1) {
		addr = __get_free_pages(GFP_ATOMIC, k);
		printk(KERN_INFO "Current addr %lu", addr);

		if (addr == 0) {
			break;
		}

		free_pages(addr, k);
		k++;
	}

	printk(KERN_INFO "Allocated and deallocated %d pages", k);

	/* list_for_each_entry(ce, &my_list, clist) { */
	/* 	printk(KERN_INFO "(entry): val %d", ce->val); */
	/* } */

	return 0;
}

static void __exit my_exit(void)
{
	/* my_entry *curr; */
	/* my_entry *tmp; */
	/* int k = 0; */
	/* list_for_each_entry_safe(curr, tmp, &my_list, clist) { */
	/* 	list_del(&curr->clist); */
	/* 	kfree(curr); */
	/* 	k++; */
	/* } */

	printk(KERN_INFO "Exiting module");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jake Norton");
MODULE_DESCRIPTION("LDD:1.0 s_07/lab1_list.c");
MODULE_LICENSE("GPL v2");

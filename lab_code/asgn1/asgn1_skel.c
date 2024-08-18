/**
 * File: asgn1.c
 * Date: 08/08/2024
 * Author: Jake Norton
 * Version: 0.1
 *
 * This is a module which serves as a virtual ramdisk which disk size is
 * limited by the amount of memory available and serves as the requirement for
 * COSC440 assignment 1. This template is provided to students for their 
 * convenience and served as hints/tips, but not necessarily as a standard
 * answer for the assignment. So students are free to change any part of
 * the template to fit their design, not the other way around. 
 *
 * Note: multiple devices and concurrent modules are not supported in this
 *       version. The template is 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include "asm/page.h"
/* #include "asm/traps.h" */
#include "linux/atomic/atomic-instrumented.h"
#include "linux/device/class.h"
#include "linux/err.h"
#include "linux/gfp.h"
#include "linux/kern_levels.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/list.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/device.h>
#include <linux/sched.h>

#define MYDEV_NAME "asgn1"
#define MYIOC_TYPE 'k'
#define CACHE_SIZE (PAGE_SIZE * 10)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jake Norton");
MODULE_DESCRIPTION("COSC440 asgn1");

/**
 * The node structure for the memory page linked list.
 */
typedef struct page_node_rec {
	struct list_head list;
	struct page *page;
} page_node;

typedef struct asgn1_dev_t {
	dev_t dev; /* the device */
	struct cdev cdev;
	struct list_head mem_list;
	int num_pages; /* number of memory pages this module currently holds */
	size_t data_size; /* total data size in this module */
	atomic_t nprocs; /* number of processes accessing this device */
	atomic_t max_nprocs; /* max number of processes accessing this device */
	struct kmem_cache *cache; /* cache memory */
	int cache_size;
	struct class *class; /* the udev class */
	struct device *device; /* the udev device node */
} asgn1_dev;

asgn1_dev asgn1_device;

int asgn1_major = 0; /* major number of module */
int asgn1_minor = 0; /* minor number of module */
int asgn1_dev_count = 1; /* number of devices */

/**
 * This function frees all memory pages held by the module.
 */
void free_memory_pages(void)
{
	page_node *curr;
	page_node *tmp;
	list_for_each_entry_safe(curr, tmp, &asgn1_device.mem_list, list) {
		if (curr->page) {
			__free_page(curr->page);
		}

		kmem_cache_free(asgn1_device.cache, curr);
		list_del(&curr->list);
	}

	kmem_cache_destroy(asgn1_device.cache);
	asgn1_device.data_size = 0;
	asgn1_device.num_pages = 0;
	/* COMPLETE ME */
	/**
   * Loop through the entire page list {
   *   if (node has a page) {
   *     free the page
   *   }
   *   remove the node from the page list
   *   free the node
   * }
   * reset device data size, and num_pages
   */
}

/**
 * This function opens the virtual disk, if it is opened in the write-only
 * mode, all memory pages will be freed.
 */
int asgn1_open(struct inode *inode, struct file *filp)
{
	/* COMPLETE ME */
	/**
   * Increment process count, if exceeds max_nprocs, return -EBUSY
   *
   * if opened in write-only mode, free all memory pages
   *
   */

	return 0; /* success */
}

/**
 * This function releases the virtual disk, but nothing needs to be done
 * in this case. 
 */
int asgn1_release(struct inode *inode, struct file *filp)
{
	/* COMPLETE ME */
	/**
   * decrement process count
   */
	return 0;
}

/**
 * This function reads contents of the virtual disk and writes to the user 
 */
ssize_t asgn1_read(struct file *filp, char __user *buf, size_t count,
		   loff_t *f_pos)
{
	printk(KERN_INFO "Starting read with f_pos %lld", *f_pos);
	printk(KERN_INFO "Starting read with original count %d", count);
	if (*f_pos >= asgn1_device.data_size) {
		return 0;
	}

	size_t size_read = 0;
	/* size read from virtual disk in this function */ /* the offset from the beginning of a page to start writing */
	size_t begin_offset = (size_t)*f_pos % PAGE_SIZE;
	int begin_page_no = *f_pos / PAGE_SIZE; /* the first page which contains
					     the requested data */
	/* count = min(count, asgn1_device.data_size - begin_offset); */
	count = min(count, asgn1_device.data_size);

	printk(KERN_INFO "STARTING OFFSET %d", begin_offset);
	printk(KERN_INFO "Min of count %d", count);
	int curr_page_no; /* the current page number */
	size_t curr_size_read; /* size read from the virtual disk in this round */
	size_t size_to_be_read; /* size to be read in the current round in 
			       while loop */

	printk(KERN_WARNING "Passed init");
	if (asgn1_device.mem_list.next == NULL) {
		printk(KERN_WARNING
		       "The asgn1_device.mem_list.next pointer is null");
		return -EFAULT;
	}
	struct list_head *ptr = asgn1_device.mem_list.next;
	page_node *curr;

	for (curr_page_no = 0; curr_page_no < begin_page_no; curr_page_no++) {
		ptr = ptr->next;
	}

	printk(KERN_WARNING "moved to page");
	if (ptr == NULL) {
		printk(KERN_WARNING "The curr pointer is null");
		return -EFAULT;
	}
	curr = list_entry(ptr, page_node, list);
	unsigned long size_not_read;

	while (size_read < count) {
		printk(KERN_INFO "start of while loop");
		size_to_be_read = min((count - size_read),
				      PAGE_SIZE - (size_t)begin_offset);
		if (curr == NULL) {
			printk(KERN_WARNING "The curr is NULL");
			return -EFAULT;
		}
		if (curr->page == NULL) {
			printk(KERN_WARNING "The curr page is NULL");
			return -EFAULT;
		}
		void *current_address = page_address(curr->page);
		printk(KERN_INFO "Current page address %p", current_address);
		current_address += begin_offset;
		printk(KERN_INFO "Current page address after offset %p",
		       current_address);
		/* size_ */
		size_not_read = copy_to_user(buf, page_address(curr->page),
					     size_to_be_read);

		if (size_not_read != 0) {
			if (size_read > 0) {
				printk(KERN_WARNING
				       "size_not_read %lu exiting...",
				       size_not_read);
				return size_not_read;
			}
			return -EINVAL;
		}
		size_read += size_to_be_read;
		*f_pos += size_to_be_read;
		buf += size_to_be_read;
		/* begin_offset = *f_pos % PAGE_SIZE; */
		if (size_read < count) {
			if (list_is_last(&curr->list, &asgn1_device.mem_list)) {
				printk(KERN_INFO "size_not_read %lu exiting...",
				       size_not_read);
				printk(KERN_INFO
				       "list is last size_read %d exiting...",
				       size_read);
				return size_read;
			}
			curr = list_entry(curr->list.next, page_node, list);
		}
	}
	/* COMPLETE ME */
	/**
   * check f_pos, if beyond data_size, return 0
   * 
   * Traverse the list, once the first requested page is reached,
   *   - use copy_to_user to copy the data to the user-space buf page by page
   *   - you also need to work out the start / end offset within a page
   *   - Also needs to handle the situation where copy_to_user copy less
   *       data than requested. If copy_to_user returns non-zero
   *       the data is not completely copied. In case partial data
   *       is copied, return the number of bytes copied. Otherwise,
   *       return -EINVAL for invalid user buffer.
   *
   * if end of data area of ramdisk reached before copying the requested
   *   return the size copied to the user space so far
   */
	printk(KERN_INFO "Finished read successfully after reading %d",
	       size_read);

	return size_read;
}

static loff_t asgn1_lseek(struct file *file, loff_t offset, int cmd)
{
	printk(KERN_INFO "STARTING SEEK");
	loff_t test_pos = 0;
	size_t buffer_size = asgn1_device.num_pages * PAGE_SIZE;

	switch (cmd) {
	case SEEK_SET:
		test_pos = offset;
		break;
	case SEEK_CUR:
		test_pos = file->f_pos + offset;
		break;
	case SEEK_END:
		test_pos = (buffer_size - 1) - offset;
		break;
	default:
		return -EINVAL;
	}
	if (test_pos < 0) {
		test_pos = 0;
		file->f_pos = test_pos;
	}

	if (test_pos > buffer_size) {
		test_pos = buffer_size;
	}

	file->f_pos = test_pos;

	printk(KERN_INFO "Seeking to pos=%ld\n", (long)test_pos);
	return test_pos;
}

/**
 * This function writes from the user buffer to the virtual disk of this
 * module
 */
ssize_t asgn1_write(struct file *filp, const char __user *buf, size_t count,
		    loff_t *f_pos)
{
	printk(KERN_INFO "Starting write");
	if (count <= 0) {
		return 0;
	}
	/* Shouldn't be possible? */
	if (*f_pos > asgn1_device.data_size) {
		printk(KERN_WARNING
		       "Starting f_pos .%lld is more than data_size, stopping write..",
		       *f_pos);
		return -EINVAL;
	}
	size_t orig_f_pos = *f_pos; /* the original file position */
	printk(KERN_INFO "Starting f_pos %lld", *f_pos);
	size_t size_written =
		0; /* size written to virtual disk in this function */
	size_t begin_offset =
		*f_pos %
		PAGE_SIZE; /* the offset from the beginning of a page to
			       start writing */
	int begin_page_no = *f_pos / PAGE_SIZE; /* the first page this function
					      should start writing to */

	int curr_page_no; /* the current page number */
	size_t curr_size_written =
		0; /* size written to virtual disk in this round */
	size_t size_to_be_written; /* size to be read in the current round in 
				 while loop */

	size_t size_not_written;
	page_node *curr;

	/* COMPLETE ME */
	//Traverse the list until the first page reached, and add nodes if necessary

	if (list_empty(&asgn1_device.mem_list)) {
		printk(KERN_INFO "Creating first page");
		curr = kmem_cache_alloc(asgn1_device.cache, GFP_KERNEL);
		curr->page = alloc_page(GFP_KERNEL);
		list_add_tail(&curr->list, &asgn1_device.mem_list);
		asgn1_device.num_pages++;
	} else {
		curr = list_first_entry(&asgn1_device.mem_list, page_node,
					list);
		for (curr_page_no = 1; curr_page_no < begin_page_no;
		     curr_page_no++) {
			if (list_is_last(&curr->list, &asgn1_device.mem_list)) {
				break;
			}
			curr = list_entry(curr->list.next, page_node, list);
		}
	}
	/* Then write the data page by page, remember to handle the situation */
	/*   when copy_from_user() writes less than the amount you requested. */
	/*       If copy_from_user returns non-zero */
	/*       the data is not completely copied. In case partial data */
	/*       is copied, return the number of bytes copied. Otherwise, */
	/*       return -EINVAL for invalid user buffer. */
	while (size_written < count) {
		printk(KERN_WARNING "%d", begin_offset);
		// There is still size to be written
		// We not at the start of the device
		// We need to start writing at the start of next page
		if (*f_pos != 0 && begin_offset == 0) {
			if (list_is_last(&curr->list, &asgn1_device.mem_list)) {
				printk(KERN_INFO "Creating page");
				curr = kmem_cache_alloc(asgn1_device.cache,
							GFP_KERNEL);
				curr->page = alloc_page(GFP_KERNEL);
				list_add_tail(&curr->list,
					      &asgn1_device.mem_list);
				asgn1_device.num_pages++;
			} else {
				printk(KERN_INFO
				       "moving pointer to next element");
				curr = list_entry(curr->list.next, page_node,
						  list);
			}
		}
		size_to_be_written =
			min((count - size_written), PAGE_SIZE - begin_offset);
		size_not_written =
			copy_from_user(page_address(curr->page) + begin_offset,
				       buf, size_to_be_written);
		if (size_not_written != 0) {
			if (size_written > 0) {
				printk(KERN_INFO
				       "size_not_written %d exiting...",
				       size_not_written);
				return size_not_written;
			}
			return -EINVAL;
		}
		size_written += size_to_be_written;
		*f_pos += size_to_be_written;
		buf += size_to_be_written;
		printk(KERN_INFO "current f_pos %lld", *f_pos);
		begin_offset = *f_pos % PAGE_SIZE;
	}
	printk(KERN_INFO "Using %d pages\n", asgn1_device.num_pages);

	asgn1_device.data_size =
		max(asgn1_device.data_size, orig_f_pos + size_written);
	printk(KERN_INFO "Data size is %d bytes\n", asgn1_device.data_size);
	printk(KERN_INFO "current f_pos at end %lld", *f_pos);
	printk(KERN_INFO "Successful wrote %d bytes\n", size_written);
	printk(KERN_INFO "FINISHED THE WRITE");
	return size_written;
}

#define SET_NPROC_OP 1
#define TEM_SET_NPROC _IOW(MYIOC_TYPE, SET_NPROC_OP, int)

/**
 * The ioctl function, which nothing needs to be done in this case.
 */
long asgn1_ioctl(struct file *filp, unsigned cmd, unsigned long arg)
{
	int nr;
	int new_nprocs;
	int result;
	if (_IOC_TYPE(cmd) != MYIOC_TYPE)
		return -EINVAL;
	//TODO check validity of arg
	if (cmd == SET_NPROC_OP) {
		atomic_set(&asgn1_device.max_nprocs, (int)arg);
		return 0;
	}
	/* COMPLETE ME */
	/** 
   * check whether cmd is for our device, if not for us, return -EINVAL 
   *
   * get command, and if command is SET_NPROC_OP, then get the data, and
     set max_nprocs accordingly, don't forget to check validity of the 
     value before setting max_nprocs
   */

	return -ENOTTY;
}

static int asgn1_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long pfn;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long len = vma->vm_end - vma->vm_start;
	unsigned long ramdisk_size = asgn1_device.num_pages * PAGE_SIZE;
	page_node *curr;
	unsigned long index = 0;

	/* COMPLETE ME */
	/**
     * check offset and len
     *
     * loop through the entire page list, once the first requested page
     *   reached, add each page with remap_pfn_range one by one
     *   up to the last requested page
     */
	return 0;
}

struct file_operations asgn1_fops = { .owner = THIS_MODULE,
				      .read = asgn1_read,
				      .write = asgn1_write,
				      .unlocked_ioctl = asgn1_ioctl,
				      .open = asgn1_open,
				      .mmap = asgn1_mmap,
				      .release = asgn1_release,
				      .llseek = asgn1_lseek };

static void *my_seq_start(struct seq_file *s, loff_t *pos)
{
	if (*pos >= 1)
		return NULL;
	else
		return &asgn1_dev_count + *pos;
}
static void *my_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	(*pos)++;
	if (*pos >= 1)
		return NULL;
	else
		return &asgn1_dev_count + *pos;
}
static void my_seq_stop(struct seq_file *s, void *v)
{
	/* There's nothing to do here! */
}

int my_seq_show(struct seq_file *s, void *v)
{
	/* COMPLETE ME */
	/**
   * use seq_printf to print some info to s
   */
	return 0;
}

static struct seq_operations my_seq_ops = { .start = my_seq_start,
					    .next = my_seq_next,
					    .stop = my_seq_stop,
					    .show = my_seq_show };

static int my_proc_open(struct inode *inode, struct file *filp)
{
	return seq_open(filp, &my_seq_ops);
}

static struct proc_ops asgn1_proc_ops = {
	.proc_open = my_proc_open,
	.proc_lseek = seq_lseek,
	.proc_read = seq_read,
	.proc_release = seq_release,
};

/* typedef struct asgn1_dev_t { */
/* 	dev_t dev; /1* the device *1/ */
/* 	struct cdev cdev; */
/* 	struct list_head mem_list; */
/* 	int num_pages; /1* number of memory pages this module currently holds *1/ */
/* 	size_t data_size; /1* total data size in this module *1/ */
/* 	atomic_t nprocs; /1* number of processes accessing this device *1/ */
/* 	atomic_t max_nprocs; /1* max number of processes accessing this device *1/ */
/* 	struct kmem_cache *cache; /1* cache memory *1/ */
/* 	struct class *class; /1* the udev class *1/ */
/* 	struct device *device; /1* the udev device node *1/ */
/* } asgn1_dev; */

/**
 * Initialise the module and create the master device
 */
int __init asgn1_init_module(void)
{
	int rv;

	if ((rv = alloc_chrdev_region(&asgn1_device.dev, 0, 1, MYDEV_NAME) <
		  0)) {
		return rv;
	}
	/* COMPLETE ME */
	/**
           * set nprocs and max_nprocs of the device
           *
           * allocate major number
           * allocate cdev, and set ops and owner field 
           * add cdev
           * initialize the page list
           * create proc entries
           */

	if (IS_ERR(asgn1_device.class = class_create(MYDEV_NAME))) {
		unregister_chrdev_region(asgn1_device.dev, 1);
		return PTR_ERR(asgn1_device.class);
	}

	if (IS_ERR(asgn1_device.device = device_create(asgn1_device.class, NULL,
						       asgn1_device.dev, "%s",
						       MYDEV_NAME))) {
		printk(KERN_WARNING "%s: can't create device\n", MYDEV_NAME);
		class_destroy(asgn1_device.class);
		unregister_chrdev_region(asgn1_device.dev, 1);
		return PTR_ERR(asgn1_device.device);
	}

	cdev_init(&asgn1_device.cdev, &asgn1_fops);
	if ((rv = cdev_add(&asgn1_device.cdev, asgn1_device.dev, 1)) < 0) {
		printk(KERN_WARNING "%s: can't create udev device\n",
		       MYDEV_NAME);
		device_destroy(asgn1_device.class, asgn1_device.dev);
		class_destroy(asgn1_device.class);
		unregister_chrdev_region(asgn1_device.dev, 1);
	}

	printk(KERN_WARNING "set up udev entry\n");
	printk(KERN_WARNING "Hello world from %s\n", MYDEV_NAME);

	/* Initialise fields */
	INIT_LIST_HEAD(&asgn1_device.mem_list);
	asgn1_device.num_pages = 0;
	atomic_set(&asgn1_device.nprocs, 0);
	atomic_set(&asgn1_device.max_nprocs, 5);
	asgn1_device.cache_size = CACHE_SIZE;

	if (!(asgn1_device.cache =
		      kmem_cache_create("cache", asgn1_device.cache_size, 0,
					SLAB_HWCACHE_ALIGN, NULL))) {
		printk(KERN_ERR "kmem_cache_create failed\n");
		cdev_del(&asgn1_device.cdev);
		device_destroy(asgn1_device.class, asgn1_device.dev);
		class_destroy(asgn1_device.class);
		unregister_chrdev_region(asgn1_device.dev, 1);
		return -ENOMEM;
	}

	printk(KERN_INFO "successfully created cache");
	return 0;

	/* cleanup code called when any of the initialization steps fail */
	/* fail_device: */
	/* 	class_destroy(asgn1_device.class); */
	/* 	unregister_chrdev_region(asgn1_device.dev, 1); */
	/* 	device_destroy(asgn1_device.class, asgn1_device.dev); */

	return 0;
}

/**
 * Finalise the module
 */
void __exit asgn1_exit_module(void)
{
	free_memory_pages();
	cdev_del(&asgn1_device.cdev);
	device_destroy(asgn1_device.class, asgn1_device.dev);
	class_destroy(asgn1_device.class);
	unregister_chrdev_region(asgn1_device.dev, 1);
	printk(KERN_WARNING "cleaned up udev entry\n");

	/* COMPLETE ME */
	/**
   * free all pages in the page list 
   * cleanup in reverse order
   */
	printk(KERN_WARNING "Good bye from %s\n", MYDEV_NAME);
}

module_init(asgn1_init_module);
module_exit(asgn1_exit_module);

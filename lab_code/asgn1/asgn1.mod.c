#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x4b49c976, "proc_create" },
	{ 0x4bce4a10, "seq_release" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x70dd78f1, "class_destroy" },
	{ 0x287e81b0, "remap_pfn_range" },
	{ 0xa63c3d95, "seq_lseek" },
	{ 0x372ddcc1, "kmem_cache_create" },
	{ 0x92997ed8, "_printk" },
	{ 0xbc10dd97, "__put_user_4" },
	{ 0x92a1ef16, "__free_pages" },
	{ 0xc5ca225b, "kmem_cache_alloc" },
	{ 0x89b05fd3, "cdev_add" },
	{ 0xa76c78c8, "device_create" },
	{ 0x58cffff9, "class_create" },
	{ 0xae2ca04d, "kmem_cache_free" },
	{ 0x5f754e5a, "memset" },
	{ 0x48c78dde, "__alloc_pages" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xc11cdbdd, "seq_read" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x987c11c7, "__pv_phys_pfn_offset" },
	{ 0x353e3fa5, "__get_user_4" },
	{ 0x76646418, "device_destroy" },
	{ 0xddade1ae, "remove_proc_entry" },
	{ 0xf0648648, "seq_printf" },
	{ 0x5b242f5, "seq_open" },
	{ 0xab528595, "mem_map" },
	{ 0x8e1ca6d9, "cdev_init" },
	{ 0x34bebc18, "cdev_del" },
	{ 0x56888907, "kmem_cache_destroy" },
	{ 0xa6f3f0f1, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "695913F0D663FF52277C725");

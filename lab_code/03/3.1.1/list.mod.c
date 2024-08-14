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
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x372ddcc1, "kmem_cache_create" },
	{ 0x92997ed8, "_printk" },
	{ 0xc5ca225b, "kmem_cache_alloc" },
	{ 0x517c4e96, "kmem_cache_size" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xae2ca04d, "kmem_cache_free" },
	{ 0x56888907, "kmem_cache_destroy" },
	{ 0x6171c3bf, "param_ops_int" },
	{ 0xa6f3f0f1, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C2AA303A5903FD76E60F0CC");

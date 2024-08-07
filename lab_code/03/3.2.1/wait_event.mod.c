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

__visible struct module __this_module __section(".gnu.linkonce.this_module") = {
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

static const struct modversion_info ____versions[] __used
	__section("__versions") = {
		{ 0x92997ed8, "_printk" },
		{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
		{ 0x74a49362, "module_refcount" },
		{ 0xb1ad28e0, "__gnu_mcount_nc" },
		{ 0x96603250, "kmalloc_large" },
		{ 0x1870937, "misc_register" },
		{ 0x5e30387c, "misc_deregister" },
		{ 0x37a0cba, "kfree" },
		{ 0xae353d77, "arm_copy_from_user" },
		{ 0x5f754e5a, "memset" },
		{ 0x2cfde9a2, "warn_slowpath_fmt" },
		{ 0x51a910c0, "arm_copy_to_user" },
		{ 0xa6f3f0f1, "module_layout" },
	};

MODULE_INFO(depends, "");

MODULE_INFO(srcversion, "7994EEEE4CB36C29C32C796");

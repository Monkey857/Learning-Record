#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

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
	{ 0x4cf819e6, "module_layout" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x1d19f77b, "physical_mask" },
	{ 0xc224abae, "boot_cpu_data" },
	{ 0xa648e561, "__ubsan_handle_shift_out_of_bounds" },
	{ 0xa22a96f7, "current_task" },
	{ 0x6a5cb5ee, "__get_free_pages" },
	{ 0xdad13544, "ptrs_per_p4d" },
	{ 0x72d79d83, "pgdir_shift" },
	{ 0x8a35b432, "sme_me_mask" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x33a21a09, "pv_ops" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "DBEF61C4E8B93AB60CFBCBC");

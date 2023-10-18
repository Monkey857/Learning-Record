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
	{ 0xa45c7b90, "stack_trace_print" },
	{ 0x828e22f4, "hrtimer_forward" },
	{ 0x63026490, "unregister_kprobe" },
	{ 0x46a4b118, "hrtimer_cancel" },
	{ 0xfcca5424, "register_kprobe" },
	{ 0xb43f9365, "ktime_get" },
	{ 0x2d5f69b3, "rcu_read_unlock_strict" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x3c5d543a, "hrtimer_start_range_ns" },
	{ 0xe8f001e9, "init_task" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x92997ed8, "_printk" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x2d0684a9, "hrtimer_init" },
	{ 0xf1e98c74, "avenrun" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "6E99E615EA8337CC2352821");

#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd394fba2, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x2e8cfdb5, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xf1d6de08, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x7207b75e, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x934d65f5, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0xadc8d6e5, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0xdea9ca32, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0xa044f8d8, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xa99a3fbe, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "EC6D635858FC1240172B003");

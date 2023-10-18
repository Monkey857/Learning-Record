#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YYS");
MODULE_DESCRIPTION("Kernel Module with File 1");

extern void myfun2(void);
extern void myfun3(void);


static int __init test_module_init(void) {
    printk("Into File one......\n");
    myfun2();
    myfun3();
    return 0;
}

static void __exit test_module_exit(void) {
    printk("Exit the module......\n");
}
module_init(test_module_init);
module_exit(test_module_exit);

#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/kernel.h>


MODULE_LICENSE("GPL");

void myfun3(void){
    printk("Into File three......\n");
}

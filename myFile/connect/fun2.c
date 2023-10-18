#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/kernel.h>


MODULE_LICENSE("GPL");

void myfun2(void){
    printk("Into File two......\n");
}

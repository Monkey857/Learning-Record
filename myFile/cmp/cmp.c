#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
static int x;
static int y;
module_param(x,int,0644);
module_param(y,int,0644);
static int __init cmp_handler(void){
    int max;
    max = max(x,y);
    printk("max=%d\n",max);
    return 0;
}
static void __exit cmp_exit(void){
    printk("EXIT THE CMP MODULE!!\n");
    return;
}
module_init(cmp_handler);
module_exit(cmp_exit);
MODULE_LICENSE("GPL");


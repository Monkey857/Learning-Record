#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#include<linux/kernel.h>

static int irq;         //申请的中断号
static char *interface; //设备名称，本实验中使用ens33（网卡）
static int count = 0;   //统计的总次数

//传递参数
module_param(interface,charp,0644);
module_param(irq,int,0644); 

//中断服务程序
static irqreturn_t intr_handler(int irq,void *dev_id){
    static long interval = 0;   //记录时间间隔
    if(count == 0)
        interval = jiffies;     //特殊处理第一次记录
    interval = jiffies - interval;   //时间差
    printk("The interval between two interrupts is %ld\n",interval);
    interval = jiffies;
    count++;
    return IRQ_NONE;
}

//模块初始化函数
static int __init intr_init(void){
	//interface表示与中断相关的设备名，&irq提供唯一的标志信息
    if(request_irq(irq,&intr_handler,IRQF_SHARED,interface,&irq)){
        printk(KERN_ERR"Fails to register IRQ %d\n",irq);
        return -EIO;
    }
    printk("%s Request on IRQ %d succeeded\n",interface,irq); //表示申请成功
    return 0;
}
static void __exit intr_exit(void){
    printk("The %d interrupts happened on irq %d",count,irq);
    free_irq(irq,&irq);  //删除自定义的中断
    printk("Freeing IRQ %d\n",irq);
    return;
}
module_init(intr_init);
module_exit(intr_exit);

MODULE_LICENSE("GPL");

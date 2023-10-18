#include <linux/interrupt.h>
#include<linux/irq.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");
static int irq=13;  //13号中断
 
// 自定义中断处理函数
static irqreturn_t myhandler(int irq, void *dev_id)
{
    printk("the irq is :%d\n", irq);  //irq是对应中断的中断号
    printk("in the interrupt handler function\n");
    return IRQ_HANDLED;
}

static int __init request_irq_init(void)
{
    
    int result=0;
    printk("into request_irq_init\n");
    /*调用函数request_irq( )申请中断，irq指中断编号，irq_handler是中断处理函数，IRQF_DISABLED
      是中断类型，“A_New_Device”指中断设备名，NULL指设备，设备为NULL说明设备不真实存在*/
    result=request_irq(irq, myhandler, IRQF_NO_SUSPEND, "A_New_Device", NULL);
    printk("the result of the request_irq is: %d\n", result);    //显示申请结果
    printk("out request_irq_init\n");
    return 0;
}
 
static void __exit request_irq_exit(void)
{
    free_irq(irq, NULL); //释放申请的中断
    printk("Goodbye request_irq\n");
    return;
}
 
module_init(request_irq_init);
module_exit(request_irq_exit);

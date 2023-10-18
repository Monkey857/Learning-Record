#include <linux/init.h>
#include <linux/module.h>
#include <linux/irq.h>
static int __init interrupt_table_info_init(void)
{
    int irq;

    printk(KERN_INFO "Interrupt Vector Table Information:\n");

    for (irq = 0; irq < NR_IRQS; irq++) {
        struct irq_desc *desc = irq_to_desc(irq);

        if (desc) {
            printk(KERN_INFO "IRQ %d:\n", irq);
            printk(KERN_INFO " Name: %s\n", desc->name ? desc->name : "N/A");
            printk(KERN_INFO " Handler Address: 0x%p\n", desc->handle_irq);
           // printk(KERN_INFO " Status: %s\n", (desc->status & IRQ_DISABLED) ? "Disabled" : "Enabled");
            //printk(KERN_INFO " Affinity: 0x%llx\n", desc->irq_data.affinity);

            // You can print more information from the irq_data structure if needed.

            printk(KERN_INFO "\n");
        }
    }

    return 0;
}

static void __exit interrupt_table_info_exit(void)
{
    printk(KERN_INFO "Interrupt Table Info module removed.\n");
}

module_init(interrupt_table_info_init);
module_exit(interrupt_table_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mr.Y");
MODULE_DESCRIPTION("Interrupt Table Info Module");

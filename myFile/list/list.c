#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YYS");
MODULE_DESCRIPTION("Kernel Module with Linked List");

// 定义一个结构体表示链表节点
struct my_node {
    int data;
    struct list_head list; // 内核提供的链表头
};

// 定义一个链表头
static LIST_HEAD(my_list);

static int __init linked_list_module_init(void) {
    struct my_node *node;
    int i;

    printk(KERN_INFO "Linked List Module: Initializing\n");

    // 插入100个节点到链表中
    for (i = 1; i <= 100; ++i) {
        node = kmalloc(sizeof(struct my_node), GFP_KERNEL);
        if (!node) {
            printk(KERN_ERR "Memory allocation failed\n");
            return -ENOMEM;
        }

        node->data = i;
        INIT_LIST_HEAD(&node->list); // 初始化节点的链表头

        list_add_tail(&node->list, &my_list); // 添加节点到链表末尾
    }

    // 删除10个节点
    for (i = 1; i <= 10; ++i) {
        if (!list_empty(&my_list)) {
            struct list_head *entry = my_list.next;
            struct my_node *node = list_entry(entry, struct my_node, list);
            printk(KERN_INFO "Removing node with data: %d\n", node->data);
            list_del(entry);
            kfree(node);
        }
    }

    // 遍历并输出剩余节点
    struct list_head *pos;
    struct my_node *curr;
    list_for_each(pos, &my_list) {
        curr = list_entry(pos, struct my_node, list);
        printk(KERN_INFO "Remaining node data: %d\n", curr->data);
    }

    return 0;
}

static void __exit linked_list_module_exit(void) {
    printk(KERN_INFO "Linked List Module: Exiting\n");
}

module_init(linked_list_module_init);
module_exit(linked_list_module_exit);

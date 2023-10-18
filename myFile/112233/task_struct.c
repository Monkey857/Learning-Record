#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int __init task_struct_info_init(void) {
    struct task_struct *task = current; // 获取当前进程的 task_struct 结构体指针

    // 打印进程的10个字段信息
    printk(KERN_INFO "进程信息：\n");
    printk(KERN_INFO "PID: %d\n", task->pid);
    printk(KERN_INFO "进程状态: %ld\n", task->__state);
    printk(KERN_INFO "进程优先级: %d\n", task->prio);
    printk(KERN_INFO "进程静态优先级: %d\n", task->static_prio);
    printk(KERN_INFO "进程动态优先级: %d\n", task->normal_prio);
    printk(KERN_INFO "进程调度策略: %d\n", task->policy);
    printk(KERN_INFO "进程父进程的PID: %d\n", task->parent->pid);
    printk(KERN_INFO "进程进程组的ID: %d\n", task->tgid);
    printk(KERN_INFO "进程进程组的leader的PID: %d\n", task->group_leader->pid);
    printk(KERN_INFO "进程命令行: %s\n", task->comm);

    return 0;
}

static void __exit task_struct_info_exit(void) {
    printk(KERN_INFO "模块退出\n");
}

module_init(task_struct_info_init);
module_exit(task_struct_info_exit);

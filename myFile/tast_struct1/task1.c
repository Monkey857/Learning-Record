#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int target_pid = 0; // 指定的进程号

//传入参数定义
module_param(target_pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(target_pid, "指定的进程号");

static int __init task_struct_info_init(void) {
    //通过调用内核提供的方法，就可以通过pid来获取到它的task_struct结构体了
    struct pid * kpid;
    struct task_struct *task;
    kpid = find_get_pid(target_pid);
    task = get_pid_task(kpid, PIDTYPE_PID);
    
    if (task == NULL) {
        printk(KERN_INFO "找不到进程号为 %d 的进程\n", target_pid);
        return -EINVAL;
    }

   // 打印进程的10个字段信息
    printk(KERN_INFO "进程信息：\n");
    printk(KERN_INFO "PID: %d\n", task->pid);
    printk(KERN_INFO "进程状态: %ld\n", task->__state);
    printk(KERN_INFO "进程的实时优先级: %d\n", task->rt_priority);
    printk(KERN_INFO "进程的优先级: %d\n", task->prio);
    printk(KERN_INFO "进程退出时的状态码: %d\n", task->exit_state);
    printk(KERN_INFO "进程调度策略: %d\n", task->policy);
    printk(KERN_INFO "进程父进程的PID: %d\n", task->parent->pid);
    printk(KERN_INFO "进程标记符: %#x\n", task->flags);
    printk(KERN_INFO "当前进程所占的cpu编号: %d\n", task->cpu);
    printk(KERN_INFO "进程命令行: %s\n", task->comm);
    return 0;
}

static void __exit task_struct_info_exit(void) {
    printk(KERN_INFO "模块退出\n");
}

module_init(task_struct_info_init);
module_exit(task_struct_info_exit);

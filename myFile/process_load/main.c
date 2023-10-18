
#include <linux/stacktrace.h> /* for stack_trace_print */
#include <linux/module.h> /* for module_*, MODULE_*, printk */
#include <linux/hrtimer.h> /* for hrtimer_*, ktime_* */
#include <linux/sched/loadavg.h> /* for avenrun, LOAD_* */
#include <linux/sched.h> /* for struct task_struct */
#include <linux/sched/signal.h> /* for do_each_thread, while_each_thread */
#include "load.h" /* for find_kallsyms_lookup_name */
#define BACKTRACE_DEPTH 20 /* 最大栈深度 */
void (*ShowStack)(struct task_struct *task, unsigned long *sp, const char *loglvl); /* 将要指向stack_show函数，可以直接输出进程控制块的调用栈 */
unsigned int (*StackTraceSaveTask)(struct task_struct *tsk, unsigned long *store, unsigned int size, unsigned int skipnr); /* 将要指向stack_trace_save_tsk */
static void print_all_task_stack(void) { /* 打印全部进程调用栈 */
    struct task_struct *g, *p; /* 用于遍历进程 */
    unsigned long backtrace[BACKTRACE_DEPTH]; /* 用于存储调用栈的函数地址 */
    unsigned int nr_bt; /* 用于存储调用栈的层数 */
    printk("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printk("Load: %lu.%02lu, %lu.%02lu, %lu.%02lu\n", /* 输出近期平均负载 */
        LOAD_INT(avenrun[0]), LOAD_FRAC(avenrun[0]),
        LOAD_INT(avenrun[1]), LOAD_FRAC(avenrun[1]),
        LOAD_INT(avenrun[2]), LOAD_FRAC(avenrun[2]));
    rcu_read_lock(); /* 为运行队列上锁 */
    printk("dump running task.\n");
    do_each_thread(g, p) { /* 遍历运行队列 */
        if(p->__state == TASK_RUNNING) {
            printk("running task, comm: %s, pid %d\n", p->comm, p->pid);
            // show_stack(p, NULL, ""); /* 可以取代下面两个语句 */
            nr_bt = StackTraceSaveTask(p, backtrace, BACKTRACE_DEPTH, 0); /* 保存栈 */ // 和下面一个语句一起可以取代上面一条语句
            stack_trace_print(backtrace, nr_bt, 0); /* 打印栈 */
        }
    } while_each_thread(g, p);
    printk("dump uninterrupted task.\n");
    do_each_thread(g, p) { /* 和上面的遍历类似 */
        if(p->__state & TASK_UNINTERRUPTIBLE) {
            printk("uninterrupted task, comm: %s, pid %d\n", p->comm, p->pid);
            // show_stack(p, NULL, ""); /* 可以取代下面两个语句 */
            nr_bt = StackTraceSaveTask(p, backtrace, BACKTRACE_DEPTH, 0); /* 保存栈 */ // 和下面一个语句一起可以取代上面一条语句
            stack_trace_print(backtrace, nr_bt, 0); /* 打印栈 */
        }
    } while_each_thread(g, p);
    rcu_read_unlock(); /* 为运行队列解锁 */
}
struct hrtimer timer; /* 创建一个计时器 */
static void check_load(void) { /* 主要的计时器触发后的程序 */
    static ktime_t last; /* 默认值是0 */
    u64 ms;
    int load = LOAD_INT(avenrun[0]);
    if(load < 4) /* 近1分钟内平均负载不超过4，没问题 */
        return;
    ms = ktime_to_ms(ktime_sub(ktime_get(), last)); /* 计算打印栈时间间隔 */
    if(ms < 20*1000) /* 打印栈的时间间隔小于20s,不打印 */
        return;
    last = ktime_get(); /* 获取当前时间 */
    print_all_task_stack(); /* 打印全部进程调用栈 */
}
static enum hrtimer_restart monitor_handler(struct hrtimer *hrtimer) { /* 计时器到期后调用的程序 */
    enum hrtimer_restart ret = HRTIMER_RESTART;
    check_load();
    hrtimer_forward_now(hrtimer, ms_to_ktime(10)); /* 延期10ms后到期 */
    return ret;
}
static void start_timer(void) {
    hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_PINNED); /* 初始化计时器为绑定cpu的自开机以来的恒定时钟 */
    timer.function = monitor_handler; /* 设定回调函数 */
    hrtimer_start_range_ns(&timer, ms_to_ktime(10), 0, HRTIMER_MODE_REL_PINNED); /* 启动计时器并设定计时模式为绑定cpu的相对时间，计时10ms，松弛范围为0 */
}
static int load_monitor_init(void) { /* 模块初始化 */
    // ShowStack = find_kallsyms_lookup_name("show_stack"); /* 使用show_stack时将此三行取消注释 */
    // if(!ShowStack)
    //     return -EINVAL;
    StackTraceSaveTask = find_kallsyms_lookup_name("stack_trace_save_tsk"); /* 使用stack_trace_save_tsk时将此三行取消注释 */
    if(!StackTraceSaveTask)
        return -EINVAL;
    start_timer();
    printk("load-monitor loaded.\n");
    return 0;
}
static void load_monitor_exit(void) { /* 模块退出 */
    hrtimer_cancel(&timer); /* 取消计时器 */
    printk("load-monitor unloaded.\n");
}
module_init(load_monitor_init);
module_exit(load_monitor_exit);
MODULE_DESCRIPTION("load monitor module");
MODULE_AUTHOR("Baoyou Xie <baoyou.xie@gmail.com>");
MODULE_LICENSE("GPL");

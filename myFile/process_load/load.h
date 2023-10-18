/** 
 * Boyou Xie's load monitor module
 *
 * Copyright (C) 2018 Baoyou Xie.
 *
 * Author: Baoyou Xie <baoyou.xie@gmail.com>
 *
 * License terms: GNU General Public License (GPL) version 2
 */

#include <linux/kprobes.h> /* for *kprobe* */
/* 调用kprobe找到kallsyms_lookup_name的地址位置 */
int noop_pre(struct kprobe *p, struct pt_regs *regs) { return 0; } /* 定义探针前置程序 */
void *find_kallsyms_lookup_name(char *sym) { /* 通过kprobe找到函数入口地址 */
    int ret;
    void *p; /* 用于保存要返回的函数入口地址 */
    struct kprobe kp = { /* 初始化探针 */
        .symbol_name = sym, /* 设置要跟踪的内核函数名 */
        .pre_handler = noop_pre /* 放置前置程序 */
    };
    if ((ret = register_kprobe(&kp)) < 0) { /* 探针注册失败就报告错误信息并返回空指针 */
        printk(KERN_INFO "register_kprobe failed, error\n", ret);
        return NULL;
    }
    /* 保存探针跟踪地址,即函数入口;输出注册成功信息,注销探针,返回地址 */
    p = kp.addr;
    printk(KERN_INFO "%s addr: %lx\n", sym, (unsigned long)p);
    unregister_kprobe(&kp);
    return p;
}
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Fork一个新的进程
    child_pid = fork();

    if (child_pid == 0) {
        // 这是子进程
        printf("子进程: PID=%d\n", getpid());

        // 使用exec调用执行一个新的程序
        execlp("/bin/ls", "ls", NULL);

        // 如果exec失败，会继续执行以下代码
        perror("exec");
        return 1;
    } else if (child_pid > 0) {
        // 这是父进程
        printf("父进程: PID=%d, 子进程的PID=%d\n", getpid(), child_pid);

        // 等待子进程结束
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("子进程正常退出，退出码：%d\n", WEXITSTATUS(status));
        }
    } else {
        perror("fork");
        return 1;
    }

    // 父进程继续执行
    printf("父进程继续执行\n");

    // 等待一段时间
    sleep(2);

    // 退出进程
    exit(0);

    // 这里的代码不会被执行
    printf("这段代码不会被执行\n");
}

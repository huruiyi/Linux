#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*
    A 、 没有抢到cup的进程都没有执行权
    B 、 挂起态的进程不可以可以直接切换到运行态
    C 、 运行态和就绪态之间可以相互转换
    D 、 终止态和其他状态之间的转换是不可逆的
*/

/*
    A 、 该函数有两个返回值，分别由父子进程返回
    B 、 父子进程的执行顺序是随机的
    C 、 子进程从代码段的fork的位置开始执行
    D 、 如果返回值pid=0，那么该进程为子进程

fork()
Return:
    成功：父进程返回子进程的进程Id，子进程返回0
    失败：父进程返回-1（子进程没有被创建，子进程没有返回信息）
    Error:
On success, the PID of the child process is returned in the parent, and 0 is
returned in the child.
On failure, -1 is returned in the parent,no child process is created, and errno
is set appropriately.
pid_t getpid(void) ::获取进程Id
pid_t getppid(void)::获取父进程Id
  PPID    PID   PGID    SID TTY       TPGID STAT   UID   TIME COMMAND
  2730   4645   4645   2730 pts/19     4645 S+    1000   0:00 ./a.out
  4645   4646   4645   2730 pts/19     4645 S+    1000   0:00 ./a.out

*/
int main() {
  pid_t pid = fork();

  if (pid > 0) {
    printf("父进程返回Id=%04d,pid=%04d,ppid=%04d----parent\n", pid, getpid(),
           getppid());
    sleep(1); //等待子进程结束
  } else if (pid == 0) {
    printf("子进程返回Id=%04d,pid=%04d,ppid=%04d----son\n", pid, getpid(),
           getppid());
  }
  sleep(30); // ps -ajx|grep 1_fork
  printf("end ....\n");
  return 0;
}
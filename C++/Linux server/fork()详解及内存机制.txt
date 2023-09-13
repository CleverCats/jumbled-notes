#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>      
#include<signal.h>
int main(int argc,char*const *argv)
{
    pid_t pid;
    /*fork()返回值:
    当成功执行fork()函数后接收收返回值时上父子进程都进行了返回值接收,且返回值不同
    子进程接收到的返回值为0,父进程接收到的返回值为*** 子进程的id ****;
    若fork()失败则返回值<0(一般默认系统能承受进程数为32767);*/

    //改变共享内存pid时会发生内存赋值,父子各拥有自己的pid
    pid=fork(); //进程数变化:1-2
    pid=fork(); //进程数变化:2-4

    /*fork内存机制:fork的速度非常快,fork产生的子进程并不复制原进程的内存空间,
     而是和原进程(父进程)共享一个内存空间,但是这个内存空间的特征是'写时复制',即当子进程将要对共享内存有修改动作
     此时内存就会复制一份给该进程单独使用,以免影响到整个进程的使用;*/
     if(pid<0)
     {
         printf("很遗憾,fork()失败...\n");
         exit(1);
     }
     else if(pid==0)
     {
         while(1)
         {
             sleep(2);
             printf("我是子进程 我的进程id=%d\n",getpid());
         }
     }
     else
     {
          while(1)
         {
          sleep(2);
          printf("我是父进程 我的进程id=%d我成功fork()了子进程,我的子进程id=%d\n",getpid(),pid);
         }
     }
     //每个实际用户I都有自己可容纳的最大进程数
     //printf("每个实际用户ID的最大进程数=%ld\n",syconf(_SC_CHILD,MAX));
     return 0;
     
}
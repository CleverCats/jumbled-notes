#include<stdio.h>
#include<unistd.h>
#include<signal.h> //有关信号头文件
int main(int argc,char *const *argv)
{
    pid_t pid;
   // signal(SIGHUP,SIG_IGN); //拦截SINGNALUP信号

     printf("%d\n",pid);
    pid=fork();
     /*程序从fork开始分支（称分支不准确）
        一路是主进程 pid>0(pid 是子进程ID)一路是子进程pid==0自此分成两个任务 
        其实fork的时候已经两个分支了，数据段被复制了一份，因此pid有两份       
         执行pid=fork()时，返回值赋给pid在两个进程中运行，       
        fork会返回给父进程的那个>0的值，告诉调用者新建进程的pid      
        子进程的fork返回值是0 */
    if(pid<0)
    {
        printf("fork fail\n");
    }
    else if(pid==0)
    {
          printf("fork success\n");
          printf("子进程开始执行\n");
          setsid();   
         /*新建一个新的session
         setsid();//创建新的session  （不可在sessionleader创建新session）
         setsid()调用成功后，返回新的会话的ID，
         调用setsid函数的进程成为新的会话的领头进程，
         并与其父进程的会话组和进程组脱离。
         由于会话对控制终端的独占性，进程同时与控制终端脱离。
         该新的进程也被称为孤儿进程*/
         //补充:该进程ppid为调用setsid()的进程,当次ppid被终止后,ppid变为init进程即ppid=1
	 //注意:不会创建新的进程只会创建一个新的会话,然后成功该会话的sessionleader,并且将调用setsid()的进程从终端脱离出来
            for(;;)
            {
                sleep(1);
                printf("子休息了1s\n");
            }
             printf("子进程结束\n");
            return 0;
    }
    else
    {
       printf("父进程开始执行\n");
       for(;;)
        {
            sleep(1);
            printf("父休息了1s\n");
        }
         printf("父进程结束\n");
    return 0;
    }
    
}
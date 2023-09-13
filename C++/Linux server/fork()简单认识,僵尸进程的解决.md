#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>      
#include<signal.h>
/*僵尸进程的产生:在类unix系统中,一个子进程结束了,但是它的父进程还在执行
并且这个父进程没有调用(wait/waitpid)函数来进行额外的处理
那么这个子进程就会变成僵尸进程(defunct).
僵尸进程:已经终止了,不在执行,但是依旧没有被内核丢弃掉,因为内核认为该进程的父进程还需后该子进程的一些信息*/
/*一个进程结束的时候，会关闭所有的文件描述符，释放所有的内存空间，但是他的PCB仍然存在，保存着子进程的一些状态信息，
如果进程正常退出，保存着正常退出的状态，如果非正常退出，那么保存着是哪个信号导致的该进程退出，
父进程可以通过wait和waitpid查看到这些信息，并且彻底清除*/
void sig_usr(int signo)
{
    int status;

    switch (signo)
    {
        case SIGUSR1:
        printf("进程id= %d 成功捕捉SIGUSR1信号\n",getpid());
        break;
        case SIGCHLD:
         printf("进程id= %d 成功捕捉SIGCHLD信号\n",getpid());
         //signal(SIGCHLD,SIG_DFL);
         pid_t pid = waitpid(-1,&status,WNOHANG);  //使用waitpid函数清除进程已死进程的残留信息
         /*参数一 pid_t pid:
                < -1 回收指定进程组内的任意子进程
                = -1 回收任意子进程
                = 0  回收和当前调用waitpid一个组的所有子进程
                > 0  回收指定ID的子进程
           参数二 int*
           指针如果参数status不是空指针，则子进程的终止信息通过这个参数传出，
           如果只是为了同步而不关心子进程的终止信息，可以将status参数指定为NULL
          
           参数三 option
            WNOHANG  若由pid指定的子进程未发生状态改变(没有结束)，则waitpid()不阻塞，立即返回0
            WUNTRACED	返回终止子进程信息和因信号停止的子进程信息
            WCONTINUED	返回收到SIGCONT信号而恢复执行的已停止子进程状态信息
            
        //*****参数WNOHANG表示无论子僵尸进程是否被终止,不可以阻塞在这里,会立即返回
        //返回值:子僵尸进程未被终止返回0,waitpid函数调用失败返回-1,成功终止子僵尸进程返会处理的的僵尸进程pid*****
                子进程并没有终止返回0（WNOHANG为参数三时）*/

         if(pid == 0) //子进程没结束返回0
             return;
         if(pid == -1) //返回-1表示waitpid调用出错
             return;
         //走到这里表示waitpid函数调用成功pid接收的返回值为终止进程的id
         printf("pid = %d\n",pid);
         return;
         break;
    }
}
int main(int argc,char *const *argv)
{
    pid_t pid;

    if(signal(SIGUSR1,sig_usr)==SIG_ERR)  //拦截自定义信号
    {
         printf("无法捕捉SIGUSR1信号!\n");
         exit(1);
    }
    if(signal(SIGCHLD,sig_usr)==SIG_ERR) //拦截SIGCHLD信号
    /*不进行信号捕捉情况下当子进程被终止掉时,会发送一个SIGCHLDE信号给父进程,该信号默认下并不会调用waitpid(...)函数,只是通知父进程子进程状态改变
     导致残留信息未被清除,形成僵尸进程    补充:僵尸进程的父进程这时也被kill的话，僵尸进程也会消失(当然这不现实,实际中应该使用代码解决僵尸进程问题)*/
    {
         printf("无法捕捉SIGCHLD信号!\n");
         exit(1);
    }
    printf("执行fork()\n");
    pid = fork();
    for(;;)
    {
        sleep(1);
        printf("当前进程id= %d\n",getpid());
    }
    return 0;
}
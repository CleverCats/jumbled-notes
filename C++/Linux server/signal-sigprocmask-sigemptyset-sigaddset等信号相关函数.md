#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>      
#include<signal.h>
void sig_quit(int signo)
{
  printf("成功捕捉SIGQUIT信号!\n");
  if(signal(SIGQUIT,SIG_DFL)==SIG_ERR)  //SIG_DFL使信号默认处理(默认处理一般为终止进程)
  {
      printf("signal(SIGQUIT,SIG_DFL)设置SIGQUIT信号default处理方式失败!\n");
  }
  else
  {
      printf("signal(SIGQUIT,SIG_DFL)设置SIGQUIT信号default处理方式成功!!!\n");
  }
  
}
int main(int argc,char *const *argv)
{
   sigset_t newmask,oldmask;
   //商业代码证中不用signal函数而是使用sigaction函数取代signal函数
   if(signal(SIGQUIT,sig_quit)==SIG_ERR) //捕捉SIGQUIT信号,失败返回‘SIG_ERR’
   {    
       //这里当SIGQUIT信号屏蔽后便不会触发SIGQUIT信号,也就不会执行signal(SIGQUIT,sig_quit)函数
       printf("SIGQUIT信号捕捉失败!\n");
       exit(1);  //0表示正常退出  非0表示异常退出
   }
   
   sigemptyset(&newmask);  //默认将参数一信号集64位信号全置为0(表示信号空闲可接受)
   sigaddset(&newmask,SIGQUIT);//将参数一信号集中的SIGQUIT信号位置为1占用状态
   //sigprocmask()设置进程所对应的信号集  进程的信号掩码(signal mask)
   //sigprocmask函数实际就是将某个信号集与当前进程绑定
   if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)//执行成功则返回0,失败返回-1
     /*参数一为SIG_BLOCK表示将当前信号集状态与参数二信号集求并集作为当前进程信号集状态
   (默认情况下信号集全为0,这里也就相当于将参数二作为新的进程信号集)
   参数三作用为存储旧的信号集(未调用该函数之前的信号集),便于后续恢复进程信号集的需求*/
   {
       printf("sigprocmask(SIG_BLOCK,&newmask,&oldmask)失败!\n");
       exit(1);  //失败退出
   }
   printf("sleep 10s begin\n");
   sleep(10); //此期间SIGQUIT处于占用状态
   printf("sleep 10s end\n");
   //sigismember返回oldmask信号集中SIGQUIT的信号占用状态0 or 1
   if(sigismember(&newmask,SIGQUIT))
   {
       printf("SIGQUIT信号屏蔽中!\n");
   }
   else
   {
        printf("SIGQUIT信号未被屏蔽中!!!\n");
   }
   //检测SIGHUP信号是否被屏蔽
   if(sigismember(&newmask,SIGHUP))
   {
       printf("SIGHUP信号屏蔽中!\n");
   }
   else
   {
        printf("SIGHUP信号未被屏蔽!!!\n");
   }
   //恢复原始信号集
   if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
   //此时当执行完sigprocmask(SIG_SETMASK,&oldmask,NULL)后SIGQUIT信号以恢复未屏蔽状态
   //如果在屏蔽状态时有请求的SIQQUIT信号,会将信号合并为一个SIGQUIT信号并阻塞等待处理该信号理该信号 
   //恢复未屏蔽状态后立即处理该信号
   {
       //参数一SIG_SETMASK表示将当前进程信号集设置为oldmask成功返回0
       printf("sigprocmask(SIG_SETMASK,&oldmask,NULL)失败!\n");
       exit(1); //失败退出
   }
   printf("sigprocmask(SIG_SETMASK,&oldmask,NULL) 成功\n");
   if(sigismember(&oldmask,SIGQUIT))
   {
       printf("SIGQUIT信号屏蔽中!\n");
   }
   else
   {
       printf("SIGHUP信号未被屏蔽 可以接受SIGQUIT信号!!!\n");
   }
   printf("sleep 10s begin\n");
   int current_t=sleep(10); //此期间SIGQUIT处于占用状态
   //sleep函数可以被中断,当睡眠中接受到了信号,将会终止sleep并且返回当前未sleep的时间
   if(current_t>0)
   {
       printf("sleep中断 剩余t=%ds\n",current_t);
   }
   printf("sleep end\n");
   printf("再见!\n");
   return 0;
}
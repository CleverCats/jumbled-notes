#include<stdio.h>
#include<unistd.h>
#include<signal.h> //�й��ź�ͷ�ļ�
int main(int argc,char *const *argv)
{
    pid_t pid;
   // signal(SIGHUP,SIG_IGN); //����SINGNALUP�ź�

     printf("%d\n",pid);
    pid=fork();
     /*�����fork��ʼ��֧���Ʒ�֧��׼ȷ��
        һ·�������� pid>0(pid ���ӽ���ID)һ·���ӽ���pid==0�Դ˷ֳ��������� 
        ��ʵfork��ʱ���Ѿ�������֧�ˣ����ݶα�������һ�ݣ����pid������       
         ִ��pid=fork()ʱ������ֵ����pid���������������У�       
        fork�᷵�ظ������̵��Ǹ�>0��ֵ�����ߵ������½����̵�pid      
        �ӽ��̵�fork����ֵ��0 */
    if(pid<0)
    {
        printf("fork fail\n");
    }
    else if(pid==0)
    {
          printf("fork success\n");
          printf("�ӽ��̿�ʼִ��\n");
          setsid();   
         /*�½�һ���µ�session
         setsid();//�����µ�session  ��������sessionleader������session��
         setsid()���óɹ��󣬷����µĻỰ��ID��
         ����setsid�����Ľ��̳�Ϊ�µĻỰ����ͷ���̣�
         �����丸���̵ĻỰ��ͽ��������롣
         ���ڻỰ�Կ����ն˵Ķ�ռ�ԣ�����ͬʱ������ն����롣
         ���µĽ���Ҳ����Ϊ�¶�����*/
         //����:�ý���ppidΪ����setsid()�Ľ���,����ppid����ֹ��,ppid��Ϊinit���̼�ppid=1
	 //ע��:���ᴴ���µĽ���ֻ�ᴴ��һ���µĻỰ,Ȼ��ɹ��ûỰ��sessionleader,���ҽ�����setsid()�Ľ��̴��ն��������
            for(;;)
            {
                sleep(1);
                printf("����Ϣ��1s\n");
            }
             printf("�ӽ��̽���\n");
            return 0;
    }
    else
    {
       printf("�����̿�ʼִ��\n");
       for(;;)
        {
            sleep(1);
            printf("����Ϣ��1s\n");
        }
         printf("�����̽���\n");
    return 0;
    }
    
}
-:������ĺ����"-"��ʾ���������ѡ��;
sudo su:����rootȨ��
�ſ��ļ�Ȩ��: chmod 777 filepath
�鿴���м���80�˿ڵĽ���:   lsof -i:80  ����:netstat����ֻ�ܲ鿴�˿ڴ���ʲô״̬,���޷���ʾ��Щ�������ڼ���

sudo ps -eo pid,ppid,sid,tty,pgrp,comm,stat,cmd | grep -E 'bash|PID|nginx'
��:sid:session id������id�� tty:�ն�  pgrp:������id  ע:һ�������������һ��������(grep) ,һ���������������һ������(session)
   session leader ��pid = session id (sid)
   ps����������ʾ��ǰ���� (process) ��״̬;-:������ĺ����"-"��ʾ���������ѡ��; -e ��ʾ���н��̣� -o ָ����ʽ(-fȫ��ʽ);
   |:�ܵ����� ��command 1 | command 2 ���Ĺ����ǰѵ�һ������command 1ִ�еĽ����Ϊcommand 2�����봫��command 2
    stat:����״̬
    ����:ls -l | more �������г���ǰĿ¼�е��κ��ĵ�����������͸�more������Ϊ���룬more�����ҳ��ʾ�ļ��б�(���������ָ�Ҫɸѡ������)
   -E �� --extended-regexp : ����ʽΪ�����������ʽ��ʹ�á�
������ʽ:
������ʽ���ֳƹ�����ʽ��(Ӣ��:Regular Expression���ڴ����г���дΪregex��regexp��RE)��
�������ѧ��һ�����������ʽͨ���������������滻��Щ����ĳ��ģʽ(����)���ı���
Ŀ��:
����һ��������ʽ����һ���ַ��������ǿ��Դﵽ���µ�Ŀ��:
1. �������ַ����Ƿ����������ʽ�Ĺ����߼�(����"ƥ��"):
2. ����ͨ��������ʽ�����ַ����л�ȡ������Ҫ���ض����֡�


signal(SIGHUP,SIG_IGN); ����SIGNALUP�źź���
�ն��˳����ն˻ᷢ��SIGHYO�źŸ�sessionleader����, �����������  sessionleader���SIGHUP�źŷ���session��������н���
�յ�SIGHUP�źŵĽ��̵�Ĭ�϶������˳�����
����:�൱��nohup������������,ϵͳ�����ڽ������,���ǻ�����һ��nohup.out�ļ�,���е�printf��ӡ�����ļ���
��bash���̱��ɵ�,�˽���Ҳ�����SIGNALUP�ź�,��Ϊ�¶����̣��������ڽ���init����)

setsid����:����һ���¶�����,�������κ��ն�,ppid=1; �� setsid ./nginx 

./nginx &��̨����
����:��̨�����¿���ִ������������,ǰ̨�򲻿���

fg�ָ�ǰ̨����

sudo find / -name "signal.h"| xargs grep -in "SIGHUP"
��:find:����;/ -name �Ӹ�Ŀ¼��ʼ,�������ļ����ҵ���Ϊsignal.h���ļ�;
   xargs:�޶�ʹ��signal.h����������;grep�ı���������;i:���Դ�Сд;n:��ʾ���������к�;"SIGHIP"��Ҫ�����Ĺؼ���

sudo strace -e trace=signal -p 1184
strace����:������
 -e strace=signal  ����������ϵͳ�ź��йص�ϵͳ����;
��:strace�������� ,-e���н��� ,trace�ۼ�=signal�ź�,-p 1184 ���Ƹ��� pid=1184�Ľ���

Kill����:��ָ�����̷���һ������,Ĭ���������Ϊ SIGTERM����ֹ�������
Kill -���� ����id ; �ܷ���һ��������ֶ�Ӧ���ź� -1Ϊ SIGHUP�ź�
ɱ��һ���������е����н���:sudo kill -9 -id(grep)


sudo ./nginx -s reload
��:ʵ�������������ͬ��kill -SIGHUP pid;
����:��Ŀ��worker���̷���һ��SIGHUP�źŸ��ϵ�mask����,�ý���Ϊ�ػ�����,SIGHUP�ź����ﲻִ��Ĭ�Ϲ���,ֻ�ǽ���һ��֪ͨ����
��Ϊ������Ϣʹ��,���ձ�ʾnginx�������ļ������ĸı�,��Ҫ��д���������ļ�.����Ч

Valgrind -h     Valgrind --version       ��: -h�����ĵ�  --version�鿴�汾�� 
��:Valgrind ��������ԱѰ�ҳ���bug�͸Ľ�����Ĺ��߼�,�ó������ڴ�Ĺ�������,��������Ҫ����Memcheck(�ڴ���)����  

��ʽ:valgrind --tool=memcheck   һЩ����   ��ִ���ļ���
				--tool=memcheck����:ʹ��valgring���߼��е�memcheck����
				--leak-check=full  :ָ������ȫ(full)����ڴ�й©
				--show-reachable=yes :����ʾ�ڴ�й©�ص�
				--trace-children = yes :�Ƿ�����ӽ���
				--log=file=log.txt  :��������Ϣ�����log.txt��,���������Ļ
��������: valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./ngx_envmove

�ڴ�й©�鿴��: allocs - free == 1;  definitely lost: 100 bytes in 1 blocks;  LEAK SUMMARY;
���� 0x400976: ngx_intit_setproctitle() (in /code/mytemptest/ngx_envmove)


����ʱ��:1.  tzselect + 4 +9 +1   (����:�������������ص�ԭ����ʱ��)��ʵֻ��������һ����ʱʱ���ļ�,����Ҫ������ļ����ǵ�Դ�ļ�
	 2.  sudo cp /usr/share/zoneinfo/Asia/Shanghai  /etc/localtime  (�����Ը���ʱ��Դ�ļ�)

telnet����:һ���������з�ʽ���еĿͻ���TCPͨѶ����,�������ӵ���������,���������˷�������,Ҳ���Խ��մӷ������˷��͹���������
           �ù��߿��Է���Ĳ��Է���˵�ĳ��TCP�˿��Ƿ�ͨ,�Ƿ��ܹ�������������,linux��window�����Ե���
ʹ������:telnet + IP + �˿�    ����:telnet 192.168.8.126 9000

netstat����:��ʾ���������Ϣ
-a:��ʾ����ѡ��
-n:����ʾ�����ֵ�����ȫ�� ��ʾ������
-p:��ʾ�����Ӧ�ĳ�����
һ������:netstat -anp | grep -E 'State|9000'
��-ִ�н��:
------------------------------------------------------------------------------------------------------------
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 0.0.0.0:9000            0.0.0.0:*               LISTEN      -               
tcp        0      0 192.168.8.126:9000      192.168.8.126:49296     TIME_WAIT   -               
------------------------------------------------------------------------------------------------------------
Local Address��������IP/PORT�� 0 0.0.0.0:9000:��������IP��9000�˿ڡ�0.0.0.0��ʾ��������IP��
Foreign Address���ͻ���IP/PORT��  192.168.8.126:49296:���ӵ�����9000�˿ڵ�IP/PORT
State��״̬��:LISTEN ����   TIME_WAIT�ͻ����ѶϿ�����ʱ�������ر��������Ļ�bind��ʧ�ܡ�

su����:
rootȨ��: su + �س� + root���롾sudo passwd��
sudo passwd����root����
Ȼ����������뵱ǰ�û�����
�������������root�û�����Ϳ�����
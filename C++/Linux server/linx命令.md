-:在命令的后面加"-"表示后面跟的是选项;
sudo su:进入root权限
放开文件权限: chmod 777 filepath
查看所有监听80端口的进程:   lsof -i:80  补充:netstat命令只能查看端口处于什么状态,而无法显示哪些进程正在监听

sudo ps -eo pid,ppid,sid,tty,pgrp,comm,stat,cmd | grep -E 'bash|PID|nginx'
释:sid:session id（会议id） tty:终端  pgrp:进程组id  注:一个或多个进程组成一个进程组(grep) ,一个或多个进程组组成一个会议(session)
   session leader 的pid = session id (sid)
   ps命令用于显示当前进程 (process) 的状态;-:在命令的后面加"-"表示后面跟的是选项; -e 显示所有进程； -o 指定格式(-f全格式);
   |:管道符号 ，command 1 | command 2 他的功能是把第一个命令command 1执行的结果作为command 2的输入传给command 2
    stat:进程状态
    例如:ls -l | more 该命令列出当前目录中的任何文档，并把输出送给more命令作为输入，more命令分页显示文件列表。(即竖杠来分隔要筛选的条件)
   -E 或 --extended-regexp : 将样式为延伸的正则表达式来使用。
正则表达式:
正则表达式，又称规则表达式。(英语:Regular Expression，在代码中常简写为regex、regexp或RE)，
计算机科学的一个概念。正则表达式通常被用来检索、替换那些符合某个模式(规则)的文本。
目的:
给定一个正则表达式和另一个字符串，我们可以达到如下的目的:
1. 给定的字符串是否符合正则表达式的过滤逻辑(称作"匹配"):
2. 可以通过正则表达式，从字符串中获取我们想要的特定部分。


signal(SIGHUP,SIG_IGN); 拦截SIGNALUP信号函数
终端退出后终端会发生SIGHYO信号给sessionleader进程, 如果不做拦截  sessionleader会把SIGHUP信号发给session里面的所有进程
收到SIGHUP信号的进程的默认动作是退出程序
补充:相当于nohup命令启动程序,系统不会在界面输出,而是会生成一个nohup.out文件,所有的printf打印到该文件中
若bash进程被干掉,此进程也会忽略SIGNALUP信号,成为孤儿进程，被老祖宗进程init收留)

setsid命令:启动一个孤儿进程,不属于任何终端,ppid=1; 例 setsid ./nginx 

./nginx &后台运行
补充:后台运行下可以执行命令行命令,前台则不可以

fg恢复前台运行

sudo find / -name "signal.h"| xargs grep -in "SIGHUP"
释:find:查找;/ -name 从根目录开始,在所有文件中找到名为signal.h的文件;
   xargs:限定使在signal.h内容中搜索;grep文本搜索命令;i:忽略大小写;n:显示搜索到的行号;"SIGHIP"需要搜索的关键字

sudo strace -e trace=signal -p 1184
strace工具:跟踪器
 -e strace=signal  跟踪所有与系统信号有关的系统调用;
释:strace跟踪命令 ,-e所有进程 ,trace痕迹=signal信号,-p 1184 限制跟踪 pid=1184的进程

Kill命令:向指定进程发送一个命令,默认命令参数为 SIGTERM（终止进程命令）
Kill -数字 进程id ; 能发出一个与该数字对应的信号 -1为 SIGHUP信号
杀掉一个进程组中的所有进程:sudo kill -9 -id(grep)


sudo ./nginx -s reload
释:实际上这条命令等同于kill -SIGHUP pid;
作用:向目标worker进程发送一个SIGHUP信号给老的mask进程,该进程为守护进程,SIGHUP信号这里不执行默认功能,只是进行一个通知作用
作为传递信息使用,接收表示nginx的配置文件发生的改变,需要重写加载配置文件.并生效

Valgrind -h     Valgrind --version       释: -h帮助文档  --version查看版本号 
释:Valgrind 帮助程序员寻找程序bug和改进程序的工具集,擅长发现内存的管理问题,其中最重要的是Memcheck(内存检查)工具  

格式:valgrind --tool=memcheck   一些开关   可执行文件名
				--tool=memcheck　　:使用valgring工具集中的memcheck工具
				--leak-check=full  :指的是完全(full)检测内存泄漏
				--show-reachable=yes :是显示内存泄漏地点
				--trace-children = yes :是否跟入子进程
				--log=file=log.txt  :将调试信息输出到log.txt中,不输出到屏幕
最终命令: valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./ngx_envmove

内存泄漏查看点: allocs - free == 1;  definitely lost: 100 bytes in 1 blocks;  LEAK SUMMARY;
例如 0x400976: ngx_intit_setproctitle() (in /code/mytemptest/ngx_envmove)


设置时区:1.  tzselect + 4 +9 +1   (问题:设置完后重启会回到原来的时区)其实只是生成了一个临时时区文件,还需要将这个文件覆盖掉源文件
	 2.  sudo cp /usr/share/zoneinfo/Asia/Shanghai  /etc/localtime  (拷贝以覆盖时区源文件)

telnet工具:一款以命令行方式运行的客户端TCP通讯工具,可以连接到服务器端,往服务器端发送数据,也可以接收从服务器端发送过来的数据
           该工具可以方便的测试服务端的某个TCP端口是否通,是否能够正常接收数据,linux与window都可以调用
使用命令:telnet + IP + 端口    例如:telnet 192.168.8.126 9000

netstat命令:显示网络相关信息
-a:显示所有选项
-n:能显示成数字的内容全部 显示成数字
-p:显示段落对应的程序名
一般命令:netstat -anp | grep -E 'State|9000'
例-执行结果:
------------------------------------------------------------------------------------------------------------
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 0.0.0.0:9000            0.0.0.0:*               LISTEN      -               
tcp        0      0 192.168.8.126:9000      192.168.8.126:49296     TIME_WAIT   -               
------------------------------------------------------------------------------------------------------------
Local Address【服务器IP/PORT】 0 0.0.0.0:9000:本地所有IP的9000端口【0.0.0.0表示本地所有IP】
Foreign Address【客户端IP/PORT】  192.168.8.126:49296:连接到本地9000端口的IP/PORT
State【状态】:LISTEN 监听   TIME_WAIT客户端已断开【此时服务器关闭在重启的话bind会失败】

su命令:
root权限: su + 回车 + root密码【sudo passwd】
sudo passwd设置root密码
然后会让你输入当前用户密码
输入完后再输入root用户密码就可以了
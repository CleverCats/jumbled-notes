前提: 1.gcc 编译要使用-g选项【已经在makefile中实现】 
        2.使用su命令在root权限下运行
        3.gdb缺省调试的是主进程(parent),7.0以上版本支持调试子进程(child)
查看gdb版本: gdb -v【命令行模式下】

【gdb命令】
首先进入gdb环境: gdb 可执行文件
#调试进程相关
查看当前调试进程类型: show follow-fork-mod    【statu:parent/child】 parent:调试父进程 child:调试子进程
设置当前调试进程类型:set follow-fork-mod parent（缺省状态）或 set follow-fork-mod child
#调试方式相关
查看当前调试方式: show detach-on-fork 【statu:on/off】 【子进程或父进程的选择由set follow-fork-mod 选项决定】
on:只调试子进程或者父进程【调试一个进程时另一个进程正常运行】
off:父进程或者子进程都可以调试【调试有一个进程时另外一个进程被暂停】
设置调试方式:set detach-on-fork on(缺省状态) 或者 set detach-on-fork off

/*总结*/
follow-fork-mode  	    detach-on-fork
	parent		on				只调试父进程，子进程正常运行
	child	   	on			  	只调试子进程，父进程正常运行
	parent		off			同时调试两个进程，子进程暂停在fork位置
	child		off			同时调试两个进程，父进程暂停在fork位置

设置断点: b 函数文件路径 文件名:行号
例如b logic/ngx_c_process_func.cxx::139  【在logic文件目录下的ngx_c_process_func.cxx文件的139行设置断点】‘
开始运行:run【运行到断点处停止】 ps:此时可以用gdb的print语句调试手段打印一些变量值
继续运行:c    【从断点处继续往下运行】

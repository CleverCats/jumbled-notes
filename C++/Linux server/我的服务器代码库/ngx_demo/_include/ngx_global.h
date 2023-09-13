#ifndef __NGX_GBLDEF_H__
#define __NGX_GBLDEF_H__

#include<signal.h>
#include<stdio.h>
#include<stddef.h>
typedef struct
{
	int  log_level;			//日志级别 或者日志类型，ngx_macro.h里分0-8共9个级别
	int  fd;				//日志文件描述符

}ngx_log_t;

//数据变量类型相关
typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;
typedef int				pid_t;


//外部全局量声明
extern size_t        g_argvneedmem;
extern size_t        g_envneedmem;
extern int           g_os_argc;
extern char          **g_os_argv;
extern char          *gp_envmem;
extern ngx_log_t	 ngx_log;
extern sig_atomic_t  ngx_reap; 

//进程相关
extern pid_t         ngx_pid;
extern pid_t	 	 ngx_parent;
extern int 			 ngx_process_type;

//结构定义,用来储存有效配置信息
typedef struct _CConfItem
{
	char ItemName[50];      //配置信息名
	char ItemContent[500];  //配置信息数据
}CConfItem, *LPCConfItem;


#endif
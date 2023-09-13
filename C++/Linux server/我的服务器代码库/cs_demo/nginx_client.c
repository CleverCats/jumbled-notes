#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//需要链接的服务器端口【服务器必须在这个端口listen】
#define SERV_PORT 9000
//client demo
int main(int argc, char* const * argv)
{
    //客户端套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));

    //设置需要连接到的服务器信息
    serv_addr.sin_family = AF_INET;        //遵循协议族为IPV4
    serv_addr.sin_port = htons(SERV_PORT); //设置需要请求连接的端口号SERV_PORT

    //这里做演示,使用固定的服务器地址
    //inet_pton:IP地址转换函数，可以在将IP地址在"点分十进制"和"二进制整数"之间转换
    //函数转换字符串到网络地址，第一个参数af是地址族，第二个参数是来源地址，第三个参数接收转换后的数据。
    if(inet_pton(AF_INET,"192.168.8.126",&serv_addr.sin_addr) <= 0)//转换成功返回>0
    {
        printf("调用inet_pton()失败,退出!\n");
        exit(1);
    }

    //走到这里serrv_addr已经记录至少三个信息,用于定向连接请求
    //【C/S遵循的协议族IPV4: sin_family = AF_INET】
    //【服务器IP地址: 192.168.1.126】
    //【需要连接的服务器端口号9000: SERV_PORT】

    //在客户端中sockfd始终是客户端的套接字,客户端使用该套接字标【套接字包含IP + 端口】标识自身信息
    //然后通过serv_addr【包含服务器IP/PORT等信息】进行C/S连接请求
    if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)//请求连接
    {
        printf("调用connect()失败,退出!\n");
        exit(1);
    }
    //连接成功,C/S通道建立
    int n;
    char recvline[1000 + 1];
    while((n = read(sockfd,recvline,1000)) > 0 )//服务端关闭连接客户端的socket后会导致客户端read返回失败,while不成立
    {
        recvline[n] = 0;
        printf("Client收到的内容为: %s\n",recvline);
    }
    //关闭套接字
    close(sockfd);
    return 0;
}

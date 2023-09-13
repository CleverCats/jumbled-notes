#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERV_PORT 9000 //本服务器要监听的端口,1024一下的端口很多是周知端口,一般采用1024以后的端口

//服务端demo
int main(int argc, char* const *argv)
{
    //服务器的socket套接字【文件描述符】【套接字包含IP+端口】
    int listenfd = socket(AF_INET,SOCK_STREAM,0); //SOCK_STREAM:使用TCP协议
    
    struct sockaddr_in serv_addr;   //服务器地址结构体
    memset(&serv_addr,0,sizeof(serv_addr));

    //设置本服务器要监听的地址和端口,使客户端能够连接到该地址并通过端口发送数据
    serv_addr.sin_family = AF_INET;  //选择协议族为IPV4
    serv_addr.sin_port = htons(SERV_PORT);//绑定自定义的端口号,客户端与服务器程序通讯时,就通过此端口传输数据
    //监听本地所以IP地址;INADDR_ANY表示一个服务器上的所有网卡(一个服务器可能不止一个网卡,也就是不止一个IP地址)这里不管服务器有几个IP,全部都进行端口绑定
    
    //绑定服务器地址结构体(将服务器地址和端口绑定在一起)
    bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    //开始监听listenfd地址上的SERV_PORT端口
    listen(listenfd,32); //参数二表示服务器可以积压未处理完的请求个数,客户端来了一个未连入的请求后,请求数+1,连入请求完成,c/s正常通讯后,请求数-1

    int connfd;
    const char *pcontent = "I sent sth to client";//指向常量字符串区的指针
    
    for(;;)
    {
        //阻塞在这里,等待客户端的链接请求,客户端连接后,该函数走下去
        //此函数的返回值是一个新的套接字【客户端套接字,在客户端请求连接时带来的信息】,后续服务使用该套接字与客户端进行通讯,原套接字继续用于监听端口
        connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
        //成功建立C/S通道
        char readbuf[1000+1] = {0};
        read(connfd,readbuf,1000);
        printf("read:%s\n",readbuf);
        //通过客户端套接字发送数据
        write(connfd,pcontent,strlen(pcontent));
        
        //只给客户端发送一条数据,然后直接关闭客户端套接字
        close(connfd);
    }
    //关闭服务端套接字
    close(listenfd);
    return 0;
}
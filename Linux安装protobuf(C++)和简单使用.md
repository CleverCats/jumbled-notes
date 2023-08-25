# # Linux安装protobuf(C++)和简单使用

## # 下载[protobuf](https://link.csdn.net/?target=https%3A%2F%2Fgithub.com%2Fprotocolbuffers%2Fprotobuf%2Freleases)

> 第一步：下载 

```第一步：下载
wget https://github.com/protocolbuffers/protobuf/releases/download/v3.19.4/protobuf-all-3.19.4.tar.gzwget https://github.com/protocolbuffers/protobuf/releases/download/v3.19.4/protobuf-all-3.19.4.tar.gz
```

> 第二步：安装

```第二步：安装
tar zxvf protobuf-all-3.19.4.tar.gz        //解压
cd protobuf-3.19.4/                        //进入解压目录
//检查并安装以下环境，本次使用centos7环境，Ubuntu使用apt-get安装。
sudo apt install autoconf 
sudo apt install automake 
sudo apt install libtool
//以上安装成功后执行下面
./autogen.sh
//生成编译配置文件成功,运行配置脚本
./configure
make                  //要编译很久
make check            //测试
make install        //安装
```

```第三步：安装成功
protoc --version    //查看版本
```

> 简单使用protobuf
> 
> 第一步 创建.proto文件

```cpp
完成序列化和反序列化，本实验目录在：/home/admin/Learn_MyProtobuf
创建一个.proto文件：myAccount.proto，内容如下

myAccount.proto文件:

syntax = "proto3";
package IM;
message Account {
    //账号
    uint64 ID = 1;
    //名字
    string name = 2;
    //密码
    string password = 3;
}

message User {
    Account user = 1;
}
```

第二部 编译.proto文件

生成C++语言的定义及操作文件myAccount.pb.h, myAccount.pb.cc

```编译.proto文件，生成C++语言的定义及操作文件
protoc --cpp_out=. ./msg.proto
编写程序main.cpp
```

> 编写程序main.cpp

```cpp
#include <iostream>
#include <fstream>
#include "myAccount.pb.h"

using namespace std;

int main(int argc, char** argv)
{
    IM::Account account1;
    account1.set_id(1);
    account1.set_name("ysl");
    account1.set_password("123456");

    string serializeToStr;
    account1.SerializeToString(&serializeToStr);
    cout <<"序列化后的字节："<< serializeToStr << endl;


    IM::Account account2;
    if(!account2.ParseFromString(serializeToStr))
    {
        cerr << "failed to parse student." << endl;
        return -1;
    }
    cout << "反序列化：" << endl;
    cout << account2.id() << endl;
    cout << account2.name() << endl;
    cout << account2.password() << endl;

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
```

> 对main.cpp进行编译

```
执行动态链接库管理命令，让可共享的动态链接库被找到
sudo ldconfig

protoc --cpp_out=<output_directory> <proto_file>
<output_directory> 是生成的C++代码的输出目录
<proto_file> 是要编译的.proto文件的路径
```

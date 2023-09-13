/*1 #define Debug  条件编译
说明：

1、Debug可以看做是声明的一个变量，但此变量没有真正的值，存在时#if Debug结果为true，否则为false；

2、#define单独用没什么意义，一般是和#if或者Conditional特性结合使用；

3、#define必须定义在所有using命名空间前面；*/

#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<atomic>
#include<future>
#include<Windows.h>

// 条件编译
#define _WINDOWSJQ_  //存在时#if  _WINDOWSJQ_结果为true，否则为false；
using namespace std;
//一个程序里线程数量不应操作100-200

static int num=0;


//使WINDOWS下的临界区实现C++11中Lock_guard<mutex>Obj(m_mutex);的出作用域后锁的自动析构操作,不需要手动Leave
//这种类一般被称为ASII类 (Resource Acquistion is initializatipo) 资源获取即初始化
//指在构造中初始化.在析构中释放的类
class CWinLock
{
private:
	//临界区类型指针
	CRITICAL_SECTION*Win_Lock;
public:
	//构造函数实现临界区进入
	CWinLock(CRITICAL_SECTION*_Lock)
	{
		//初始化
		Win_Lock = _Lock;

		//进入临界区
		EnterCriticalSection(Win_Lock);
	}
	//析构函数实现临界区离开
	~CWinLock()
	{
		//离开临界区
		LeaveCriticalSection(Win_Lock);
	}
};
#ifdef _WINDOWSJQ_

//CRITICAL 临界  SECTION区域  Windows系统下类似与互斥量的东西

//实例化临界区对象
CRITICAL_SECTION my_wintex;  
#endif // _WINDOWSJQ_

void mythread()
{
#ifdef _WINDOWSJQ_         //相当于if(true/false) else   end if
	//进入临界区
	//注意:允许次Enter,但需要对应的多次Leave.C++11与其不同,C++11中只能使互斥量加锁一次,不允许连续lock
	//EnterCriticalSection(&my_wintex);
	//EnterCriticalSection(&my_wintex);

	//实现WINDOWS下自动锁的功能
	CWinLock wlock(&my_wintex);  
	for (int i = 0; i < 10000000; i++)
	{
		num++;
		cout << "num=" << num << endl;
	}
	//离开临界区
	//LeaveCriticalSection(&my_wintex);
	//LeaveCriticalSection(&my_wintex);
#else	
	cout << "未进入临界区" << endl;
#endif
}
int main()
{
#ifdef _WINDOWSJQ_
	InitializeCriticalSection(&my_wintex); //不同于mutex临界区对象使用前必须初始化 Initialize初始化 Critical临界区 Section区域
#endif
	std::thread thr1(mythread);
	std::thread thr2(mythread);
	thr1.join();
	thr2.join();
	system("PAUSE");
	return 0;
}
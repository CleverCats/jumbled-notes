#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<atomic>
//static int i = 0;
std::mutex mut;
std::atomic<int>i=0;
//原子操作 意:不可分割的操作,针对单个变量时使用
//作用:它是一个类模板,这个类模板可以封装一个类型的变量,这里我们封装了一个int类型的变量i,可以像int i一样去同样操作这个i;
//特点:这个i在被操作时,无法被打断也就是++i要么还未++要么已经++完,在++的中途线程是不会切换的
//优点:虽然只能操作单一变量,但效率不mutex互斥量高出数倍
//建议:遇到这种单变量的多线程操作,优先使用std::atomic而不是mutex;
//用途:一般用于多线程计算或者统计(累积发送了多少数据包，累积接收了多少数据包)保证不会出错
//陷阱:与普通变量类型相似,但也不完全支持不同变量进行的一些运算符
//支持++i,--i，i+=5 类似的操作符,但不支持 i=i+1;这种操作
void Count()
{
	
	for (int x = 0; x < 10000000; x++)
	{
		//mut.lock();  //1. 通过互斥量保证数据的完整执行
		++i;
		//mut.unlock();
	}
}
int main()
{
	//同时进行写,一个i++在系统中不止一步,可能在中途的某一步时线程切换,得到一个意想不到的值，结果不一定是20000000
	std::thread thr1(Count); 
	std::thread thr2(Count);
	thr1.join(); 
	thr2.join();
	std::cout << i << std::endl;
	system("PAUSE");
	return 0;
}

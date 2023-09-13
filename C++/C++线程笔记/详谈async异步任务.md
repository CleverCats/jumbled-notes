#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<atomic>
#include<future>
//一个程序里线程数量不应操作100-200
int mythread()
{
	std::cout << "线程被调用ID=" << std::this_thread::get_id() << std::endl;
	return 10;
}
int mian()
{
	//thread的调用代表一定会尝试创建一个线程,但当系统资源紧张时,线程的创建可能会失败,导致系统崩溃
	static int a;
	std::thread thr1(mythread);
	//使用异步创建一个异步任务,默认参数是launch::asybc|launch::deferred
	//由系统自动选择两者之一,如果*****系统资源不紧张采用启动方式1,如果紧张选择启动方式2*****
	//这代表系统不一定创建线程,采用launch::async代表立即自动创建一个线程,并执行
	//采用launch::deferred代表不创建线程,如果有future与其关联,在.get或者.wait时在当前get/wait所在线程调用函数入口
	//如果需要一定创建异步任务时创建线程那么使用std::async参数启动
	//****如果强制采用launch::async参数,如果系统资源紧张,那么系统创建失败,系统崩溃****
	//如果想判断是否采用deffered延迟调用的方式,需要使用std::futuru_status stus=result.wait_for(0s  等待0秒);来判断启动状态
	std::future<int>result = std::async(mythread); 
	system("PAUSE");
	return 0;
}
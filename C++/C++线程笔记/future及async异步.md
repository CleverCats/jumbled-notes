#include<iostream>
#include<string>
#include<thread>
#include<future>
//一个类模板 它实例化的对象    提供一个访问线程操作结果的机制  future 是将来的意思,代表不一定能马上拿到线程任务的信息,但会在将来的某个时刻拿到信息
int  MyThr1()
{
	std::cout << "我的线程开始了  线程ID=" << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds sleep(3000); 
	std::this_thread::sleep_for(sleep);  //模拟线程处理信息需要的时间
	std::cout << "我的线程结束了  线程ID=" << std::this_thread::get_id() << std::endl;
	return 2020;
}
int main()
{
/*启动异步任务线程的方式枚举值参值  launch(启动)  总结;默认效果,***默认启动方式***即默认下实际上为 std::async(std::launch::async|std::launch::defferred,线程入口函数);
launch::defferred可以延迟但是在主线程调用没有创建线程 /*

	/*若仅传入参数  std::launch::async(同步启动.创建线程)  在异步线程创建时同步调用，一定会创建出一个线程，如果系统资源紧张则会创建失败导致系统崩溃

	std::launch::defferred(延迟调用,未创建线程)  异步线程等待fature的Object.wait()或者Obeject.get()的执行时才启动任务,但其实是在***主线程***中执行调用,并没有创建子线程*****
如果使用 launch::defferred 但未调用get()或者wait()那么调用的线程(***其实是在主线程中,未创建新线程)函数不会被执行,***甚至没被创建出来***

如果使用(默认) std::launch::defferred | std::launch::async 的方式传入那么异步任务创建启动的方式由系统决定
如果系统资源不紧张采用(一般都是这个) std::launch::async 紧张采用std::launch::defferred */

	std::future<int>Ret = std::async(/*默认缺省launch::async|std::launch::defferred */  MyThr1);

	//async (异步)  表示自动创建一个线程,并且通过执行的入口开始执行;(future<int>Ret其实是将Ret与线程建立一些联系)

	std::cout << "主线程ID=" << std::this_thread::get_id() << std::endl;
	         //Ret为future模板生成的一个对象,它可以接收线程(这里即MyThr1函数)返回来的信息；
	        //但不一定立刻接受到,因为如果线程还在运行没有返回,那么将需要直到线程返回才会接收到返回值,但这条语句并不会堵塞线程的运行

	std::chrono::milliseconds sleep(200);
	std::this_thread::sleep_for(sleep);  //模拟线程处理信息需要的时间

	std::cout << "正在获取异步线程返回信息......" << std::endl;
	std::cout << "正在获取异步线程返回信息......" << std::endl;
	std::cout << "正在获取异步线程返回信息......" << std::endl;
	std::cout << "正在获取异步线程返回信息......" << std::endl;
	std::cout << "正在获取异步线程返回信息......" << std::endl;
	std::cout << "正在获取异步线程返回信息......" << std::endl;

	std::cout << "接收到异步线程返回的信息:" << Ret.get() << std::endl;   
	/******在此处调用 future对象.get()获取异步线程的返回值,如果线程还在运行没有返回,那么程序将会在此处堵塞,直到获取到信息*******/
	/*陷阱,get()函数只能调用一次,不能调用多次*/
	/*fature类模板对象还有一个 Object.wait()函数,等待线程关联线程的结束,相当于 join()函数*/
	system("PAUSE");
	//老师测试如果不用get主线程会在return 0;也会处等待异步线程任务的执行,不过我没有出现这种线程		
	return 0;

}

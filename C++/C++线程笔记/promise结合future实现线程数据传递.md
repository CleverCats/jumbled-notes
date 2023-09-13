#include<iostream>
#include<string>
#include<vector>
#include<future>   //使用packaged_task也必须包含的头文件
#include<mutex>
#include<thread>
using std::cout;
using std::endl;
void Thr1(std::promise<int>&tmmp, int n)
{
	cout << "线程1执行中" << "ID=" << std::this_thread::get_id() << endl;
	//进行一些计算
	n=n*n+100;
	//模拟运算时间
	std::chrono::milliseconds sleep(2000);
	std::this_thread::sleep_for(sleep);  

	//set值
	tmmp.set_value(n);
	//注意:set_value只能被调用一次

	cout << "线程1结束执行" << endl;
	return;
}
void Thr2(std::future<int>&tmpf)
{
	cout << "线程2执行中" << "ID=" << std::this_thread::get_id() << endl;
	//get出future对象储存的值为线程2所用

	//注意:get只能调用一次
	auto result = tmpf.get();  
	//auto result2 = tmpf.get();只能调用一次
	cout << "Vaule=" << result << endl;
	cout << "线程2结束执行" << endl;
	cout << "Object.setvalue Over" << result << endl;
	return;
}
int main()
{
	cout << "主线程正在执行中 " << "ID=" << std::this_thread::get_id() << endl;
	std::promise<int> pro;  //实例化一个接收整形值值promise的类模板参数

	//promise对象传入线程1，对pro进行setvalue
	std::thread thr(Thr1,std::ref(pro), 220);
	thr.join();

	//future对象也可以和promise对象绑定
	std::future<int>result = pro.get_future();
	/*std::future<int>result2 = pro.get_future();*/  //只能调用一次get.future
	//future对象传入线程2
	std::thread thr2(Thr2,std::ref(result));
	thr2.join();
	system("PAUSE");
	return 0;
}
							//总结:std::promise的作用是实现线程之间的通讯
//promise对象的Set.value只能调用一次                                 
//future对象所(=等于)绑定的的目标对象后,目标对象所具有的Get.future也只能调用一次  
//future的Object.get()也只能调用一次             *****因为get相当于一个移动语义,执行get后里面已经指向空了***
/*事实上std::promise::set_xxx函数会改变std::promise的状态为ready，再次调用时发现状态已要是reday了，则抛出异常。*/

/*一个std::promise实例只能与一个std::future关联共享状态，当在同一个std::promise上反复调用get_future会抛出future_error异常。
共享状态。在std::promise构造时，std::promise对象会与共享状态关联起来，这个共享状态可以存储一个R类型的值或者一个由std::exception派生出来的异常值。
通过std::promise::get_future调用获得的std::future与std::promise共享相同的共享状态。
如果promise直到销毁时，都未设置过任何值，则promise会在析构时自动设置为std::future_error，这会造成std::future.get抛出std::future_error异常。*/
#include<iostream>
#include<string>
#include<vector>
#include<future>   //使用packaged_task也必须包含的头文件
#include<mutex>
#include<thread>
using std::cout;
using std::endl;
int MyThr1(int i,std::string flag)
{
	cout << flag<<"调用了被打包的MyThr1函数" << endl;
	std::chrono::milliseconds sleep(2000);
	std::this_thread::sleep_for(sleep);   //模拟线程处理事件事件
	cout << "MyThr1线程正在执行中 " << "ID=" << std::this_thread::get_id() << endl;
	cout << "MyThr1执行结束:" << endl;
	return i;
}
int main()
{ 
	cout << "主线程正在执行中 " << "ID=" << std::this_thread::get_id() << endl;
	 //  :packaged  包装  task  任务  packaged_task<可调用对象返回值(可调用对象的参数列表)> 

	//例1:  打包可调用函数MyThr1
	std::packaged_task<int(int,std::string)> Fun_tsk1(MyThr1);   //通过该packaged_task模板对象****打包各种可调用对象,方便以后作为线程入口函数来调用***

	//例2:  打包Lambda表达式[](){ };
	std::packaged_task<void(std::string)>Lambda_task1([](std::string msg){
	
		cout << msg << "调用了被打包的Lambda表达式" << endl;
		cout << "Lambda线程正在执行中 " << "ID=" << std::this_thread::get_id() << endl;
		cout << "Lambda调用结束了" << endl;
	});

																		//调用方法

	//方法一  .通过thread创建线程,packaged_task生成的对象代替原函数作为线程入口函数
	std::thread Thr1(std::ref(Lambda_task1), "方法一 ");  //创建线程并直接开始执行
	Thr1.join();

	std::thread Tr(std::ref(Fun_tsk1), 2020, "方法一");
	std::future<int>result=Fun_tsk1.get_future();
	//packaged_task生成的Object具有一个Object.get.future();的成员函数,用来返回一个future<返回值类型>的类模板对象的类型值,在用相应的类模板对象接收
	cout << "获取返回值" << result.get() << endl;  

	//方法二  .仿函数形式，启动任务
	/*因为packaged_task的对象成员中有仿函数对象存在    void operator()( ArgTypes... args ); 
	所以packaged_task的对象也是一个可调用对象, 可以通过以下方法调用(相当于直接在主线程的成员函数调用)*/

	Fun_tsk1.reset();  //******重置共享状态**********
	Lambda_task1.reset();  //重置共享状态
	Fun_tsk1(2020, "方法二 ");						//直接通过packaged_task的对象来调用 (参数列表) 为被绑定可调用对象需要传递的参数
	Lambda_task1("方法二 ");
	
	//方法三 将打包对象放入容器中
	Fun_tsk1.reset();//重置共享状态
	std::vector<std::packaged_task<int(int,std::string)>>ArrFunTask;  //创建一个容纳指定packaged_task Object的vector容器
	ArrFunTask.push_back(std::move(Fun_tsk1));  //使用移动语义,移动赋值,赋值完后	原地址即&Fun_tsk1指向Null 
	std::packaged_task<int(int, std::string)>Fun_tsk2;
	auto iter = ArrFunTask.begin();
	Fun_tsk2 = std::move(*iter);   //使用移动语义将vector中的packaged_task Object移除赋值到Fun_tsk2中，*iter指向空,但容器中size还在需要erase删除
	ArrFunTask.erase(iter); //删除空项
	Fun_tsk2(2, "移动语义进行移动赋值后使用赋值对象");
	system("PAUSE");
	return 0;
}
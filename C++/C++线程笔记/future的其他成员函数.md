#include<iostream>                     //std::future 只能get一次 get是移动语义
									//****std::shared_future 可以get多次  get是复制数据***
							//传递类模板的对象必须使用std::move的移动语义,share_future除了可以使用移动语义还可以使用Object.shared();与move效果完全相同
#include<future>
#include<thread>
using std::cout;
using std::endl;
using std::string;
int thr()
{
	cout << "线程开始执行" << endl;

	//模拟线程处理时间
	std::chrono::milliseconds sleep(3000);
	std::this_thread::sleep_for(sleep);

	cout << "线程结束执行" << endl;
	return 2025;
}
int main()
{
	//创建异步任务立即执行
	//不同与普通的future,shared_future的get是复制而不是移动,因此可以多次get
	std::shared_future<int>result = std::async(/*std::launch::deferred,*/ thr);


	//等待3s,如果异步任务还没执行完毕,返回状态枚举值timeout表示线程超时,超出等待时间
	//wait_for等待一段时间  返回三种枚举类型 timeout/ready/deferred  注:延迟启动状态下,wait_for直接返回枚举,不会等待
	std::future_status stus = result.wait_for(std::chrono::seconds(4));  
	if (stus == std::future_status::timeout)
	{
		cout << "线程执行时间超过等待时间:timeout" << endl;
	}


	//异步任务已执行完毕
	else if (stus == std::future_status::ready)
	{
		cout << "线程执行完毕:ready" << endl;
		//多次get
		bool flag = result.valid();  //返回一个bool值,表示result里面是否有值可以被get,有则返回false;

		cout << "第一次get返回值=:" << result.get() << endl;
				if (flag)
				{
					cout << "result存在值" << endl;
				}
		cout << "第二次get返回值=:" << result.get() << endl;
	}

	//延迟启动

	else if (stus== std::future_status::deferred)
	{

		cout << "使用std::launch::deffered方法在主线程中延迟启动:deffered" << endl;
		cout << "开始获取延迟启动返回值:" << endl;
		cout << "返回值=:" << result.get() << endl;
		
	}

	system("PAUSE");
	return 0;
}
#include<iostream>
#include<vector>
#include<list>
#include<thread>
#include<mutex>
std::timed_mutex m_mutex;
//具有超时功能的独占互斥量
//使用:调用成员函数try_for(等待时间)与try_until(一直持续到的时间) ) 在这段时间内不断不断尝试锁住互斥量,成功返回true,失败返回false
//try_for(等待时间)与try_until(一直持续到的时间)方式不同,功能相同
//作用:通过bool返回值实现不堵塞的功能,不需要依赖future的成员函数或者参数try_lock来实现不阻塞
//特点:相比std::mutex灵活,可以不被堵塞
using namespace std;
class msgQueue  //消息队列
{
public:
	bool IsRecvMsg()
	{
		if (!msgMyQueue.empty())
		{
			cout << "msgQueue读取到需处理消息" << msgMyQueue.front() << endl;
			return true;
		}
		else
		{
			cout << "MsgOutQueue执行,但消息队列读取为空" << endl;
			return false;
		}
	}
	void MsgRecvQueue()
	{
		for (int i = 0; i < 100000; ++i)
		{
			//m_mutex.lock();
			std::chrono::milliseconds TIM(10);
			//until (std::chrono::steady_clock::now()+TIM )即 当前时间+TIM 这段时间内不断获取锁,成功返回true
			if (m_mutex.try_lock_until(std::chrono::steady_clock::now() + TIM))
			//在TIM时间内不断尝试加锁互斥量,如果成功则返回true
			//if (m_mutex.try_lock_for(TIM))
			{
				//拿到锁了
				cout << "线程" << std::this_thread::get_id() << "   拿到锁了" << endl;
				/*std::chrono::milliseconds sleeptime(1000);
				std::this_thread::sleep_for(sleeptime);*/
				msgMyQueue.push_back(i);   //消息队列接收消息
				cout << "msgQueue接收到消息" << i << endl;
				m_mutex.unlock();
			}
			else
			{
				//没有拿到锁,干点别的事情
				cout << "线程" << std::this_thread::get_id() << "没有拿到锁,干点别的事情" << endl;
			}
			cout << "继续执行" << endl;
			cout << "继续执行" << endl;
		}
			
	}
	void MsgOutQueue()
	{
		for (int i = 0; i < 100000; i++)
		{

			m_mutex.lock();  //锁住

			if (IsRecvMsg() == true)
			{
				msgMyQueue.pop_front(); //处理完后删除消息
				cout << "处理讯息成功" << endl;
			}
			m_mutex.unlock(); //解锁
			std::chrono::milliseconds wait(200); //2ms等待
			std::this_thread::sleep_for(wait); //开始等待
		}
	}
private:
	std::list<int>msgMyQueue;  //消息队列链表 list的优点,高效插入和删除
};
int main()
{
	msgQueue myMsg;
	//多线程同时访问共享数据  同时读写需要谁用谁锁,用完解锁
	std::thread myInMsg(&msgQueue::MsgRecvQueue, &myMsg);  //消息接收
	std::thread myInMsg1(&msgQueue::MsgRecvQueue, &myMsg);  //消息接收
	std::thread myOutMsg(&msgQueue::MsgOutQueue, &myMsg);  //消息处理  （类成员函数地址,类对象,（若有构造函数）构造参数1,构造参数2,.....）

	myInMsg.join();
	myOutMsg.join();


	cout << "主线程结束了" << endl;
	system("pause");
	return 0;
}

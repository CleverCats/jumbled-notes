#include<iostream>
#include"my_vector.h"
#include<thread>
#include<future>
#include<mutex>
using namespace std;
class MyQuenue
{
public:
	bool IsEmpty();      //判断队列是否为空
	void InQuenue();	 //进队列
	void GetQuenueInfo();//出队列
private:
	my_vector<int>v_Info;         //接收消息
	std::mutex in_lock;
	std::mutex get_lock;
};
bool MyQuenue::IsEmpty()
{
	if (v_Info.m_size()!=0)
	{
		return false;
	}
	else
	{
		cout << "消息队列为空无法处理" << endl;
		in_lock.unlock();
		return true;
	}
}
void MyQuenue::InQuenue()
{
	for (int i = 0; i < 10000000; i++)
	{
		std::unique_lock<std::mutex>m_lock(in_lock,defer_lock);			 //智能锁
		if (m_lock.try_lock() == true)
		{
			//cout << "线程:" << this_thread::get_id() <<"成功锁住互斥量"<< endl;
			v_Info.m_push_back(i);
			cout << "成功接收消息:" << i << "  当前队列待处理消息余总量:　" << v_Info.m_size() << endl;
			m_lock.unlock();										     //解锁
		}
		else
		{
			cout << "正在等待消息处理......." << "  当前队列待处理消息余总量:　" << v_Info.m_size() << endl;
		}
	}
}
void MyQuenue::GetQuenueInfo()
{
	int i = 0;
	while (true)
	{
		in_lock.lock();
		cout << "线程:" << this_thread::get_id() << "成功锁住互斥量" << endl;
		if (IsEmpty() == false)
		{
			i++;
			v_Info.m_pop_back();
			cout << "        累积成功处理消息: " << i << endl;
			in_lock.unlock();
		}
		//else
		//{
		//	
		//	/*std::chrono::milliseconds sleep(300);
		//	std::this_thread::sleep_for(sleep);*/
		//}
	}
}
int main()
{
	MyQuenue QuenueInfo;
	std::thread InThread(&MyQuenue::InQuenue, &QuenueInfo);
	std::thread GetThread(&MyQuenue::GetQuenueInfo, &QuenueInfo);
	InThread.join();
	GetThread.join(); 
	system("PAUSE");
	return 0;
}
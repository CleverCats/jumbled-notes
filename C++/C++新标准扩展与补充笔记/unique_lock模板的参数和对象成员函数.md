#include<iostream>
#include<vector>
#include<list>
#include<thread>
#include<mutex>  //互斥量  
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
		{	//传入参数try_to_lock的作用是使对象u_lock尝试锁住互斥量,如果失败也可以执行如下判断代码,然后接着往下运行,不会阻塞等待
			std::unique_lock<mutex>u_lock(m_tex, std::try_to_lock);  //当传入参数try_to_lock当被锁住时不会像guard_lock一样在此处等待而是可以通过else继续运行,执行完else判断后接着往下运行
		    if (u_lock.owns_lock()==true)  /*检测互斥量是否被加锁,失败返回false */	
			{
				//........如果成功锁住
				cout << "成功锁住" << endl;
			}
			else
			{
				//......如果没有锁住
				cout << "没有锁住互斥量解锁,干点其他事" << endl;
			}
			msgMyQueue.push_back(i);   //消息队列接收消息
			cout << "msgQueue接收到消息" << i << endl;
			//std::unique_lock<mutex>d_lock(m_tex,defer_lock);  //defer_lock初始化一个没被锁住的内模板对象,该语句其实就是将锁和d_lock绑定到一起
			//														//优点,可以灵活解锁与锁住
			//if (d_lock.try_lock() == true)  //尝试给互斥量加锁,如果没有成功则返回false
			//{
			//	//拿到锁了
			//	cout << "拿到锁了" << endl;
			//	msgMyQueue.push_back(i);   //消息队列接收消息
			//	cout << "msgQueue接收到消息" << i << endl;
			//}
			//else
			//{
			//	//没有拿到锁,干点别的事情
			//	cout << "没有拿到锁,干点别的事情" << endl;
			//}
			//d_lock.lock();//锁住
			
			//...共享程序的使用
			//msgMyQueue.push_back(i);   //消息队列接收消息
			//cout << "msgQueue接收到消息" << i << endl;
			//d_lock.unlock();  //解锁 
			//...私有程序的使用,解锁用来不影响其他进程

			//...
			//使用完后如果已经unlock就不会调用析构函数中的unlock;
		}
	}
	void MsgOutQueue()
	{
		for (int i = 0; i < 10000; i++)
		{
			
			m_tex.lock();  //锁住
			
			if(IsRecvMsg()==true)
			{
				
				msgMyQueue.pop_front(); //处理完后删除消息
				cout << "处理讯息成功"<< endl;
				
			}
			m_tex.unlock(); //解锁
			std::chrono::milliseconds wait(200); //2ms等待
			std::this_thread::sleep_for(wait); //开始等待
		}
	}
private:
	std::list<int>msgMyQueue;  //消息队列链表 list的优点,高效插入和删除
	mutex m_tex; //锁1
	mutex m_tex2; //锁2
};
int main()
{
	msgQueue myMsg;
						  //多线程同时访问共享数据  同时读写需要谁用谁锁,用完解锁
	std::thread myInMsg(&msgQueue::MsgRecvQueue, &myMsg);  //消息接收
	std::thread myOutMsg(&msgQueue::MsgOutQueue, &myMsg);  //消息处理  （类成员函数地址,类对象,（若有构造函数）构造参数1,构造参数2,.....）

	myInMsg.join(); 
	myOutMsg.join();
	

	cout << "主线程结束了" << endl;	
	//system("pause");
	return 0;
}
/* 总结: 1.模板对象的创建的作用是将模板对象与互斥量绑定在一起，通过模板对象的传递参数初始化或者模板对象的成员函数灵活的进行锁的操作
	     2.参数defer_lock初始化一个未被锁住的模板对象,从而可以灵活使用模板对象的成员函数例如 Object.tye_lock() 尝试锁住互斥量，并且根据返回值执行相应的代码,执行完后继续往下执行
		    而不会像普通的情况区等待锁被解锁
			或者可以灵活使用unique的成员函数 lock();unlock();

			Object.lock();
			处理共享代码....
			Object.unlock();
			处理非共享代码...


		 if (d_lock.try_lock() == true)  //尝试给互斥量加锁,如果没有成功则返回false
			{
				拿到锁
				处理......
			}
			else
			{
				没有拿到锁,干点别的事情
				处理.....
			}
			//继续往下执行代码

		3.若为使用类模板对象的成员函数tye_lock 可以使用 unique<mutext>Object(m_tex,std::tye_to_lock); 即传入tye_to_lock参数,该参数实际是一个结构体对象
		  它的传入会执行尝试锁住互斥量,同时也不会被阻塞,可以使用如下的代码判断互斥量是否被成功锁住,而执行相应的代码,然后继续往下执行
		  if (u_lock.owns_lock()==true)  /*检测互斥量是否被加锁,失败返回false 
			{
				//........如果成功锁住
				cout << "成功锁住" << endl;
			}
			else
			{
				//......如果没有锁住
				cout << "等待解锁,干点其他事" << endl;
			}
			//.....继续执行
		4.使程序等待的函数  std::chrono::milliseconds wait(200); 实例化2ms等待的对象（chrono 计时器）
							std::this_thread::sleep_for(wait); 开始等待

		5.模板对象.release()  解开对象和锁的关联关系,模板对象绑定关联的指针置为Null,同时返回一个mutex的指针，该指针即为当前被解开关联的锁的指针
		      std::mutex*mu=Object.release()； 因为解除了关联,所以如果该互斥量锁住,将不会在Object的析构中被解锁	,所以需要程序员接管下来手动解锁 mu->unlock();
		6.unique_lock的所有权的传递:
		std::unique_lock<mutex>u_lock(m_tex); 表示u_lock拥有m_tex的所有权
		传递方法1:
		***  复制所有权是非法的:			std::unique_lock<mutex>u_lock2(u_lock);    ***
		***  移动所有权是合法的:			std::unique_lock<snutex>u_lock2(move(u_lock));   *** 转移所有权后u_lock关联的指针为Null,解除关联,u_lock2开始关联m_tex
		传递方法二:
		public:
		std::unique_lock<mutex>u_lock();  //实例化一个unique_lock<mutex>模板类的对象,但没有关联任何互斥量 (这句话其实相当于  函数返回值类型  函数名() )
			{
				unique_lock<mutex>u_temp(m_tex);  //实例化一个关联m_tex的temp对象
				return u_temp;  返回临时的temp
			}

			std::unique_lock<mutex>u_lock2 = u_lock();  //调用该语句时相当于初始化u_lock2使其关联  u_lock()的返回值,也就是 temp 代表的指针,即关联了m_tex,达到了所有权的转移*/
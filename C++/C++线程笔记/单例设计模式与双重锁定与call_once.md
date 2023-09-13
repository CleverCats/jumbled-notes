#include<iostream>                                                             /******单例模式*******/
#include<string>
#include<thread>
#include<mutex>
#include<vector>
using namespace std;

//std::once_flag m_flag;  //********  once_flag实际上是一个结构体,它实例化的对象可以看作一个标记,该标记结合call_once使用  ********
                                //call_once(m_flag,需调用的函数);  该语句第一次被执行会产生一个****锁的作用****,当一个线程执行到该语句,其他线程如果也要执行该语句则会被阻塞
                                //当第一个线程执行完该语句后,即调用完第二个参数(需调用的函数),m_falg这个标记就被做了记号,其它线程就会识别该记号,然后不在执行参数二的函数
//小结:call_once(标记,函数);可以实现多线程都执行该语句但只会有一个线程成功即执行参数二的函数,其它线程不在执行该函数;即保证参数二的函数只被调用一次

std::mutex m_mutex1;  //堆区的互斥量(静态成员函数不能调用非静态的变量)
class MakeFile
{
private:
	MakeFile(){}  //构造函数做私有成员,以保证不能直接实例化对象
	static MakeFile*m_instance;  //静态类指针作为成员变量
public:                                                                            //（也叫双重锁定）
	static MakeFile*get_instance()                                        /*****双重检查可以提高效率,达到多个线程不在此处为一个If判断而等待锁的堵塞情况*****/
	{
		if (m_instance == NULL)  //双重检查,如果!=Null表示一定有一个线程已经实例化了该单例对象，不需要在调用m_instance = new MakeFile();
			                       //  此时直接调用 return m_instance;获取MakeFile类的单例对象
			                              //如果=Null表示不一定没有实例化该单例对象,因为两个线程可能同时判断为=Null 此时就进入了争夺锁的环节
		{
			unique_lock<mutex>un_lock(m_mutex1);    //等待一方执行完后，必然单例对象已经被实例化 第二重检测为!=Null 直接执行return m_instance;
			//多线程使用该单例对象时都会进行此判断,可能会存在同时判断为Null的现象
			if (m_instance == NULL)  //如果静态该类成员指针为空
			{
				m_instance = new MakeFile();  //实例化一个匿名无参的临时对象做右值,并用静态成员指针接收new返回的临时对象地址
				cout << "实例化了一个单例对象" << endl;
				static PRecycle rec;//创建一个静态类，该类仅在系统结束时回收调用它的析构函数,同时在其析构函数中实现MakeFlie的静态成员指针的回收(可以不写,因为系统会自动回收，但写了更好)
			}
			//return m_instance;   //如果静态类成员指针已经不为空，那么即返回原单例的对象指针，不进行构造.以保持MakeFile类只存在一个对象，即单例对象
			//返回该临时对象的指针
		}
			return m_instance;
	}
	class PRecycle  //指针回收
	{
	public:
		~PRecycle()
		{
			if (MakeFile::m_instance!=NULL)
			{
				delete MakeFile::m_instance;  //释放MakeFile的单例的指针空间
				MakeFile::m_instance = NULL; //置空
			}
		}
	};
};
void Thr1(int i)  //线程入口
{
	cout << "我的线程开始了"<<i << endl;
	MakeFile*m_Obj = MakeFile::get_instance();  //两个线程都要使用MakeFile类的单例对象,如果没有该单例对象，就在线程中实例化
	cout << "我的线程结束了" << i << endl;
}
MakeFile*MakeFile::m_instance = NULL;  //静态成员类外初始化
int main()
{
	//MakeFile*m_Obj = MakeFile::get_instance();  //通过静态成员函数返回一个临时的匿名类对象指针,并用m_Obj接收,从而实现单例化类对象
	//thread m_thr1(Thr1,1);  //两个线程用一个接口,如果需要在线程中实例化MakeFile类的单例对象
	vector<thread>ArrThread;
	for (int i = 0; i < 100000; i++)
	{
		/*std::chrono::milliseconds wait(20);
		std::this_thread::sleep_for(wait);*/
		ArrThread.push_back(thread(Thr1, i));
	}
	for (int i = 0; i < 100000; i++)
	{
		ArrThread[i].join();
	}
	//MakeFile*m_Obj2 = MakeFile::get_instance();  //两者指针相同,并没有构建新的对象
	//MakeFile obj; //不允许,因为构造函数为私有成员函数
	system("PAUSE");
	return 0;
}

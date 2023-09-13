
#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<future>
using namespace std;
static int num = 0;
std::recursive_mutex m_mutex;  //递归独占式的递归互斥量
//独占式的递归互斥量
//特点:相对于普通的独占式互斥量std::mutex obj; 递归式独占互斥量允许**同一个线程***多次.lock()****，普通独占式互斥量则不允许
//效率:比std::mutex这种独占式互斥量消耗资源大
//用法:和普通std::mutex相同,但多次lock时,释放互斥量时需要调用与该锁层次深度相同次数的 unlock()
//注意:独占式互斥量的多次,多次使用递归(调用.lock)可能会报错,但几乎不会发生,不考虑
//有锁的作用,当前线程使用std::recursive mutex这种互斥量时别的线程就进不来,这玩意的作用就是允许一个线程中互斥量多次lock
void myfun();
void mythread()
{
	for (int i = 0; i < 100000; i++)
	{
		std::lock_guard<std::recursive_mutex> g1(m_mutex);
		num++;
		cout << "num=" << num << endl;

		//调用
		myfun();  
	}

}
inline void myfun()
{
	std::lock_guard<std::recursive_mutex> g2(m_mutex);
	num++;
}
int main()
{

	std::thread thr1(mythread);
	std::thread thr2(mythread);
	thr1.join();
	thr2.join();
	system("PAUSE");
	return 0;
}

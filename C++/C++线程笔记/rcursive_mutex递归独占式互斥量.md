
#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<future>
using namespace std;
static int num = 0;
std::recursive_mutex m_mutex;  //�ݹ��ռʽ�ĵݹ黥����
//��ռʽ�ĵݹ黥����
//�ص�:�������ͨ�Ķ�ռʽ������std::mutex obj; �ݹ�ʽ��ռ����������**ͬһ���߳�***���.lock()****����ͨ��ռʽ������������
//Ч��:��std::mutex���ֶ�ռʽ������������Դ��
//�÷�:����ͨstd::mutex��ͬ,�����lockʱ,�ͷŻ�����ʱ��Ҫ�����������������ͬ������ unlock()
//ע��:��ռʽ�������Ķ��,���ʹ�õݹ�(����.lock)���ܻᱨ��,���������ᷢ��,������
//����������,��ǰ�߳�ʹ��std::recursive mutex���ֻ�����ʱ����߳̾ͽ�����,����������þ�������һ���߳��л��������lock
void myfun();
void mythread()
{
	for (int i = 0; i < 100000; i++)
	{
		std::lock_guard<std::recursive_mutex> g1(m_mutex);
		num++;
		cout << "num=" << num << endl;

		//����
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

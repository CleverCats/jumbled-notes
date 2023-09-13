#include<iostream>
#include"my_vector.h"
#include<thread>
#include<future>
#include<mutex>
using namespace std;
class MyQuenue
{
public:
	bool IsEmpty();      //�ж϶����Ƿ�Ϊ��
	void InQuenue();	 //������
	void GetQuenueInfo();//������
private:
	my_vector<int>v_Info;         //������Ϣ
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
		cout << "��Ϣ����Ϊ���޷�����" << endl;
		in_lock.unlock();
		return true;
	}
}
void MyQuenue::InQuenue()
{
	for (int i = 0; i < 10000000; i++)
	{
		std::unique_lock<std::mutex>m_lock(in_lock,defer_lock);			 //������
		if (m_lock.try_lock() == true)
		{
			//cout << "�߳�:" << this_thread::get_id() <<"�ɹ���ס������"<< endl;
			v_Info.m_push_back(i);
			cout << "�ɹ�������Ϣ:" << i << "  ��ǰ���д�������Ϣ������:��" << v_Info.m_size() << endl;
			m_lock.unlock();										     //����
		}
		else
		{
			cout << "���ڵȴ���Ϣ����......." << "  ��ǰ���д�������Ϣ������:��" << v_Info.m_size() << endl;
		}
	}
}
void MyQuenue::GetQuenueInfo()
{
	int i = 0;
	while (true)
	{
		in_lock.lock();
		cout << "�߳�:" << this_thread::get_id() << "�ɹ���ס������" << endl;
		if (IsEmpty() == false)
		{
			i++;
			v_Info.m_pop_back();
			cout << "        �ۻ��ɹ�������Ϣ: " << i << endl;
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
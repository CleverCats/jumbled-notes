#include<iostream>
#include<vector>
#include<list>
#include<thread>
#include<mutex>
std::timed_mutex m_mutex;
//���г�ʱ���ܵĶ�ռ������
//ʹ��:���ó�Ա����try_for(�ȴ�ʱ��)��try_until(һֱ��������ʱ��) ) �����ʱ���ڲ��ϲ��ϳ�����ס������,�ɹ�����true,ʧ�ܷ���false
//try_for(�ȴ�ʱ��)��try_until(һֱ��������ʱ��)��ʽ��ͬ,������ͬ
//����:ͨ��bool����ֵʵ�ֲ������Ĺ���,����Ҫ����future�ĳ�Ա�������߲���try_lock��ʵ�ֲ�����
//�ص�:���std::mutex���,���Բ�������
using namespace std;
class msgQueue  //��Ϣ����
{
public:
	bool IsRecvMsg()
	{
		if (!msgMyQueue.empty())
		{
			cout << "msgQueue��ȡ���账����Ϣ" << msgMyQueue.front() << endl;
			return true;
		}
		else
		{
			cout << "MsgOutQueueִ��,����Ϣ���ж�ȡΪ��" << endl;
			return false;
		}
	}
	void MsgRecvQueue()
	{
		for (int i = 0; i < 100000; ++i)
		{
			//m_mutex.lock();
			std::chrono::milliseconds TIM(10);
			//until (std::chrono::steady_clock::now()+TIM )�� ��ǰʱ��+TIM ���ʱ���ڲ��ϻ�ȡ��,�ɹ�����true
			if (m_mutex.try_lock_until(std::chrono::steady_clock::now() + TIM))
			//��TIMʱ���ڲ��ϳ��Լ���������,����ɹ��򷵻�true
			//if (m_mutex.try_lock_for(TIM))
			{
				//�õ�����
				cout << "�߳�" << std::this_thread::get_id() << "   �õ�����" << endl;
				/*std::chrono::milliseconds sleeptime(1000);
				std::this_thread::sleep_for(sleeptime);*/
				msgMyQueue.push_back(i);   //��Ϣ���н�����Ϣ
				cout << "msgQueue���յ���Ϣ" << i << endl;
				m_mutex.unlock();
			}
			else
			{
				//û���õ���,�ɵ�������
				cout << "�߳�" << std::this_thread::get_id() << "û���õ���,�ɵ�������" << endl;
			}
			cout << "����ִ��" << endl;
			cout << "����ִ��" << endl;
		}
			
	}
	void MsgOutQueue()
	{
		for (int i = 0; i < 100000; i++)
		{

			m_mutex.lock();  //��ס

			if (IsRecvMsg() == true)
			{
				msgMyQueue.pop_front(); //�������ɾ����Ϣ
				cout << "����ѶϢ�ɹ�" << endl;
			}
			m_mutex.unlock(); //����
			std::chrono::milliseconds wait(200); //2ms�ȴ�
			std::this_thread::sleep_for(wait); //��ʼ�ȴ�
		}
	}
private:
	std::list<int>msgMyQueue;  //��Ϣ�������� list���ŵ�,��Ч�����ɾ��
};
int main()
{
	msgQueue myMsg;
	//���߳�ͬʱ���ʹ�������  ͬʱ��д��Ҫ˭��˭��,�������
	std::thread myInMsg(&msgQueue::MsgRecvQueue, &myMsg);  //��Ϣ����
	std::thread myInMsg1(&msgQueue::MsgRecvQueue, &myMsg);  //��Ϣ����
	std::thread myOutMsg(&msgQueue::MsgOutQueue, &myMsg);  //��Ϣ����  �����Ա������ַ,�����,�����й��캯�����������1,�������2,.....��

	myInMsg.join();
	myOutMsg.join();


	cout << "���߳̽�����" << endl;
	system("pause");
	return 0;
}

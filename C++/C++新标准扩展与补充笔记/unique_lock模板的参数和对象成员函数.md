#include<iostream>
#include<vector>
#include<list>
#include<thread>
#include<mutex>  //������  
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
		{	//�������try_to_lock��������ʹ����u_lock������ס������,���ʧ��Ҳ����ִ�������жϴ���,Ȼ�������������,���������ȴ�
			std::unique_lock<mutex>u_lock(m_tex, std::try_to_lock);  //���������try_to_lock������סʱ������guard_lockһ���ڴ˴��ȴ����ǿ���ͨ��else��������,ִ����else�жϺ������������
		    if (u_lock.owns_lock()==true)  /*��⻥�����Ƿ񱻼���,ʧ�ܷ���false */	
			{
				//........����ɹ���ס
				cout << "�ɹ���ס" << endl;
			}
			else
			{
				//......���û����ס
				cout << "û����ס����������,�ɵ�������" << endl;
			}
			msgMyQueue.push_back(i);   //��Ϣ���н�����Ϣ
			cout << "msgQueue���յ���Ϣ" << i << endl;
			//std::unique_lock<mutex>d_lock(m_tex,defer_lock);  //defer_lock��ʼ��һ��û����ס����ģ�����,�������ʵ���ǽ�����d_lock�󶨵�һ��
			//														//�ŵ�,��������������ס
			//if (d_lock.try_lock() == true)  //���Ը�����������,���û�гɹ��򷵻�false
			//{
			//	//�õ�����
			//	cout << "�õ�����" << endl;
			//	msgMyQueue.push_back(i);   //��Ϣ���н�����Ϣ
			//	cout << "msgQueue���յ���Ϣ" << i << endl;
			//}
			//else
			//{
			//	//û���õ���,�ɵ�������
			//	cout << "û���õ���,�ɵ�������" << endl;
			//}
			//d_lock.lock();//��ס
			
			//...��������ʹ��
			//msgMyQueue.push_back(i);   //��Ϣ���н�����Ϣ
			//cout << "msgQueue���յ���Ϣ" << i << endl;
			//d_lock.unlock();  //���� 
			//...˽�г����ʹ��,����������Ӱ����������

			//...
			//ʹ���������Ѿ�unlock�Ͳ���������������е�unlock;
		}
	}
	void MsgOutQueue()
	{
		for (int i = 0; i < 10000; i++)
		{
			
			m_tex.lock();  //��ס
			
			if(IsRecvMsg()==true)
			{
				
				msgMyQueue.pop_front(); //�������ɾ����Ϣ
				cout << "����ѶϢ�ɹ�"<< endl;
				
			}
			m_tex.unlock(); //����
			std::chrono::milliseconds wait(200); //2ms�ȴ�
			std::this_thread::sleep_for(wait); //��ʼ�ȴ�
		}
	}
private:
	std::list<int>msgMyQueue;  //��Ϣ�������� list���ŵ�,��Ч�����ɾ��
	mutex m_tex; //��1
	mutex m_tex2; //��2
};
int main()
{
	msgQueue myMsg;
						  //���߳�ͬʱ���ʹ�������  ͬʱ��д��Ҫ˭��˭��,�������
	std::thread myInMsg(&msgQueue::MsgRecvQueue, &myMsg);  //��Ϣ����
	std::thread myOutMsg(&msgQueue::MsgOutQueue, &myMsg);  //��Ϣ����  �����Ա������ַ,�����,�����й��캯�����������1,�������2,.....��

	myInMsg.join(); 
	myOutMsg.join();
	

	cout << "���߳̽�����" << endl;	
	//system("pause");
	return 0;
}
/* �ܽ�: 1.ģ�����Ĵ����������ǽ�ģ������뻥��������һ��ͨ��ģ�����Ĵ��ݲ�����ʼ������ģ�����ĳ�Ա�������Ľ������Ĳ���
	     2.����defer_lock��ʼ��һ��δ����ס��ģ�����,�Ӷ��������ʹ��ģ�����ĳ�Ա�������� Object.tye_lock() ������ס�����������Ҹ��ݷ���ִֵ����Ӧ�Ĵ���,ִ������������ִ��
		    ����������ͨ��������ȴ���������
			���߿������ʹ��unique�ĳ�Ա���� lock();unlock();

			Object.lock();
			���������....
			Object.unlock();
			����ǹ������...


		 if (d_lock.try_lock() == true)  //���Ը�����������,���û�гɹ��򷵻�false
			{
				�õ���
				����......
			}
			else
			{
				û���õ���,�ɵ�������
				����.....
			}
			//��������ִ�д���

		3.��Ϊʹ����ģ�����ĳ�Ա����tye_lock ����ʹ�� unique<mutext>Object(m_tex,std::tye_to_lock); ������tye_to_lock����,�ò���ʵ����һ���ṹ�����
		  ���Ĵ����ִ�г�����ס������,ͬʱҲ���ᱻ����,����ʹ�����µĴ����жϻ������Ƿ񱻳ɹ���ס,��ִ����Ӧ�Ĵ���,Ȼ���������ִ��
		  if (u_lock.owns_lock()==true)  /*��⻥�����Ƿ񱻼���,ʧ�ܷ���false 
			{
				//........����ɹ���ס
				cout << "�ɹ���ס" << endl;
			}
			else
			{
				//......���û����ס
				cout << "�ȴ�����,�ɵ�������" << endl;
			}
			//.....����ִ��
		4.ʹ����ȴ��ĺ���  std::chrono::milliseconds wait(200); ʵ����2ms�ȴ��Ķ���chrono ��ʱ����
							std::this_thread::sleep_for(wait); ��ʼ�ȴ�

		5.ģ�����.release()  �⿪��������Ĺ�����ϵ,ģ�����󶨹�����ָ����ΪNull,ͬʱ����һ��mutex��ָ�룬��ָ�뼴Ϊ��ǰ���⿪����������ָ��
		      std::mutex*mu=Object.release()�� ��Ϊ����˹���,��������û�������ס,��������Object�������б�����	,������Ҫ����Ա�ӹ������ֶ����� mu->unlock();
		6.unique_lock������Ȩ�Ĵ���:
		std::unique_lock<mutex>u_lock(m_tex); ��ʾu_lockӵ��m_tex������Ȩ
		���ݷ���1:
		***  ��������Ȩ�ǷǷ���:			std::unique_lock<mutex>u_lock2(u_lock);    ***
		***  �ƶ�����Ȩ�ǺϷ���:			std::unique_lock<snutex>u_lock2(move(u_lock));   *** ת������Ȩ��u_lock������ָ��ΪNull,�������,u_lock2��ʼ����m_tex
		���ݷ�����:
		public:
		std::unique_lock<mutex>u_lock();  //ʵ����һ��unique_lock<mutex>ģ����Ķ���,��û�й����κλ����� (��仰��ʵ�൱��  ��������ֵ����  ������() )
			{
				unique_lock<mutex>u_temp(m_tex);  //ʵ����һ������m_tex��temp����
				return u_temp;  ������ʱ��temp
			}

			std::unique_lock<mutex>u_lock2 = u_lock();  //���ø����ʱ�൱�ڳ�ʼ��u_lock2ʹ�����  u_lock()�ķ���ֵ,Ҳ���� temp �����ָ��,��������m_tex,�ﵽ������Ȩ��ת��*/
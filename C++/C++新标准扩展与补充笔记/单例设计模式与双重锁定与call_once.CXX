#include<iostream>                                                             /******����ģʽ*******/
#include<string>
#include<thread>
#include<mutex>
#include<vector>
using namespace std;

//std::once_flag m_flag;  //********  once_flagʵ������һ���ṹ��,��ʵ�����Ķ�����Կ���һ�����,�ñ�ǽ��call_onceʹ��  ********
                                //call_once(m_flag,����õĺ���);  ������һ�α�ִ�л����һ��****��������****,��һ���߳�ִ�е������,�����߳����ҲҪִ�и������ᱻ����
                                //����һ���߳�ִ���������,��������ڶ�������(����õĺ���),m_falg�����Ǿͱ����˼Ǻ�,�����߳̾ͻ�ʶ��üǺ�,Ȼ����ִ�в������ĺ���
//С��:call_once(���,����);����ʵ�ֶ��̶߳�ִ�и���䵫ֻ����һ���̳߳ɹ���ִ�в������ĺ���,�����̲߳���ִ�иú���;����֤�������ĺ���ֻ������һ��

std::mutex m_mutex1;  //�����Ļ�����(��̬��Ա�������ܵ��÷Ǿ�̬�ı���)
class MakeFile
{
private:
	MakeFile(){}  //���캯����˽�г�Ա,�Ա�֤����ֱ��ʵ��������
	static MakeFile*m_instance;  //��̬��ָ����Ϊ��Ա����
public:                                                                            //��Ҳ��˫��������
	static MakeFile*get_instance()                                        /*****˫�ؼ��������Ч��,�ﵽ����̲߳��ڴ˴�Ϊһ��If�ж϶��ȴ����Ķ������*****/
	{
		if (m_instance == NULL)  //˫�ؼ��,���!=Null��ʾһ����һ���߳��Ѿ�ʵ�����˸õ������󣬲���Ҫ�ڵ���m_instance = new MakeFile();
			                       //  ��ʱֱ�ӵ��� return m_instance;��ȡMakeFile��ĵ�������
			                              //���=Null��ʾ��һ��û��ʵ�����õ�������,��Ϊ�����߳̿���ͬʱ�ж�Ϊ=Null ��ʱ�ͽ������������Ļ���
		{
			unique_lock<mutex>un_lock(m_mutex1);    //�ȴ�һ��ִ����󣬱�Ȼ���������Ѿ���ʵ���� �ڶ��ؼ��Ϊ!=Null ֱ��ִ��return m_instance;
			//���߳�ʹ�øõ�������ʱ������д��ж�,���ܻ����ͬʱ�ж�ΪNull������
			if (m_instance == NULL)  //�����̬�����Աָ��Ϊ��
			{
				m_instance = new MakeFile();  //ʵ����һ�������޲ε���ʱ��������ֵ,���þ�̬��Աָ�����new���ص���ʱ�����ַ
				cout << "ʵ������һ����������" << endl;
				static PRecycle rec;//����һ����̬�࣬�������ϵͳ����ʱ���յ���������������,ͬʱ��������������ʵ��MakeFlie�ľ�̬��Աָ��Ļ���(���Բ�д,��Ϊϵͳ���Զ����գ���д�˸���)
			}
			//return m_instance;   //�����̬���Աָ���Ѿ���Ϊ�գ���ô������ԭ�����Ķ���ָ�룬�����й���.�Ա���MakeFile��ֻ����һ�����󣬼���������
			//���ظ���ʱ�����ָ��
		}
			return m_instance;
	}
	class PRecycle  //ָ�����
	{
	public:
		~PRecycle()
		{
			if (MakeFile::m_instance!=NULL)
			{
				delete MakeFile::m_instance;  //�ͷ�MakeFile�ĵ�����ָ��ռ�
				MakeFile::m_instance = NULL; //�ÿ�
			}
		}
	};
};
void Thr1(int i)  //�߳����
{
	cout << "�ҵ��߳̿�ʼ��"<<i << endl;
	MakeFile*m_Obj = MakeFile::get_instance();  //�����̶߳�Ҫʹ��MakeFile��ĵ�������,���û�иõ������󣬾����߳���ʵ����
	cout << "�ҵ��߳̽�����" << i << endl;
}
MakeFile*MakeFile::m_instance = NULL;  //��̬��Ա�����ʼ��
int main()
{
	//MakeFile*m_Obj = MakeFile::get_instance();  //ͨ����̬��Ա��������һ����ʱ�����������ָ��,����m_Obj����,�Ӷ�ʵ�ֵ����������
	//thread m_thr1(Thr1,1);  //�����߳���һ���ӿ�,�����Ҫ���߳���ʵ����MakeFile��ĵ�������
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
	//MakeFile*m_Obj2 = MakeFile::get_instance();  //����ָ����ͬ,��û�й����µĶ���
	//MakeFile obj; //������,��Ϊ���캯��Ϊ˽�г�Ա����
	system("PAUSE");
	return 0;
}

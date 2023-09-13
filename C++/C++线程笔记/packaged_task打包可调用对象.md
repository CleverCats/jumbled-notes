#include<iostream>
#include<string>
#include<vector>
#include<future>   //ʹ��packaged_taskҲ���������ͷ�ļ�
#include<mutex>
#include<thread>
using std::cout;
using std::endl;
int MyThr1(int i,std::string flag)
{
	cout << flag<<"�����˱������MyThr1����" << endl;
	std::chrono::milliseconds sleep(2000);
	std::this_thread::sleep_for(sleep);   //ģ���̴߳����¼��¼�
	cout << "MyThr1�߳�����ִ���� " << "ID=" << std::this_thread::get_id() << endl;
	cout << "MyThr1ִ�н���:" << endl;
	return i;
}
int main()
{ 
	cout << "���߳�����ִ���� " << "ID=" << std::this_thread::get_id() << endl;
	 //  :packaged  ��װ  task  ����  packaged_task<�ɵ��ö��󷵻�ֵ(�ɵ��ö���Ĳ����б�)> 

	//��1:  ����ɵ��ú���MyThr1
	std::packaged_task<int(int,std::string)> Fun_tsk1(MyThr1);   //ͨ����packaged_taskģ�����****������ֿɵ��ö���,�����Ժ���Ϊ�߳���ں���������***

	//��2:  ���Lambda���ʽ[](){ };
	std::packaged_task<void(std::string)>Lambda_task1([](std::string msg){
	
		cout << msg << "�����˱������Lambda���ʽ" << endl;
		cout << "Lambda�߳�����ִ���� " << "ID=" << std::this_thread::get_id() << endl;
		cout << "Lambda���ý�����" << endl;
	});

																		//���÷���

	//����һ  .ͨ��thread�����߳�,packaged_task���ɵĶ������ԭ������Ϊ�߳���ں���
	std::thread Thr1(std::ref(Lambda_task1), "����һ ");  //�����̲߳�ֱ�ӿ�ʼִ��
	Thr1.join();

	std::thread Tr(std::ref(Fun_tsk1), 2020, "����һ");
	std::future<int>result=Fun_tsk1.get_future();
	//packaged_task���ɵ�Object����һ��Object.get.future();�ĳ�Ա����,��������һ��future<����ֵ����>����ģ����������ֵ,������Ӧ����ģ��������
	cout << "��ȡ����ֵ" << result.get() << endl;  

	//������  .�º�����ʽ����������
	/*��Ϊpackaged_task�Ķ����Ա���зº����������    void operator()( ArgTypes... args ); 
	����packaged_task�Ķ���Ҳ��һ���ɵ��ö���, ����ͨ�����·�������(�൱��ֱ�������̵߳ĳ�Ա��������)*/

	Fun_tsk1.reset();  //******���ù���״̬**********
	Lambda_task1.reset();  //���ù���״̬
	Fun_tsk1(2020, "������ ");						//ֱ��ͨ��packaged_task�Ķ��������� (�����б�) Ϊ���󶨿ɵ��ö�����Ҫ���ݵĲ���
	Lambda_task1("������ ");
	
	//������ ������������������
	Fun_tsk1.reset();//���ù���״̬
	std::vector<std::packaged_task<int(int,std::string)>>ArrFunTask;  //����һ������ָ��packaged_task Object��vector����
	ArrFunTask.push_back(std::move(Fun_tsk1));  //ʹ���ƶ�����,�ƶ���ֵ,��ֵ���	ԭ��ַ��&Fun_tsk1ָ��Null 
	std::packaged_task<int(int, std::string)>Fun_tsk2;
	auto iter = ArrFunTask.begin();
	Fun_tsk2 = std::move(*iter);   //ʹ���ƶ����彫vector�е�packaged_task Object�Ƴ���ֵ��Fun_tsk2�У�*iterָ���,��������size������Ҫeraseɾ��
	ArrFunTask.erase(iter); //ɾ������
	Fun_tsk2(2, "�ƶ���������ƶ���ֵ��ʹ�ø�ֵ����");
	system("PAUSE");
	return 0;
}
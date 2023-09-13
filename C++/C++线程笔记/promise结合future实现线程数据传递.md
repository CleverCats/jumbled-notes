#include<iostream>
#include<string>
#include<vector>
#include<future>   //ʹ��packaged_taskҲ���������ͷ�ļ�
#include<mutex>
#include<thread>
using std::cout;
using std::endl;
void Thr1(std::promise<int>&tmmp, int n)
{
	cout << "�߳�1ִ����" << "ID=" << std::this_thread::get_id() << endl;
	//����һЩ����
	n=n*n+100;
	//ģ������ʱ��
	std::chrono::milliseconds sleep(2000);
	std::this_thread::sleep_for(sleep);  

	//setֵ
	tmmp.set_value(n);
	//ע��:set_valueֻ�ܱ�����һ��

	cout << "�߳�1����ִ��" << endl;
	return;
}
void Thr2(std::future<int>&tmpf)
{
	cout << "�߳�2ִ����" << "ID=" << std::this_thread::get_id() << endl;
	//get��future���󴢴��ֵΪ�߳�2����

	//ע��:getֻ�ܵ���һ��
	auto result = tmpf.get();  
	//auto result2 = tmpf.get();ֻ�ܵ���һ��
	cout << "Vaule=" << result << endl;
	cout << "�߳�2����ִ��" << endl;
	cout << "Object.setvalue Over" << result << endl;
	return;
}
int main()
{
	cout << "���߳�����ִ���� " << "ID=" << std::this_thread::get_id() << endl;
	std::promise<int> pro;  //ʵ����һ����������ֵֵpromise����ģ�����

	//promise�������߳�1����pro����setvalue
	std::thread thr(Thr1,std::ref(pro), 220);
	thr.join();

	//future����Ҳ���Ժ�promise�����
	std::future<int>result = pro.get_future();
	/*std::future<int>result2 = pro.get_future();*/  //ֻ�ܵ���һ��get.future
	//future�������߳�2
	std::thread thr2(Thr2,std::ref(result));
	thr2.join();
	system("PAUSE");
	return 0;
}
							//�ܽ�:std::promise��������ʵ���߳�֮���ͨѶ
//promise�����Set.valueֻ�ܵ���һ��                                 
//future������(=����)�󶨵ĵ�Ŀ������,Ŀ����������е�Get.futureҲֻ�ܵ���һ��  
//future��Object.get()Ҳֻ�ܵ���һ��             *****��Ϊget�൱��һ���ƶ�����,ִ��get�������Ѿ�ָ�����***
/*��ʵ��std::promise::set_xxx������ı�std::promise��״̬Ϊready���ٴε���ʱ����״̬��Ҫ��reday�ˣ����׳��쳣��*/

/*һ��std::promiseʵ��ֻ����һ��std::future��������״̬������ͬһ��std::promise�Ϸ�������get_future���׳�future_error�쳣��
����״̬����std::promise����ʱ��std::promise������빲��״̬�����������������״̬���Դ洢һ��R���͵�ֵ����һ����std::exception�����������쳣ֵ��
ͨ��std::promise::get_future���û�õ�std::future��std::promise������ͬ�Ĺ���״̬��
���promiseֱ������ʱ����δ���ù��κ�ֵ����promise��������ʱ�Զ�����Ϊstd::future_error��������std::future.get�׳�std::future_error�쳣��*/
#include<iostream>
#include<string>
#include<thread>
#include<future>
//һ����ģ�� ��ʵ�����Ķ���    �ṩһ�������̲߳�������Ļ���  future �ǽ�������˼,����һ���������õ��߳��������Ϣ,�����ڽ�����ĳ��ʱ���õ���Ϣ
int  MyThr1()
{
	std::cout << "�ҵ��߳̿�ʼ��  �߳�ID=" << std::this_thread::get_id() << std::endl;
	std::chrono::milliseconds sleep(3000); 
	std::this_thread::sleep_for(sleep);  //ģ���̴߳�����Ϣ��Ҫ��ʱ��
	std::cout << "�ҵ��߳̽�����  �߳�ID=" << std::this_thread::get_id() << std::endl;
	return 2020;
}
int main()
{
/*�����첽�����̵߳ķ�ʽö��ֵ��ֵ  launch(����)  �ܽ�;Ĭ��Ч��,***Ĭ��������ʽ***��Ĭ����ʵ����Ϊ std::async(std::launch::async|std::launch::defferred,�߳���ں���);
launch::defferred�����ӳٵ��������̵߳���û�д����߳� /*

	/*�����������  std::launch::async(ͬ������.�����߳�)  ���첽�̴߳���ʱͬ�����ã�һ���ᴴ����һ���̣߳����ϵͳ��Դ������ᴴ��ʧ�ܵ���ϵͳ����

	std::launch::defferred(�ӳٵ���,δ�����߳�)  �첽�̵߳ȴ�fature��Object.wait()����Obeject.get()��ִ��ʱ����������,����ʵ����***���߳�***��ִ�е���,��û�д������߳�*****
���ʹ�� launch::defferred ��δ����get()����wait()��ô���õ��߳�(***��ʵ�������߳���,δ�������߳�)�������ᱻִ��,***����û����������***

���ʹ��(Ĭ��) std::launch::defferred | std::launch::async �ķ�ʽ������ô�첽���񴴽������ķ�ʽ��ϵͳ����
���ϵͳ��Դ�����Ų���(һ�㶼�����) std::launch::async ���Ų���std::launch::defferred */

	std::future<int>Ret = std::async(/*Ĭ��ȱʡlaunch::async|std::launch::defferred */  MyThr1);

	//async (�첽)  ��ʾ�Զ�����һ���߳�,����ͨ��ִ�е���ڿ�ʼִ��;(future<int>Ret��ʵ�ǽ�Ret���߳̽���һЩ��ϵ)

	std::cout << "���߳�ID=" << std::this_thread::get_id() << std::endl;
	         //RetΪfutureģ�����ɵ�һ������,�����Խ����߳�(���ＴMyThr1����)����������Ϣ��
	        //����һ�����̽��ܵ�,��Ϊ����̻߳�������û�з���,��ô����Ҫֱ���̷߳��زŻ���յ�����ֵ,��������䲢��������̵߳�����

	std::chrono::milliseconds sleep(200);
	std::this_thread::sleep_for(sleep);  //ģ���̴߳�����Ϣ��Ҫ��ʱ��

	std::cout << "���ڻ�ȡ�첽�̷߳�����Ϣ......" << std::endl;
	std::cout << "���ڻ�ȡ�첽�̷߳�����Ϣ......" << std::endl;
	std::cout << "���ڻ�ȡ�첽�̷߳�����Ϣ......" << std::endl;
	std::cout << "���ڻ�ȡ�첽�̷߳�����Ϣ......" << std::endl;
	std::cout << "���ڻ�ȡ�첽�̷߳�����Ϣ......" << std::endl;
	std::cout << "���ڻ�ȡ�첽�̷߳�����Ϣ......" << std::endl;

	std::cout << "���յ��첽�̷߳��ص���Ϣ:" << Ret.get() << std::endl;   
	/******�ڴ˴����� future����.get()��ȡ�첽�̵߳ķ���ֵ,����̻߳�������û�з���,��ô���򽫻��ڴ˴�����,ֱ����ȡ����Ϣ*******/
	/*����,get()����ֻ�ܵ���һ��,���ܵ��ö��*/
	/*fature��ģ�������һ�� Object.wait()����,�ȴ��̹߳����̵߳Ľ���,�൱�� join()����*/
	system("PAUSE");
	//��ʦ�����������get���̻߳���return 0;Ҳ�ᴦ�ȴ��첽�߳������ִ��,������û�г��������߳�		
	return 0;

}

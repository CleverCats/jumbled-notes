#include<iostream>
#include<thread>
using namespace std;
int main()
{
	auto sonlambda = [](void){
		
		cout << "LAMBDA�߳̿�ʼ��" << endl;
		cout << "LAMBDA�߳̿�ʼ��" << endl;
		cout << "LAMBDA�߳̿�ʼ��" << endl;
		cout << "LAMBDA�߳̿�ʼ��" << endl;
		cout << "LAMBDA�߳̿�ʼ��" << endl;
	};
	thread thre1(sonlambda);
	thre1.detach();
	cout << "���̵߳�����" << endl;
	cout << "���̵߳�����" << endl;
	cout << "���̵߳�����" << endl;
	cout << "���̵߳�����" << endl;
	cout << "���̵߳�����" << endl;
	cout << "���߳����н���" << endl;
	system("pause");
	return 0;
}
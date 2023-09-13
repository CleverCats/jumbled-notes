#include<iostream>
#include<thread>
using namespace std;
int main()
{
	auto sonlambda = [](void){
		
		cout << "LAMBDA线程开始了" << endl;
		cout << "LAMBDA线程开始了" << endl;
		cout << "LAMBDA线程开始了" << endl;
		cout << "LAMBDA线程开始了" << endl;
		cout << "LAMBDA线程开始了" << endl;
	};
	thread thre1(sonlambda);
	thre1.detach();
	cout << "主线程调用中" << endl;
	cout << "主线程调用中" << endl;
	cout << "主线程调用中" << endl;
	cout << "主线程调用中" << endl;
	cout << "主线程调用中" << endl;
	cout << "主线程运行结束" << endl;
	system("pause");
	return 0;
}
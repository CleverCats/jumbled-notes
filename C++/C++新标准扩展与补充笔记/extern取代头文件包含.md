#include<iostream>
using namespace std;
int main()
{

	//���������ļ��ĺ���ֻ��Ҫд��������,�Ϳ���ʹ����
	//�����Ļ�û��Ҫ��extern��ȫ�ֱ����Ļ���Ҫ�ӣ����������static���εĻ�,������������ֻ���ڵ�ǰ�����ε��ļ�,���ɱ������ļ�����
	void p();
	void f();
		//fun1.cpp

		/*#include<iostream>
		using namespace std;

	    static int B ���κ�������ֻ���ڵ�ǰ�ļ�,���ɱ������ļ����� 
		/*int B=20;

		void p()
		{
			cout << B << endl;
		}*/
	
		
	//���߱�����,���������ļ������Ѿ������B��,�ñ�����ȥѰ��,����ȡ��#include".cpp/h"�İ���
	extern int B;
	cout << B << endl;
	B = 40;
	p();
	f();
	system("pause");
	return 0;
}
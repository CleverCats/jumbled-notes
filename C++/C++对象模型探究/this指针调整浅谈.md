#include<iostream>
using namespace std;
class A
{
public:
	A()
	{
		cout << "A ������ this = " << this << endl;
	}
	void funA()
	{
		cout << "A func this = " << this << endl;
	}
	int a=1, b=2;
};
class B
{
public:
	B()
	{
		cout << "B ������ this = " << this << endl;
	}
	void funB()
	{
		cout << "B  func this = " << this << endl;
	}
	int c=3, d=4;
};
//����˳�� A-B-C
class C :public A, public B
{
public:
	C()
	{
		cout << "C ������ this = " << this << endl;
	}
	void funC()
	{
		cout << "C func this = " << this << endl;
	}
	int e=5, f=6;
};
int main()
{
	C obj;       
	obj.funA();
	obj.funB(); 
	obj.funC();
	cout<<"adress obj = adress C = adress A =" <<&obj << endl;
	//thisָ���������:
	/*C�ȼ̳�A Ȼ��̳� B ��ôC����A�� thisָ����ͬ,��ʼλ�ö���A��ָ����ʼλ��---A��thisָ��
	Bthisָ����A��thisָ������ sizeof(A) ���ֽ�
	���Ե��� obj.funC(); �� obj.funA(); ʱ����ͨ��ͬһ��thisָ�����,������obj.funBʱ��������thisָ������sizeof(A)���ֽ�,��B��thisָ�봦
	Ȼ��ͨ����B��this����obj.funB()*/

	/*�ܽ�:�����Ǹ�����ĳ�Ա����,���thisָ��ͻᱻ�������Զ������������ڴ沼����ȥ,��Ӧ������������ʼ��ַ��ȥ(thisָ��)*/
	system("PAUSE");
	return 0;
}
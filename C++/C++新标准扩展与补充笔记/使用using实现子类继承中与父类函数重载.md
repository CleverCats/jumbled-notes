#include<iostream>
using namespace std;
class A
{
public:
	void print()
	{
		cout << "Father print_void was called" << endl;
	}
	void print1(int)
	{
		cout << "Father print1_int was called" << endl;
	}
	void print2(int, int)
	{
		cout << "Father print2_int_int was called" << endl;
	}
	void print2(int,int,int)
	{
		cout << "Father print2_int_int_int was called" << endl;
	}


};
class  B:public A
{
public:


	
	//��Ϊ���������������ͬ������,���ຯ�������ε�(���Ǹ���)���ຯ��,Ĭ��һ�����Ϊ����ĺ���
	//���÷���1: sonObj(sonObjΪ����Ķ���).::father(fatherΪ������)::fun(); 
	//���÷���2: �������Ա������ʹ��father::fun();���������
	//���÷���3: �������public::Ȩ�������� using father::��������������( )��;  //��using namespace����˼

	//���÷���3_C++11: �ø���ͬ�������������пɼ�,˵���˾���"�ø���ͬ�����������������������صķ�ʽ��ʹ��"
	//ע��:����using ����3 using ���Ǻ�����,�����������Ĳ����б�,�����൱�ڽ�����������������������ض���������Ա����ص���ʽ����
	//���ʹ��uisng�˷�ʽ�¸������඼�к��ʵ����ذ汾��ͬ,��ôĬ�ϵ�������İ汾
	using A::print1;
	using A::print2;
	void print()
	{
		cout << "Son print_void was called" << endl;
	}
	void print1()
	{
		cout << "Son print1_void was called" << endl;
	}
	void print2(int)
	{
		cout << "Son print2_int  was called" << endl;
	}
	void print2(int, int, int)
	{
		cout << "Son print2_int_int_int was called" << endl;
	}

	
};
int main()
{
	B b;
	//��������
	b.print();

	//���ø���
	b.A::print();

	//���ø����еĵ���print1
	b.A::print1(10);

	//��δʹ��using ����::������;ʱ,ֻ��������,ʹ�����˺�Ĭ��Ҳ��������,��������û������ƥ��ĺ���������ü̳��ڸ�������ذ汾
	b.print1();

	//��Ϊδ�������м�⵽���ʵĺ��������Ե��ø��������ص�print1
	b.print2(10,10);

	//���ʹ��uisng�˷�ʽ�¸������඼�к��ʵ����ذ汾��ͬ,��ôĬ�ϵ�������İ汾
	b.print2(10, 10, 10);
	system("pause");
	return 0;
}
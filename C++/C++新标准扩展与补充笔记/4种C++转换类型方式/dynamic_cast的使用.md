#include<iostream>
using namespace std;
class A
{
public:
	void fun();
	virtual ~A(){};
};
void A::fun()
{
	cout << "call A fun()" << endl;
}
class B:public::A
{
public:
	void fun1();
};
void B::fun1()
{
	cout << "call B fun1()" << endl;
}
class C :public::A
{
public:
	void fun3()
	{
		cout << "call C fun3" << endl;
	}
};
int main()
{
	A*p = new B;
	p->fun();
	//����ʹ��c�������͵�ǿ������ת��
	//���Խ�p����ָ��ɹ�תΪC����ָ��,�����Ȳ���ȫ,��Ϊpʵ������B���͵�ָ��,ֻ��ת��ΪB����ָ����ǰ�ȫ��
	//C*p1 = (C*)p;   //���Ե��Ǽ��Ȳ���ȫ

	//�ڶ�̬������,������Ϊ�����(���ٴ���һ���麯����Ա),�ſ���ʹ��dynamic_cast���������͵Ķ�̬ת��
	//����:dynamic_cast���������ת���İ�ȫ���,pʵ������B���͵�ָ��,���Բ���B*p1 = dynamic_cast<B*>(p);��pת��ΪB*��ָ���ǰ�ȫ��,ת���ɹ�
	//��� C*p1 = dynamic_cast<C*>(p);��Ϊpʵ���ϲ���C��ָ��,���Լ�⵽ת������ȫ,��ʱ�᷵��һ����ָ��,��ʾת�����ɹ�

	B*p1 = dynamic_cast<B*>(p);               //ָ������ת��,ʧ�ܷ��ؿ�ָ��
	if (p1!= nullptr)
	{
		cout << "��ȫת���ɹ�,pʵ������B*����ָ��" << endl;

		//����B*��ָ����Ե��õĳ�Ա����
		p1->fun1();
	}
	else
	{
		//ͨ����ȫ���,��Ϊ��Ҫת��������ʵ�����Ͳ���,���ؿ�ָ��
		cout << "��ȫת��ʧ��,pʵ���ϲ���B*����ָ��" << endl;
	}


	A *p2 = new B;
	//refΪ *p2 ������
	A &ref = *p2;

	//ʹ��dynamic_cast��refת��ΪC���Ͷ��������ref1
	//��Ϊrefʵ������B���Ͷ��������,���� dynamic_cast���������ж�ת��ʧ��,ϵͳ�׳�std::bad_cast�쳣,��Ҫ����Ա���д���
	try
	{
		C &ref1 = dynamic_cast<C&>(ref);

		//�����ȫת���ɹ��Ļ�����øö�������õĳ�Ա����
		ref1.fun3();
	}
	catch (std::bad_cast)
	{
		cout << "����ת��ʧ��,refʵ������B���͵�����,���ܰ�ȫת��ΪC��������" << endl;
	}

	system("PAUSE");
	return 0;
}
#include<iostream>
#include<vector>
using namespace std;
int fun(int a)
{
	return a;
}
int main()
{
	//int fun(int a) ��������ȥ��  ��ʽ:   ��������ֵ����  (ָ��)  (�����б�)
	int(*p)(int a);

	//������������������ڵ�ַ,ʹ�ø����͵�ָ�����ͬ���͵ĺ���
	p = fun;  //��p=&fun �ȼ� ��Ϊ���������뺯���׵�ַ������ͬ
	//ע��:һ��Ҫ��	��*p��������������,����(*p)���Ƚ��

	//************�������( ) ��Ϊ int *p (int a);��ʾһ���������� ,������Ϊ p ,��������ֵΪ int*  �ͺ���ָ������������*********

	//����(*p)��ȡ��fun,����ʱ(*p)(1973)��p(1973)�ȼ�,��Ϊ���������뺯���׵�ַ������ͬ
	cout << "return_fun =" << (*p)(1973) << endl;


	//ʹ��typedef������ȡ����,ʹ��POINT,����һ�� ����ֵ����Ϊ int �����б�Ϊ(int a) �ĺ���ָ������
	typedef int(*POINT)(int a);

	//ʵ����һ�������͵�ָ��
	POINT p_f1; 

	p_f1 = fun;
	cout << "return_*p =" << (*p_f1)(2020) << endl;
	

	//*********************************************************typedef��auto������************************************
	//typedef�Ǹ�������ȡ����,auto���Զ�ʶ�������������¾���
	vector<int>v;
	for (int i=0;i < 10;i++)
	{
		v.push_back(i*10);
	}
	//m_iterΪvector<int>::iterator���͵������ı���
	typedef vector<int>::iterator m_itr;
	//ʹ�ñ���
	for (m_itr i = v.begin(); i != v.end(); i++)
	{
		cout << *i << endl;
	}
	//auto�Զ�ʶ��v.begin()Ϊvector<int>::iterator,ʡȥ�� vector<int>::iterator i = v.begin()�������µ�����
	//auto i =     i����ͬʱ��ʼ��,�Ⱥ��ұ߲�����������,����Ҫ��ĳ�����͵Ķ���,��auto����������ƶ� ,��typedef ������������	, ��Ϊtypedef�����þ��Ǹ�������ȡ����
	for (auto i = v.begin(); i != v.end(); i++)
	{
		cout << *i << endl;
	}
	/*auto��c++11��׼�����һ�������ƶϵĹؼ��֣�
	auto�ܹ��ñ������Զ�ȥ�������ʽ����������,���ض����������Ͳ�ͬ������double��,�ñ�����ͨ����ʼֵ��������������͡���Ȼauto��������г�ʼֵ��*/
	system("PAUSE");
	return 0;
}
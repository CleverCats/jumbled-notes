#include<iostream>
#include<vector>
using namespace std;
int& fc(int &i)
{
	cout << typeid(i).name() << endl;
	return i;
}
double fc(double &i)
{
	return i;
}
template<class T>

//auto���ﲻ�������ƶ�,ֻ�Ǻ��÷���ֵ���͵� auto ��� decltype���﷨��ʽ
auto Func(T &arg)->decltype(fc(arg))  //type arg = int &
{
	//true type arg = int &
	return fc(arg);
}
/*
//C++14 decltype(auto)��Ϊǰ�÷������ͣ�Ҳ�����ڱ�������(���俴��һ�������Ͷ������Զ������ƶ�)
//auto�������ƶ�ʱ�ᶪ����ԭ���ݵ���������(����ʹ����������)
//decltype�ܹ�"���"auto���������������� �������Ҫ��ر���ʹ�� decltype(auto)���ʹ��
/*
****************************************************
ע�ⲻҪ���:  �� const int &n=10;  auto m=n; ��ʱauto�Ѿ�����const �� ���� type m = int
��ʱ decltype(m) k;  type k = int ; m������Ϊint ,��Ϊ m�Ѿ������� const �� ���� ,���� type k = int;
����ʹ�� decltype(auto) s = n; ���൱�� decltype��ֹauto���������޶�,��ʱ type s = const int &;
****************************************************
*/
/*
template<class T>
decltype(auto) Func2(T& m)  //type auto = T; type decltype(auto) = T & //decltype "���" auto������������
{
	return m;  //type m= T &
	//****************************************************
	//ע��:���ʹ�� return (m);  (m)�൱��һ�����ʽ.��ʱdecltype(auto)���ƶϳ� ��������  ���ؾֲ����������ÿ���������غ��
	//****************************************************
}
*/
int main()
{
	int n = 10; double m = 20.5;
	cout << Func(n) << endl;

	int &temp = n;
	decltype(temp) tmp_2=n;
	tmp_2 = 100;
	cout << n << endl;
	cout << "----------------------" << endl;

	//type n = int
	//decltype(Func2(n)) x = 10; //type x = int &         VS2013��֧��decltype(auto)������ֵ����
	
	const int &p = 10;
	auto p2 = p; //�ᶪ�� const  &  ��Ϊint

	//C++14��

	//decltype(auto) p3 = p;    //�����һ� "auto��������"��  const  & ��ԭΪ const int &.
	/*ע�ⲻҪ���:  �� const int &n = 10;  auto m = n; ��ʱauto�Ѿ�����const �� ���� type m = int
	��ʱ decltype(m) k;  type k = int; m������Ϊint, ��Ϊ m�Ѿ������� const �� ����, ���� type k = int;
	����ʹ�� decltype(auto) s = n; ���൱�� decltype��ֹauto���������޶�, ��ʱ type s = const int &;*/
	system("PAUSE");
	return 0;
}
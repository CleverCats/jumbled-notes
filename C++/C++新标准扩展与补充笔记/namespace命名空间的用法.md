#include<iostream>
#include<string>
//��׼�������ռ�
using namespace std;

//ʹ�ùؼ���namespace����һ�������ռ�A
//����ͨ�������ռ����������µĳ�Ա
namespace A
{
	void f1()
	{
		cout << "namespace A::f1()" << endl;
	}
}

//�Ѿ����������ռ�A��,�������������ǶԳ�Ա�����
//�����ɴ�Ҳ���������·�����std��׼�������ռ�������³�Ա
namespace A
//namespace std   //��std��׼�������ռ�������³�Ա
{
	void f2()
	{
		cout << "namespace A::f2()" << endl;
	}
}
namespace B
{
	void f1()
	{
		cout << "namespace B::f2()" << endl;
	}
}
class C
{
public:
	C()
	{
		m_str = "c++ nb";
	}
	string m_str;
};
using namespace B;
namespace D
{
	ostream& operator<<(ostream& os, string str)
	{
		os << str << endl;
	}
}
int main()
{
	//��Ҫָ�������ռ�
	A::f1();
	A::f2();
	//�Ѿ�ʹ���� using namespace B;�����ʡ��B��������B::����д(ǰ�᲻����������ͬ�������ռ��³�Ա�����Ķ�����)
	f1();
	system("pause");
	return 0;
}
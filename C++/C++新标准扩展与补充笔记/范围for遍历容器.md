#include<iostream>
#include<string>
#include<vector>
using namespace std;
void test()
{
	//C++11�п���ͨ��������{ }��ʼ��
	vector<int>v1{ 1, 2, 3, 4, 5 };

	//auto�ķ�Χfor����Ҳ����������
	for (auto &v : v1)
	{
		//v.push_back(50); //���ֲ����ᵼ������˳�����.��ʹ�÷�Χfor����ʱ,ǧ��Ҫ�ı�����������
		cout << v << endl;
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}
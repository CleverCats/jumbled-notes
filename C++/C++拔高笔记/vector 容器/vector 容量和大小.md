#include<iostream>          //��̬��չ������ԭ�пռ���濪���¿ռ�,�����ҵ�һ������Ŀռ�
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
void print(int vect)
{
	cout << vect << "  ";
}
void PrintVector(vector<int> v)
{
	for_each(v.begin(), v.end(), print);
}
void test()
{
	vector<int>v1;   //Ĭ�Ϲ���һ����Ϊv��vector<int>���͵�����
	for (int i = 0; i < 20; i++)
	{
		v1.push_back(i);
	}
	PrintVector(v1);
	if (v1.empty())
	{
		cout << "����Ϊ��" << endl;
	}
	else
	{             //v1.capacity()<=v1.size()  ��������>=������С����ǰԪ�ظ�����
		cout << "��������:" << v1.capacity() << " " << "������С����ǰԪ�ظ�����:" << v1.size() << endl;
	}
	cout << "��������resize" << endl;
	v1.resize(10,9);  //����ָ�������Ĵ�С(��������),��������ԭ��С���ֺ�Ĭ��λ��Ĭ��Ϊ0,����Ϊ9.���С��ԭ������С��ô�����������Ĳ���
	PrintVector(v1);
	cout << "��������:" << v1.capacity() << " " << "������С����ǰԪ�ظ�����:" << v1.size() << endl;
	v1.push_back(10086);
	cout << "������������" << endl;
	PrintVector(v1);
	cout << "��������:" << v1.capacity() << " " << "������С����ǰԪ�ظ�����:" << v1.size() << endl;
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}

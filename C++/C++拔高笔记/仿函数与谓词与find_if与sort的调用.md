#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
class Control
{
public:
	bool operator()(int val) //һ��������bool�ͷº���  -  һԪν��
	{
		return val>5;
	}
};
class Sort
{
public:
	bool operator()(int val1, int val2)  //����������bool�ͷº���  -  ��Ԫν��
	{
		return val2 < val1;
	}
};
template<typename V>
void PrintVector(const V &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	/*for (V::iterator i = 0; i != v.end(); i++)  //������
	{
		cout << *i << endll;
	}*/
}
void Assign()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	/*��һ���͵ڶ�������Ϊ������������(����������),����������ΪControl�������޲ι���.
	�� Control ��������( )  ��Ϊ����������������()�ҷ���ֵΪbool�ͼ�����һԪν��,
	��ʱ��Control()Ϊһ������һԪν�ʵķ���ֵ���� bool��,������Ϊfind_if�Ĳ�ѯ����*/
	vector<int>::iterator it=find_if(v.begin(), v.end(), Control()); //�������������ĵ�һ��������,���ȫ��������,�������һ��������
	if (it != v.end())
	{
		cout << "�����ɹ�:" << *it << endl;
	}
	else
	{
		cout << "�������޶������µ�ֵ" << endl;
	}
	sort(v.begin(), v.end(), Sort());  //sortҲ��������������,���������������Զ����������,Ĭ��Ϊ����
	PrintVector(v);
}
int main()
{
	Assign();
	system("PAUSE");
	return 0;
}
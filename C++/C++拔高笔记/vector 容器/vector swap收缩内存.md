#include<iostream>      //swap���������л����Ĳ���,���Դﵽ�����ڴ��Ч��
#include<string>
#include<vector>
using namespace std;
void test()
{
	vector<int>v;
	for (int i = 0; i < 99999; i++)
	{
		v.push_back(i);
	}
	cout << "v������:" << v.capacity() << "  " << "v�Ĵ�С:" << v.size() << endl;
	v.resize(3);                        
	cout << "v������:" << v.capacity() << "  " << "v�Ĵ�С:" << v.size() << endl; //��ʱ����������ɿռ��˷�
	vector<int>(v).swap(v);  //������һ����������Ŀ�������(�������ʼ�����������ڴ�С),�������������������capacity��size����v.size()
	                       //����������������ڴ���Զ�����   
	cout << "v������:" << v.capacity() << "  " << "v�Ĵ�С:" << v.size() << endl;
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}
#include<iostream>
#include<list>
using namespace std;
bool Compare(int a, int b)  //ʵ�������һ������
{
	return a > b;
}
void PrintList(const list<int> &L)
{
	for (list<int>::const_iterator i=L.begin();i!=L.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
}
void test()
{
	list<int>L;
	L.push_back(10);
	L.push_back(18);
	L.push_back(17);
	L.push_back(11);
	L.push_back(25);
	cout << "ԭʼ����" << endl;
	PrintList(L);
	cout << "���ݷ�ת" << endl;
	L.reverse();  //reverse ��ת
	PrintList(L);
	cout << "��������"<< endl;
	L.sort();  //Ĭ�ϴ�С����
	PrintList(L);
	cout << "���ݵ���" << endl;
	L.sort(Compare);       //��ʱ�����˽�ײ�ԭ��,����Compare����
	PrintList(L);
} 
int main()
{
	test(); 
	system("pause");
	return 0;
}
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
void PrintVector(int val)
{
	cout << val << endl;
}
class MyChange
{
public:
	int operator()(int val)  //�º���
	{
		return val * 10;
	}
};
void CreatVector()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>v1;  //Ŀ������
	v1.resize(v.size());  //Ԥ�ȿ���Ŀ��������С
	transform(v.begin(), v.end(), v1.begin(), MyChange());   //transform�����㷨 ��ԭ������ʼ������,ԭ�����Ľ���������,Ŀ����������ʼ������,�º�����
	//�º������Ԫ��ȡ����,����º������ڷ�����
	for_each(v.begin(), v.end(), PrintVector); //������ͨ��������,����Ϊ������
	cout << "------------------------------------------------------" << endl;
	for_each(v1.begin(), v1.end(), PrintVector);

}
int main()
{
	CreatVector();
	system("PAUSE");
	return 0;
}
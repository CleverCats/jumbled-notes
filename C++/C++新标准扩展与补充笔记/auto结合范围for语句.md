#include<iostream>
#include<string>
using namespace std;
int main()
{
	//C++11 ����ʡ��=����
	int A []{1, 2, 3, 4, 5, }; 

	//��Χfor���
	//��������A, auto &n=A[i];ֱ�����һ��Ԫ��
	for (auto &n : A)
	{
		cout << n << endl;
	}
	system("pause");
	return 0;
}
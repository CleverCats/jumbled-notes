#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
void test()
{
	//大容器
	vector<vector<int>> V;
	//小容器
	vector<int> v1;  
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;
	for (int i = 0; i < 4; i++)
	{
		v1.push_back(i + 1);
		v2.push_back(i + 2);
		v3.push_back(i + 3);
		v4.push_back(i + 4);
	}
	V.push_back(v1);
	V.push_back(v2);
	V.push_back(v3);
	V.push_back(v4);
	for (int i = 0; i < 4; i++)
	{
		cout << *v1.begin() << endl;
	}
	for (vector<vector<int>>::iterator it = V.begin(); it < V.end(); it++)  //大容器*it是返回vector<int>型的相应的小容器,需要再次二次返回
	{
		for (vector<int>::iterator vit=(*it).begin(); vit < (*it).end(); vit++)
		{
			cout << *vit;
		}
		cout << endl;
	}
	
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}
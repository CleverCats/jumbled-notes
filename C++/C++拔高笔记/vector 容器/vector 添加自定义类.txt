#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
class person
{
public:
	person(int a,string b)
	{
		this->age = a;
		this->name = b;
	}
	int age;
	string name;
};
void test()
{
	vector<person> V;  //存放自定义类数据,也可以存放指针来达到效果
	person A(13,"AA");
	person B(14, "BB");
	person C(15, "CC");
	person D(16, "DD");
	V.push_back(A);
	V.push_back(B);
	V.push_back(C);
	V.push_back(D);
	for (vector<person>::iterator vbegin = V.begin(); vbegin != V.end(); vbegin++)
	{
		cout << "姓名:" << (*vbegin).name << "  "<< "年龄:" << (*vbegin).age << endl;
	}
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}
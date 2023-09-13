#include<iostream>
using namespace std;
class person
{
public:
	person(int age)
	{
		m_age = age;
	}      
	person& Ageadd(const person&p)
	{                        
		this->m_age += p.m_age;
		return *this;   //this表示被调用成员函数，所属的对象的指针
		  //返回对象本身用 *this
	}
int m_age;
};
int main()
{
	person A(15);
	person B(10);
	                //链式编程思维
	B.Ageadd(A).Ageadd(A).Ageadd(A).Ageadd(A).Ageadd(A);
	cout << B.m_age << endl;
	system("pause");
	return 0;
}
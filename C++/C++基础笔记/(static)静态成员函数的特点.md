#include<iostream>
#include<string>
using namespace std;
class Teacher        //能在类中初始化的成员只有一种，那就是静态常量成员。
	                       //例如   const static int age=10; 
{
public:
	static void Infm()   //静态成员函数也是有访问权限的
	{
		age = 18;    //静态成员函数可以访问静态成员变量
		//score = 80; 静态成员函数不可以访问非静态成员变量
		             //无法区分到底是哪个对象的score属性
	}
	static int age;  //静态成员变量
	int score;  //非静态
};
int Teacher::age = 0;      //必须先在类外初始化
void sub()
{
	Teacher A;
	A.Infm();
	//A.Infm;//通过类对象访问
	cout << A.age << endl;
    Teacher::Infm();   //直接通过类来访问
	cout << A.age << endl;
	cout << Teacher::age << endl;
}
int main()
{ 
	sub();	
	system("pause");
	return 0;
}
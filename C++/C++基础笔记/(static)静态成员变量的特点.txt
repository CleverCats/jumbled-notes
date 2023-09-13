#include<iostream>
#include<string>
using namespace std;         //能在类中初始化的成员只有一种，那就是静态常量成员。
class person
{                    /*静态成员变量特点 
					 1.在编译阶段分配内存
					 2.自能类内声明，类外初始化
					 3.所有对象共用同一份数据*/
public:
	static string Stu1;  //注意:静态变量在类内声明后还未开辟内存空间，需要在类外初始化
	int a;     //int型声明的时候   已经分配了4个字节的空间，但还未存放变量
private:   //静态变量也是有访问权限的
	static string Stu2;
};
string person::Stu1 = "张三";
string person::Stu2 = "李四";   //类外初始化
int main()
{
	person Student;  //1.通过对象访问
	cout << sizeof(Student.a) << endl;
	cout << Student.Stu1 << endl;
	cout << person::Stu1 << endl; //2.用过类访问
	system("pause");
	return 0;
}
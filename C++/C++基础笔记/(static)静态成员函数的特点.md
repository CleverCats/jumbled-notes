#include<iostream>
#include<string>
using namespace std;
class Teacher        //�������г�ʼ���ĳ�Աֻ��һ�֣��Ǿ��Ǿ�̬������Ա��
	                       //����   const static int age=10; 
{
public:
	static void Infm()   //��̬��Ա����Ҳ���з���Ȩ�޵�
	{
		age = 18;    //��̬��Ա�������Է��ʾ�̬��Ա����
		//score = 80; ��̬��Ա���������Է��ʷǾ�̬��Ա����
		             //�޷����ֵ������ĸ������score����
	}
	static int age;  //��̬��Ա����
	int score;  //�Ǿ�̬
};
int Teacher::age = 0;      //�������������ʼ��
void sub()
{
	Teacher A;
	A.Infm();
	//A.Infm;//ͨ����������
	cout << A.age << endl;
    Teacher::Infm();   //ֱ��ͨ����������
	cout << A.age << endl;
	cout << Teacher::age << endl;
}
int main()
{ 
	sub();	
	system("pause");
	return 0;
}
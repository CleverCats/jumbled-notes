#include<iostream>
using namespace std;

//MyColor���͵�ö��ֵ
enum MyColor
{
	//ö��ֵ,���൱������ֵ����,�����γ���,���ɱ��ı�
	Red=3,   //Ĭ��Ϊ0  �Զ���Ϊ3  �����ö���� +1  
	Green,  //4
	Blue    //5
}/*Ҳ������������ö�������*/;
int main()
{
	//ö��ֵ���Ͷ��� ����ΪMyColor����,���Խ���MyColor���͵�ö��ֵ,���Ｔ���Խ��� Red,Green,Blue,���Ե���һ�����ο���

							//***************���ã��ǳ���ɶ��Ը���,��ö������������******************
	MyColor Color;  
	Color = Red;
	cout << Color << endl;
	//������ֱ�ӽ�����ͨ������,��ΪColorֻ�ܽ���MyColor���͵�ö��ֵ,�����Բ���ǿ������ת��
	//Color = 2000;
	Color = static_cast<MyColor>(2000);
	cout << Color << endl;
	system("PAUSE");
	return 0;
}
#include<iostream>
using namespace std;

//MyColor类型的枚举值
enum MyColor
{
	//枚举值,就相当于整形值看待,是整形常量,不可被改变
	Red=3,   //默认为0  自定义为3  下面的枚举累 +1  
	Green,  //4
	Blue    //5
}/*也可以在这生成枚举类对象*/;
int main()
{
	//枚举值类型对象 类型为MyColor类型,可以接受MyColor类型的枚举值,这里即可以接受 Red,Green,Blue,可以当作一个整形看待

							//***************作用：是程序可读性更高,用枚举名代替数字******************
	MyColor Color;  
	Color = Red;
	cout << Color << endl;
	//不可以直接接收普通的整形,因为Color只能接收MyColor类型的枚举值,但可以采用强制类型转换
	//Color = 2000;
	Color = static_cast<MyColor>(2000);
	cout << Color << endl;
	system("PAUSE");
	return 0;
}
#include<iostream>
using namespace std;
#include<iostream>
#include"circle.h"
using namespace std;
int main()
{
	circle Cir1;
	Cir1.setcenter(10,0); //设置圆心
	Cir1.setcenterR(10); //设置半径
	int x,y;
	cin >> x >> y;  //输入点
	Cir1.judgepoint(x,y); //判断点的位置
	system("PAUSE");
	return 0;
}
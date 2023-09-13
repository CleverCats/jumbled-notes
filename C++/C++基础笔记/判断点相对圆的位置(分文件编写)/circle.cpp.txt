#include"circle.h"
	void circle::setcenter(const int &x, const int &y)//设置圆心
	{
		CenterX = x; CenterY = y;        //circle:: 表示表现circle作用于下的声明
	}
	void circle:: setcenterR(const int &r) //设置半径
	{
		CircleR = r;
	}
	void circle:: judgepoint(const int&x, const int&y) //判断相对位置
	{
		int single1 = pow(x - CenterX, 2) + pow(y - CenterY, 2);
		int single2 = pow(CircleR, 2);
		if (single1 > single2)
		{
			cout << "在圆外" << endl;
		}
		else if (single1 == single2)
		{

			cout << "在圆上" << endl;
		}
		else
		{
			cout << "在圆内" << endl;
		}
	}
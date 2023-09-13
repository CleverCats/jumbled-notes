#pragma once //防止头文件重复包含
#include<iostream>
using namespace std;
class circle
{
public:
	void setcenter(const int&x, const int &y);//设置圆心
	void setcenterR(const int &r);//设置半径
	void judgepoint(const int&x, const int&y); //判断相对位置
private:
	int CenterX,CenterY,CircleR;   //类成员属性
};
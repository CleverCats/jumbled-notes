#pragma once //��ֹͷ�ļ��ظ�����
#include<iostream>
using namespace std;
class circle
{
public:
	void setcenter(const int&x, const int &y);//����Բ��
	void setcenterR(const int &r);//���ð뾶
	void judgepoint(const int&x, const int&y); //�ж����λ��
private:
	int CenterX,CenterY,CircleR;   //���Ա����
};
#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Boss:public Worker
{
public:
	Boss(int id, string name, int depid);  //���������Ϣ
	void ShowInfor();  //��ʼ��������Ϣ
	string Getdeptname();  //��ȡ��λ
};
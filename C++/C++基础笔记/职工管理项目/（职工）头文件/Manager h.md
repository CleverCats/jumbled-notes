#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Manager:public Worker
{
public:
	Manager(int id, string name, int depid);
	void ShowInfor();  //��ʼ��������Ϣ
	string Getdeptname();  //��ȡ��λ
};
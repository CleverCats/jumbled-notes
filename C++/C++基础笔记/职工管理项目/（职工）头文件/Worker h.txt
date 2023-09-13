#pragma once
#include<iostream>
#include<string>
using namespace std;
//抽象职工类
class Worker
{
public:
	virtual void ShowInfor()=0;  //显示职工信息

	virtual string Getdeptname()=0;  //获取岗位
public:
	int m_id;
	string m_name;
	int m_depid;
};

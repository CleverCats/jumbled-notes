#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Boss:public Worker
{
public:
	Boss(int id, string name, int depid);  //构造个人信息
	void ShowInfor();  //初始化个人信息
	string Getdeptname();  //获取岗位
};
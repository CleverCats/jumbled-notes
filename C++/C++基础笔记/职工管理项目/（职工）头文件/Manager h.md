#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Manager:public Worker
{
public:
	Manager(int id, string name, int depid);
	void ShowInfor();  //初始化个人信息
	string Getdeptname();  //获取岗位
};
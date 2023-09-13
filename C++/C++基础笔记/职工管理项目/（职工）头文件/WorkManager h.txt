#pragma once
#include<iostream>
#include"Worker.h"
#define filedata "Person.txt"
using namespace std;
class WorkManager
{
public:
	WorkManager();  //构造: 职工信息初始化

	void ShowMenu(); //菜单显示
	 
	void ExitSystem();  //退出系统
	
	void AddPerson();  //添加成员

	void NewArr(); //读取职工信息到数组

	void save(); //储存数据文件

	void ShowNewArr();  //显示读取到数组中的职员信息

	void Deletedata();  //删除数据

	void FixMember(); //修改职工

	void ClearFile();  //清空数据

	int SearchMember();   //查询数据
	
	int GetSumMember();  //取得数据总数

	void Rank();  //排序
public:
	bool FileEmpty;   //文件是否为空
	int m_EmpoySum;  //职工总数
	Worker**Emp_arr;       //二级指针
};
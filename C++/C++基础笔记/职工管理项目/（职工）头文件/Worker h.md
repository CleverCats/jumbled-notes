#pragma once
#include<iostream>
#include<string>
using namespace std;
//����ְ����
class Worker
{
public:
	virtual void ShowInfor()=0;  //��ʾְ����Ϣ

	virtual string Getdeptname()=0;  //��ȡ��λ
public:
	int m_id;
	string m_name;
	int m_depid;
};

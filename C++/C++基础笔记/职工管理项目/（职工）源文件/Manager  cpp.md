#include"employee.h"
#include"Manager.h"
#include"Worker.h"
//Ա����Ϣ
Manager::Manager(int id, string name, int depid)
{
	this->m_id = id; this->m_name = name; this->m_depid = depid;
}

string Manager::Getdeptname()
{
	return string("����");
}
void Manager::ShowInfor()
{
	cout << "���:" << this->m_id << "\t"
		 << "����:" << this->m_name << "\t"
		 << "ְλ:" << this->Getdeptname() <<"\t"
		 << "ְ��:�·��ϰ�������Ա��" << endl;
}
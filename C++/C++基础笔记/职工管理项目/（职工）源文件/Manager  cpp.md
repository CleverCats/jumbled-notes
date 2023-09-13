#include"employee.h"
#include"Manager.h"
#include"Worker.h"
//员工信息
Manager::Manager(int id, string name, int depid)
{
	this->m_id = id; this->m_name = name; this->m_depid = depid;
}

string Manager::Getdeptname()
{
	return string("经理");
}
void Manager::ShowInfor()
{
	cout << "编号:" << this->m_id << "\t"
		 << "姓名:" << this->m_name << "\t"
		 << "职位:" << this->Getdeptname() <<"\t"
		 << "职责:下发老板的命令给员工" << endl;
}
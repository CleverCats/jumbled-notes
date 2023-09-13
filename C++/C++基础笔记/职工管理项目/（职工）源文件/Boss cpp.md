#include"employee.h"
#include"Worker.h"
#include"Boss.h"
//员工信息
Boss::Boss(int id, string name, int depid)
{
	this->m_id = id; this->m_name = name; this->m_depid = depid;
}

string Boss::Getdeptname()
{
	return string("老板");
}
void Boss::ShowInfor()
{
	cout << "编号:" << this->m_id << "\t"
		 << "姓名:" << this->m_name << "\t"
		 << "职位:" << this->Getdeptname() << "\t"
		 << "职责:管理公司,下发任务给经理" << endl;
}
#include"employee.h"
#include"Worker.h"
#include"Boss.h"
#include"WorkManager.h"
#include"Manager.h"
                     //员工信息
Employee::Employee(int id, string name, int depid)
{
	this->m_id = id; this->m_name = name; this->m_depid = depid;
}

string Employee::Getdeptname()
{
	return string("普通员工");
}
void Employee::ShowInfor()
{
	cout << "编号:" << this->m_id << "\t"
		 << "姓名:" << this->m_name<<"\t"
		 << "职位:" << this->Getdeptname()<< "\t"
		 << "职责:完成经理交代的任务" << endl;
}
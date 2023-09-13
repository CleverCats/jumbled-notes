#include"WorkManager.h"
#include"employee.h"
#include"Boss.h"
#include"Manager.h"
#include<fstream>
#include"Worker.h"
#define filedata "Person.txt"
WorkManager::WorkManager()
{
	ifstream ifs(filedata, ios::in);
	if (!ifs.is_open())         //检测文件是否存在
	{	
		cout << "当前文件状态:nOfiLe" << endl;
		this->m_EmpoySum = 0;   //初始化总数
		this->Emp_arr = NULL;   //置空指针
		this->FileEmpty = true;
		ifs.close();
		return ;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())  //检测是否直接读到了文件尾,也就是空文件
	{
		cout << "当前文件状态:FlieEmPty" << endl;
		this->m_EmpoySum = 0;   //初始化总数
		this->Emp_arr = NULL;   //置空指针
		this->FileEmpty = true;
		ifs.close();
		return;
	}
	else
	{
		int Sum = this->GetSumMember();
		this->m_EmpoySum = Sum;   //初始化总数 不为空
		this->Emp_arr = new Worker*[Sum];  //初始二级指针分配空间大小
		this->NewArr();    //实例化二级指针数组  存取职工数据
		if (Sum != 0)this->FileEmpty = false;
	}
	return;
}

int WorkManager::GetSumMember()   
{
	int SumMember = 0;
	int id; int depid; string name;
	ifstream ifs(filedata, ios::in);
	while (ifs >> id && ifs >> name && ifs >> depid) //注意:此方法遇到空格会被判断为一行,所以用此方法分割
	{ 
		//cout << id << " " << name << " " << depid << endl;
		SumMember++;		        //取得员工人数
	}
	ifs.close();
	return SumMember;
}
void WorkManager::save()
{
	ofstream ofs(filedata, ios::out);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl; return;
	}
	for (int i = 0; i < this->m_EmpoySum; i++)      //储存文件
	{
			ofs << this->Emp_arr[i]->m_id << " "
			    << this->Emp_arr[i]->m_name << " "
			    << this->Emp_arr[i]->m_depid << endl;
	}
	ofs.close();
}
void WorkManager::ShowNewArr()    //显示读取到二级指针数组中的职员信息
{
	if (this->m_EmpoySum > 0)
	{
		for (int index = 0; index < this->m_EmpoySum; index++)
		{
			this->Emp_arr[index]->ShowInfor();
		}
	}
	else
	{
		cout << "数据为空" << endl;
	}
	system("PAUSE");
	system("cls");
}
void WorkManager::NewArr()          //读取数据到二级指针数组
{
	Worker*work=NULL; int index = 0;
	int id; string name; int depid;
	ifstream ifs(filedata, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		return;
	}
	while (ifs >> id && ifs >> name && ifs >> depid)
	{
		if (depid == 1)
		{
			work = new Employee(id, name, depid);
		}
		if (depid == 2)
		{
			work = new Manager(id, name, depid);
		}
		if (depid == 3)
		{
			work = new Boss(id, name, depid);
		}
		this->Emp_arr[index] = work;   //二级指针赋初始值
		index++;
	}
	ifs.close();  //关闭文件
}
void WorkManager::ExitSystem()
{

	cout << "系统即将关闭" << endl;   //关闭系统
	system("PAUSE");
	exit(0);  //关闭系统
}
int WorkManager::SearchMember()
{
	int Sel_id; string Sel_name; int select;
	cout << "请选择查找方式" << endl;
	cout << "1.姓名查找" << endl
		 << "2.编号查找" << endl;
	cout << "选择:"; cin >> select;
	if (select != 1 && select != 2){ system("cls"); return 0; }
	switch (select)
	{
	case 1:
	{
		cout << "对象姓名:";
		cin >> Sel_name; break;
	}
	case 2:
	{
		cout << "对象编号:";
		cin >> Sel_id; break;
	}
	default:{cout << "输入有误" << endl; system("PAUSE"); system("cls"); return 0; }
	}
	for (int index = 0; index < this->m_EmpoySum; index++)
	{
		
		if (select == 2)
		{
			if (this->Emp_arr[index]->m_id == Sel_id)
			{
				cout << "成功查询！" << endl;
				this->Emp_arr[index]->ShowInfor();  //显示信息
				system("PAUSE"); system("cls"); return index;
			}
		}
		else
		{
			if (this->Emp_arr[index]->m_name == Sel_name)
			{
				cout << "成功查询！" << endl;
				this->Emp_arr[index]->ShowInfor();  //显示信息
				system("PAUSE"); system("cls"); return index;
			}
		}
	}
	cout << "查询失败" << endl;
	system("PAUSE"); system("cls"); return -1;   //清理界面
}
//--------------------------------------------------------------------------------------------
void WorkManager::Deletedata()
{
	if (this->m_EmpoySum>0)
	{
		int index = this->SearchMember();
		if (index != 0 && index != -1)
		{
			for (int i = index; i < this->m_EmpoySum-1; i++)
			{
				this->Emp_arr[i] = this->Emp_arr[i + 1];
			}
		}
			this->m_EmpoySum--;//更新删除后的人员数据
			this->save();    //储存数据
			cout << "职工信息已删除" << endl;
			system("CLS");
	}
	else
	{
		cout << "数据为空" << endl; system("PAUSE");  system("cls");
	}
}
//--------------------------------------------------------------------------------------------
void WorkManager::AddPerson()
{
	int AddNum = 0;
	cout << "添加员工数量:"; cin >> AddNum;
	if (AddNum > 0)
	{
		int NewSize = this->m_EmpoySum + AddNum;
		Worker**NewSpace = new Worker*[NewSize];
		if (this->Emp_arr != NULL)      //拷贝数据
		{
			for (int i=0; i < m_EmpoySum; i++)       
			{
				NewSpace[i] = this->Emp_arr[i];
			}
		}
		for (int i = 0; i < AddNum; i++) //增加新数据
		{
			system("cls"); this->ShowMenu();    //清理界面
			int id; string name; int depid;
			cout << "请输入:" << endl
				<< "第" << i+1 << "位员工编号:"; cin >> id;
			cout << "姓名:"; cin >> name;
			cout << "1.普通员工" << endl
				 << "2.经理" << endl
				 << "3.老板" << endl;
			cout << "职位:"; cin >> depid;
			
			Worker*work = NULL;
			switch (depid)
			{
			case 1:
			{
				work = new Employee(id, name, depid); break;
			}
			case 2:
			{
				work = new Manager(id, name, depid); break;
			}
			case 3:
			{
				work = new Boss(id, name, depid); break;
			}
			default:	break;
			}
			//更新指针数组大小
			NewSpace[this->m_EmpoySum + i] = work;
		}
		delete[] this->Emp_arr;  //释放原空间
		Emp_arr = NewSpace;    //指向新空间
		this->m_EmpoySum = NewSize;  //更新成员总数
		this->save();  //储存
		cout << "成功添加" << AddNum << "名新职工" << endl;
		this->FileEmpty = false;    //文件不为空的指示
		system("PAUSE"); system("cls");
		
	}
	else
	{
		cout << "输入有误" << endl; return;
	}
}
void WorkManager::FixMember()
{
	string name; int search; int id; int depid;
	cout << "需要修改者的姓名:"; cin >> name;
	for (int i = 0; i < this->m_EmpoySum; i++)
	{
		if (this->Emp_arr[i]->m_name == name)
		{
			cout << "查询成功" << endl;
			this->Emp_arr[i]->ShowInfor();
			cout << "新的编号:"; cin >> id;
			cout << "新的姓名:"; cin >> name;
			cout << "1.普通员工" << endl
				 << "2.经理" << endl
				 << "3.老板" << endl;
			cout << "新的部门:"; cin >> depid;
			delete this->Emp_arr[i];  //释放原指针
			if (depid == 1)this->Emp_arr[i] = new Employee(id, name, depid);
			if (depid == 2)this->Emp_arr[i] = new Manager(id, name, depid);
			if (depid == 3)this->Emp_arr[i] = new Boss(id, name, depid);
			this->save();  //储存新数据
			cout << "修改成功" << endl; system("PAUSE"); system("cls");
			return;
		}
	}
	cout << "数据不存在" << endl; system("PAUSE"); system("cls");
}
void WorkManager::Rank()         //数据排序
{
	int select;
	cout << "请选择排列方式" << endl;
	cout << "1.升序排列"<<endl
		 << "2.降序排列" << endl;
	cout << "选择:"; cin >> select;
	if (select == 1)
	{
		for (int i = 0; i < this->m_EmpoySum - 1; i++)
		{
			for (int j = 0; j < this->m_EmpoySum - 1 - i; j++)
			{
				if (this->Emp_arr[j]->m_id >= this->Emp_arr[j + 1]->m_id)
				{
					Worker*temp = this->Emp_arr[j];  //换位
					this->Emp_arr[j] = this->Emp_arr[j + 1];
					this->Emp_arr[j + 1] = temp;
				}
			}
		}
		cout << "已完成升序排列" << endl; system("PAUSE"); system("CLS");
	}
	else if (select == 2)
	{

		for (int i = 0; i < this->m_EmpoySum - 1; i++)
		{
			for (int j = 0; j < this->m_EmpoySum - 1 - i; j++)
			{
				if (this->Emp_arr[j]->m_id <= this->Emp_arr[j + 1]->m_id)
				{
					Worker*temp = this->Emp_arr[j];  //换位
					this->Emp_arr[j] = this->Emp_arr[j + 1];
					this->Emp_arr[j + 1] = temp;
				}
			}
		}
		cout << "已完成降序排列" << endl; system("PAUSE"); system("CLS");
	}
	else
	{
		cout << "输入有误" << endl; system("PAUSE"); system("CLS");
	}
	this->save();  //储存排序后的数据
}
void WorkManager::ClearFile()
{
	int select = 0;
	cout << "清空数据:" << endl
		<< "1.确定" << endl
		<< "2.取消" << endl;
	cout << "选择:";	cin >> select;
	if (select == 1)
	{
		ofstream ofs(filedata, ios::trunc);
		ofs.close();  // 重建文件并关闭文件
		this->m_EmpoySum = 0;   //初始化总数
		this->Emp_arr = NULL;   //置空指针
		this->FileEmpty = true;
		cout << "数据以清空" << endl; system("PAUSE"); system("CLS");
	}
	else
	{
		cout << "操作取消" << endl; system("PAUSE"); system("CLS");
	}
}
void WorkManager::ShowMenu()
{
	{
		if (!FileEmpty)cout << "当前职工总数:" << this->m_EmpoySum << endl;
		cout << "                       *********职工管理系统界面*********" << endl;
		cout << "                       ********* 1.退出当前系统**********" << endl;
		cout << "                       ********* 2.添加职工信息 *********" << endl;
		cout << "                       ********* 3.显示职工信息 *********" << endl;
		cout << "                       ********* 4.删除职工信息 *********" << endl;
		cout << "                       ********* 5.修改职工信息 *********" << endl;
		cout << "                       ********* 6.查找职工信息 *********" << endl;
		cout << "                       ********* 7.按照编号排序 *********" << endl;
		cout << "                       ********* 8.清空所有文档 *********" << endl;
		cout << "                       **********************************" << endl;
	}
	return;
}

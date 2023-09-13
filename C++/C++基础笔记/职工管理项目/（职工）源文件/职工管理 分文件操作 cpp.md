
#include"Worker.h"
#include"Boss.h"
#include"WorkManager.h"
#include"employee.h"
using namespace std;
int main()
{
	WorkManager Wor;
		while (true)
		{
			Wor.ShowMenu();
			int select = 0;
			cout << "等待操作..." << endl << "选择:";
			cin >> select;        //用户选择
			switch (select)     //判断
			{
				case 1:
				{
					Wor.ExitSystem(); break;//退出系统
				}
				case 2:
				{
					Wor.AddPerson(); break;  //添加新员工
				}
				case 3:
				{
					Wor.ShowNewArr(); break;  //显示数据
				}
				case 4:
				{
					Wor.Deletedata(); break;  //查询数据
				}
				case 5:
				{ 
					Wor.FixMember(); break;   //修改数据
				}
				case 6:
				{
					Wor.SearchMember(); break;  //查询数据
				}
				case 7:
				{
					Wor.Rank();  break;  //升序排序
				}
				case 8:
				{
					Wor.ClearFile();  //清除数据
				}
				default:
				{
					system("cls"); break;
				}
			}
		}	
		system("PAUSE");
		return 0;
}
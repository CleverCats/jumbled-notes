
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
			cout << "�ȴ�����..." << endl << "ѡ��:";
			cin >> select;        //�û�ѡ��
			switch (select)     //�ж�
			{
				case 1:
				{
					Wor.ExitSystem(); break;//�˳�ϵͳ
				}
				case 2:
				{
					Wor.AddPerson(); break;  //�����Ա��
				}
				case 3:
				{
					Wor.ShowNewArr(); break;  //��ʾ����
				}
				case 4:
				{
					Wor.Deletedata(); break;  //��ѯ����
				}
				case 5:
				{ 
					Wor.FixMember(); break;   //�޸�����
				}
				case 6:
				{
					Wor.SearchMember(); break;  //��ѯ����
				}
				case 7:
				{
					Wor.Rank();  break;  //��������
				}
				case 8:
				{
					Wor.ClearFile();  //�������
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
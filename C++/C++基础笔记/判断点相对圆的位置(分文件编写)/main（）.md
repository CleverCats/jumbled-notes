#include<iostream>
using namespace std;
#include<iostream>
#include"circle.h"
using namespace std;
int main()
{
	circle Cir1;
	Cir1.setcenter(10,0); //����Բ��
	Cir1.setcenterR(10); //���ð뾶
	int x,y;
	cin >> x >> y;  //�����
	Cir1.judgepoint(x,y); //�жϵ��λ��
	system("PAUSE");
	return 0;
}
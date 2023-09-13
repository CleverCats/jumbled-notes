#include<iostream>
using namespace std;
class Base1  //����1
{
public:
	virtual void f1(){ cout << "Base1::f1() Called" << endl; };
	virtual void g1(){ cout << "Base1::g1() Called" << endl; };
};
class Base2  //����2
{
public:
	virtual void f2(){ cout << "Base2:: f2() Called" << endl; };
	virtual void g2(){ cout << "Base2:: g2() Called" << endl; };
};
//�̳�Base1��Base2���麯��ָ��,Derive�а��������麯��ָ��,��ռ���ڴ��ǰ8���ֽڣ�ͬʱ������Ҳ���ڻ��ڸ���������麯����
class Derive :public Base1, public Base2
{
public:
	//��д�����麯��
	virtual void f1(){ cout << "Derive:: f1() Called" << endl; }//��дBase1::f1()
	virtual void g2(){ cout << "Derive:: g2() Called" << endl; }//��дBase2::g2()

	//�Լ���2���麯��
	virtual void m_f(){ cout << "Derive::m_f() Called" << endl; }
	virtual void m_g(){ cout << "Derive::m_g() Called" << endl; }
};
int main()
{
	cout << "sizeof(Derive)="<<sizeof(Derive) << endl;
	//����ָ���������ָ��,ʵ�ֶ�̬
	Base1*bas1 = new Derive;//���౻�����ʼ��,��Ϊ�����������ȫ������,  /*������֤,��̬��ʵ��ʵ������ָ��ƫ��,����Ľ����д�ȷ��*
				//��ʱ��"�ָ�"���������ಿ�ֵ�����,������ʼ������(ע��,��ʱ�麯��ָ���ָ�򲻻ᷢ���ı�,������麯��ָ��ָ����ָ������麯����)
				//����������麯�������า��
	bas1->f1();
	bas1->g1();
	Derive div;
	int*Derive_vptr = (int*)&div;
	//��ȡ����һ��Vptr������һ���麯������׵�ַ)(******************ע��:�౾����麯������ڵ�һ���麯��������(β��λ��)**********************)
	int*vptr = (int*)(*Derive_vptr);
	typedef void(*Func)(void);
	Func De_f1 = (Func)vptr[0];
	Func B1_g1 = (Func)vptr[1];
	Func De_m_f = (Func)vptr[2];
	Func De_m_g = (Func)vptr[3];
	De_f1();
	B1_g1();
	De_m_f();
	De_m_g();
	cout << "----------------------------------------------------" << endl;
	//��ȡ���ڶ���Vptr(���麯������׵�ַ)
	int*Derive_vptr2 = Derive_vptr+1; //ƫ��4���ֽڵ��ڶ���vbtable���׵�ַ
	int*vptr2 = (int*)(*Derive_vptr2);
	Func B2_f2 = (Func)vptr2[0];
	Func De_g2 = (Func)vptr2[1];
	B2_f2();
	De_g2();
	system("PAUSE");
	return 0;
}

/*�ܽ�:������̳���,��������ֱ���������麯��,�������������麯����,�������д�����麯��,��ô�������麯��������������������麯����ֱ���ͬ
  ͬʱ�̳е������麯��ָ��,ռ���ڴ��ǰ�˸��ֽ�,�ֱ�ָ�������麯������׵�ַ() ������static int A[4];static int B[2];(���ƾ�̬��Ա,��ռ�ö����ڴ�,��Ȼ����Ӧ��Ϊ����ָ�����������int)
  ����������麯����;void(*vptr1)()=A; void(*vptr2)()=B;�ֱ�����������麯������׵�ַ���������׵�ַ������,Ҳ�������4���ֽ�
  ÿ���麯������Կ���һ��ָ������(�ҿ���ʹ������ķ�ʽ����)ÿ�������е�Ԫ�ؿ��Կ���Ϊһ������ָ��(���Ե���������),ÿ��ָ���Ӧһ���麯��
  �ڶ�̳���,���౾����麯��������һ���麯������(ͷ��Ϊ�����麯��β��Ϊ�����麯��,������д�����麯�����滻�����麯����λ��),���������һ���麯������4���麯��,�ڶ����麯����ֻ��2���麯��
  ���Եڶ����麯����Ͳ����ڰ������౾����麯��,��Ĭ���¸��麯��������ڶ������е��麯����������ͬ(ͬ��,��д�麯���ᷢ���滻);*/
	   
	   
	   
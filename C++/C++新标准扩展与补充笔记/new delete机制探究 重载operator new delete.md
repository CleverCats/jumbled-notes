#include<iostream>                                  
using namespace std;
class A
{
public:
	A()
	{
		cout << "����" << endl;
	}
	~A()
	{
		cout << "����" << endl;
	}
	static void* operator new(rsize_t size);  //���䵥�������ڴ� size=1
											  //�����������һ��������ڴ�,Ҳ����A�������ڴ�1�ֽ�,��Ϊ����һ������,���Բ���Ҫ����4�ֽڼ���),����������һ�ι��캯��
	static void operator delete(void* p);     //ͬ��1��,���ú����1����������
	static void* operator new[](rsize_t size) //������������ڴ�,ֻ����һ��,һ�η�����3�����������ڴ��С szie=7�����ǵ���������������3�ι��캯��
	{										  //(�����ڳ���3��A����������3���ֽ����������4���ֽ�,��4���ֽ�������¼�����˼�������,�Ա�������ʱ׼ȷ���ö��ٴ�����)
		A*ptr = (A*)malloc(size);
		cout << "return ptr = " << ptr << endl;
		return ptr;
	}
		static void operator delete[](void* p) //ͬ��1��,���ú����3����������
	{
		free(p);
	}
};
void* A::operator new(rsize_t size)
{	
	A*ptr = (A*)malloc(size);
	return ptr;
}
void A::operator delete(void* p)
{
	free(p); 
}
int main()
{
	/*A*ptr = new A();
	delete ptr;*/

	// ::ȫ�ֲ�����,ָ������ϵͳ�� operator new �� operator delete���������Լ���
	/*A*ptr = ::new A();
	::delete ptr;*/

	A*ptr2 = new A[3];
	cout << "receive ptr = " << ptr2 << endl;
	cout << "��¼��������Ķ������ռ���ֽ���(receive ptr - return ptr):  4" << endl;
	delete[]ptr2;
	system("PAUSE");
	return 0;
}
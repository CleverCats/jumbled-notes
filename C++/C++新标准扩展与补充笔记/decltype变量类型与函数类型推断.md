#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class  Container
{
public:
	//decltype:�ƶϱ�������,���д��decltype((����)) ���ƶϳ���������Ϊ���� ����int &�� (����)��ʾһ�����ʽ(ע��*ptr�ǽ����ñ��ʽ) 
	//Ҳ����˵decldype(���ʽ),�ƶϳ�����Ϊ��������,������ʽ�Ǻ���,��ô�ƶϵ�Ϊ ����ֵ���� &
	//����ı��ʽ�������Ϊ��ֵ

	/*int i=10;int &j=i; decltype(j) m = i; m=20; �õ�i=20; */
	//����decltypeҲ��ԭ�ⲻ���Ľ������������Ƶ�����

	//���decltype(������)  type =  (����ֵ����)(�����б�)  ��ʾһ���ɵ��ö��������
	//���decltype(������())  type =  ����ֵ����; decltype(��������/�壩)����,������decltype((����))һ���ƶϳ����� &


	//���淽��,����һ�����������Ͷ���
	//ȱ��������������Ϊconst ������������Ҫ����Ϊ typename T::const_iterator iter;�������������Ҫ����дһ��ƫ�ػ��汾,�ȽϷ���
	//typename T::const_iterator iter;

	//ʹ��C++11�е�decltype �����ƶϽ�������� 
	//�ƶ�T����ʱ�������ʼ����������,�Ӷ������ iterator��const_iterator�ļ�������
	decltype(T().begin()) iter;      
	void Func(T &temp)
	{

		//...
	}
};
class A
{
public:
	A()
	{
		printf("22222222222\n");
		//decltype������ִ�����ŵ�����,ֻ�����ƶ�
	}
	int Fu(){};
};
int Func(){ return 0; };
int main()
{
	using Conter = const std::vector<int>;    //ֻ������
	Conter v1 = { 1, 2, 3, 4 };  //��ʼ������
	Container<Conter>Cer;
	Cer.Func(v1);
	decltype(Func()) f = 10; //type f = int

	//����A()��û��������ʱ����(����û�е����޲ι���)��ֻ�����������ƶ�
	decltype(A().Fu()) m=10;  // Type m = int
	system("PAUSE");
	return 0;
}
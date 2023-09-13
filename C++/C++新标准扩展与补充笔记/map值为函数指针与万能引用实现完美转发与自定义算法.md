#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<functional>
#include<unordered_set>
using namespace std;
void Prefectcall(int &n,int &m);   //��ֵ����
void Prefectcall(int &&n, int &m);  //��ֵ����
template<class Function,class T,class T2>
void TemplateFunTurn(Function f, T &&n, T2 &&m);
void Fun(int i)
{
	cout << i << endl;
}
template<class InputIterator, class Function>
void for_each(InputIterator IterBegin, InputIterator IterEnd, Function Fun,int)  //�Զ���for_each�㷨
{
	for (;IterBegin!=IterEnd;++IterBegin)          //InputIterator ���յ�Ϊ����������
	{                                              //Function ���ܵ�Ϊ����ָ�� ����ָ����ÿ���ʹ�� *ָ��(����) Ҳ����ʹ�� ָ��(����)
		Fun(*IterBegin);
	}
	cout << typeid(Fun).name() << endl;
	cout << typeid(IterBegin).name() << endl;
}
class A
{
public:
	A(){};
	bool operator()(int n,int n1)
	{
		return n > n1;
	}
};
void PutChar(char chr)
{
	cout << chr << endl;
}

//��������,T&& Ϊ��������,������T����,ע:T&& ��������    
template<class T> 
void Fun2(T&& s)          //universal  reference  ��������/δ��������
//const���δʻ�����������õ��ʸ�    void Fun2(const T&& s)  
{
	cout << typeid(T).name() << endl;
	cout << s << endl;
}
void Fun4(int (&p))
{
	cout << p << endl;
}
int main()
{
	//unordered_set<int>my_set = { 2, 4, 8, 6, 10 };
	//auto result = my_set.find(6);
	//cout << typeid(result).name() << endl;   //resultΪ����������
	//cout << *result << endl;      
	//printf("%p\n", result);
	//void(*pf)(int) = Fun;
	//vector<int>v = { 1, 2, 3, 1, 4, 5, 6, 4, 6, 7 };
	//cout << "------------------------------" << endl;
	//
	//sort(v.begin(), v.end(), A());  
	//for_each(v.begin(), v.end(), pf,1);  //���� pf(*v.begin()��*v.end()) Ȼ�� ++v.begin();

	//���ɵ��ж�����ֵ����map,��ͨ��������
	void(*p)(char) = PutChar;
	function<void(char)> f = p;
	map<int, function<void(char)>> m = { { 1, f } };
	m[1 ]('x');  //ͨ��������ֵ(ֵΪ��ģ��function����,�ö����װ�˿ɵ��ö���ָ��,�ö������Ϊ���ö���)
	cout << "---------------------------------------------" << endl;

	//����ģ������������,���Դ�����ֵ,Ҳ���Դ�����ֵ,����ֵ���Ϊ��ֵ����,����ֵ,���Ϊ��ֵ����
	Fun2<int>(10);  //����ֵ
	int i = 10;
	Fun2<int&>(i);    //����ֵ
	//Fun2<int&>(i);    //����ֵ

	//auto&& tmp= Ҳ���������� 

	//ע��:��ģ�����ͨ��Ա�����������������ã���Ϊ��Ա�������������Ƶ�,��ʵ��������ʱ,�Ѿ�ȷ����T������
	//��ģ���ж����ĺ���ģ���Ա��������Ϊ��������


	cout << "-----------------------��������ʵ������ת��------------------------" << endl;
	int m_i = 10; int m_j = 20;
	typedef void(*FUN)(int &, int &);
	typedef void(*FUN2)(int &&, int &);
	FUN  FleftRef = Prefectcall;          // Prefectcall(int &n, int &m)
	FUN2 FRightRef = Prefectcall;         // Prefectcall(int &&n, int &m)
	TemplateFunTurn(FleftRef, m_i, m_j);
	TemplateFunTurn(FRightRef,10,m_j);
	system("pause");
	return 0;
}
void Prefectcall(int &&n, int &m)
{
	cout << "-------------------begin------------------------" << endl;
	cout << "��ֵ���� Prefectcall (int &&n, int m)) ����" << endl;
	cout << "value=  " << n + m << endl;
	cout << "--------------------end-------------------------" << endl;
}
void Prefectcall(int &n, int &m)
{
	cout << "-------------------begin------------------------" << endl;
	cout << "��ֵ���� Prefectcall (int &n, int &m) ����" << endl;
	cout <<"value=  "<< n + m << endl;
	cout << "--------------------end-------------------------" << endl;
}

template<class Function, class T, class T2>
void TemplateFunTurn(Function f, T &&n, T2 &&m)     //�������� T &&n ���Խ�����ֵ������ֵ,���ұ���ʵ�ε�����(����const)
                                                    //��Ϊ��������ֵ������ֵ����,n,m������Ϊ��ֵ,��T�б����n,m��ʵ������(��ֵ/��ֵ)
{
	//std::forward<T>(n) forward<T>(n)�Ὣnת��ΪT��ǵ�����(Ҳ����ʵ��ԭ��������),���ҷ��ظ�ֵ,��������Ϊ�βε���f(����1������2);
	//***************����T=int��ʾʵ��Ϊ��ֵ,T=int &��ʾʵ��Ϊ��ֵ**********************
	//***********std::forword<>����std::forword<int>����������ֵ std::forword<int&>����������ֵ**************
	//�Ӷ��ﵽ���ı�ת��ǰʵ�����͵�Ŀ��,�ﵽ����ת��,���ｫnתΪ��ֵ,m�����ı�,����Ϊ��ֵ,std::move()����������ǿ��תΪ��ֵ
	f(std::forward<T>(n), std::forward<T2>(m));     //����ת������
}

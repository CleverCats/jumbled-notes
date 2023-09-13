#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<functional>
#include<unordered_set>
using namespace std;
void Prefectcall(int &n,int &m);   //左值引用
void Prefectcall(int &&n, int &m);  //右值引用
template<class Function,class T,class T2>
void TemplateFunTurn(Function f, T &&n, T2 &&m);
void Fun(int i)
{
	cout << i << endl;
}
template<class InputIterator, class Function>
void for_each(InputIterator IterBegin, InputIterator IterEnd, Function Fun,int)  //自定义for_each算法
{
	for (;IterBegin!=IterEnd;++IterBegin)          //InputIterator 接收到为迭代器类型
	{                                              //Function 接受到为函数指针 函数指针调用可以使用 *指针(参数) 也可以使用 指针(参数)
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

//万能引用,T&& 为万能引用,单独的T不是,注:T&& 必须相连    
template<class T> 
void Fun2(T&& s)          //universal  reference  万能引用/未定义引用
//const修饰词会剥夺万能引用的资格    void Fun2(const T&& s)  
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
	//cout << typeid(result).name() << endl;   //result为迭代器类型
	//cout << *result << endl;      
	//printf("%p\n", result);
	//void(*pf)(int) = Fun;
	//vector<int>v = { 1, 2, 3, 1, 4, 5, 6, 4, 6, 7 };
	//cout << "------------------------------" << endl;
	//
	//sort(v.begin(), v.end(), A());  
	//for_each(v.begin(), v.end(), pf,1);  //调用 pf(*v.begin()，*v.end()) 然后 ++v.begin();

	//将可调研对象作值传入map,可通过键调用
	void(*p)(char) = PutChar;
	function<void(char)> f = p;
	map<int, function<void(char)>> m = { { 1, f } };
	m[1 ]('x');  //通过键调用值(值为类模板function对象,该对象封装了可调用对象指针,该对象可作为调用对象)
	cout << "---------------------------------------------" << endl;

	//函数模板做万能引用,可以传递左值,也可以传递右值,传左值则变为左值引用,传右值,则变为右值引用
	Fun2<int>(10);  //传右值
	int i = 10;
	Fun2<int&>(i);    //传左值
	//Fun2<int&>(i);    //传左值

	//auto&& tmp= 也是万能引用 

	//注意:类模板的普通成员函数不能做万能引用，因为成员函数不做类型推导,在实例化对象时,已经确定了T的类型
	//类模板中独立的函数模板成员函数可作为万能引用


	cout << "-----------------------万能引用实现完美转发------------------------" << endl;
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
	cout << "右值引用 Prefectcall (int &&n, int m)) 调用" << endl;
	cout << "value=  " << n + m << endl;
	cout << "--------------------end-------------------------" << endl;
}
void Prefectcall(int &n, int &m)
{
	cout << "-------------------begin------------------------" << endl;
	cout << "左值引用 Prefectcall (int &n, int &m) 调用" << endl;
	cout <<"value=  "<< n + m << endl;
	cout << "--------------------end-------------------------" << endl;
}

template<class Function, class T, class T2>
void TemplateFunTurn(Function f, T &&n, T2 &&m)     //万能引用 T &&n 可以接受左值或者右值,并且保留实参的属性(例如const)
                                                    //因为不管是左值还是右值引用,n,m都将成为左值,但T中标记了n,m的实参类型(左值/右值)
{
	//std::forward<T>(n) forward<T>(n)会将n转化为T标记的类型(也就是实参原本的类型),并且返回改值,在这里作为形参调用f(参数1，参数2);
	//***************这里T=int表示实参为右值,T=int &表示实参为右值**********************
	//***********std::forword<>规则std::forword<int>返回整形右值 std::forword<int&>返回整形左值**************
	//从而达到不改变转发前实参类型的目的,达到完美转发,这里将n转为右值,m不做改变,还是为左值,std::move()则是无条件强制转为右值
	f(std::forward<T>(n), std::forward<T2>(m));     //完美转发调用
}

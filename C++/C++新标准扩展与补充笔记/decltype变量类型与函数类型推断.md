#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class  Container
{
public:
	//decltype:推断变量类型,如果写成decltype((变量)) 则推断出来的类型为引用 例如int &， (变量)表示一个表达式(注意*ptr是解引用表达式) 
	//也就是说decldype(表达式),推断出来的为引用类型,如果表达式是函数,那么推断的为 返回值类型 &
	//这里的表达式必须可以为左值

	/*int i=10;int &j=i; decltype(j) m = i; m=20; 得到i=20; */
	//所以decltype也会原封不动的将变量的类型推导出来

	//如果decltype(函数名)  type =  (返回值类型)(参数列表)  表示一个可调用对象的类型
	//如果decltype(函数名())  type =  返回值类型; decltype(（函数名/体）)无用,不会像decltype((变量))一样推断出引用 &


	//常规方法,声明一个迭代器类型对象
	//缺点如果传入的容器为const 迭代器类型需要声明为 typename T::const_iterator iter;即解决该问题需要额外写一个偏特化版本,比较繁琐
	//typename T::const_iterator iter;

	//使用C++11中的decltype 类型推断解决该问题 
	//推断T的临时对象的起始迭代器类型,从而灵活解决 iterator与const_iterator的兼容问题
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
		//decltype并不会执行括号的内容,只是做推断
	}
	int Fu(){};
};
int Func(){ return 0; };
int main()
{
	using Conter = const std::vector<int>;    //只读容器
	Conter v1 = { 1, 2, 3, 4 };  //初始化容器
	Container<Conter>Cer;
	Cer.Func(v1);
	decltype(Func()) f = 10; //type f = int

	//这里A()并没有生成临时对象(测试没有调用无参构造)，只是做了类型推断
	decltype(A().Fu()) m=10;  // Type m = int
	system("PAUSE");
	return 0;
}
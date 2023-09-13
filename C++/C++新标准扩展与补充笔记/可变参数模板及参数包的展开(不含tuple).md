#include<iostream>
#include<string>
using namespace std;

//可变参函数模板(递归调用)
namespace VarianceFunc    //命名空间
{

	void Variance()					//参数包终止函数,当args...参数包中不存在参数时,会调用该重载函数
	{
		cout << "参数包展开完毕" << endl;
	}
	template<typename T, typename...T2>             //T 类的参数作用:  提取 typename...声明 T2 (代表T2为类型参数包接受的各种类)  参数包接收的各种参数 
	void Variance(const T& firstarg, T2...args)     //注意: 这里 T2 代表 0-任意个 相同或者各不相同不同 参数类型而不是一个参数类型 ,args ... 代表 0-任意个参数 而不是一个参数  
	{                 /*一包类型 一包形参*/
		cout << "参数包 : " << sizeof...(T2) << endl;    //等同于 sizeof...(T/args)  获得参数包中参数数量,或者T的数量
		cout << "展开参数包: " << firstarg << endl;
		//if (sizeof...(T2) == 1) return;
		Variance(args...);          //递归调用传输参数包,参数包中的第一个参数会传输给firstarg  其他参数会传入 ...args  导致参数包数量递减,直至为空后调用终止函数,打断递归

	}
}          
//可变参类模板(递归继承)
namespace VarianceClass
{
	
	template<typename...args> class A{};			 //泛化模板,这里仅仅用来形成特例化类模板(存在特例化与泛化都可以构建/调用时,优先会选择特例化,所以会进行特例化类模板的自我递归继承
	template<typename firstarg, typename...otherargs>//祖父辈模板的特例化  将类型参数包 args  拆分为 firtsargs 和剩下的 otherargs 两部分的类型参数
	class A <firstarg, otherargs...> :private A<otherargs...>   //递归继承,每次继承将参数包中除第一个参数的其他参数传入父辈
																//机制:当构造该特例化类模板的对象时,调用该特例化模板,这时发现该模板存在私有继承父类
																//然后通过模板参数列表  A<otherargs...> 确定了父类的类模板类型,进而开始先构造该父类
	                                                            //然而父类也就是特例化类模板本身,将传来的参数包又再一次做了拆分,再次继承.再次拆分,直至参数包为空 < >
																//参数包为空的父类不存在,于是终止继承(因为class A <firstarg, otherargs...> 只是需要指定一个参数类型 )
	{															//然而也可以自己特例化也可空模板参数的类模板,进行操作
	public:
		A(firstarg val, otherargs... val2) :m_val(val), A<otherargs...>(val2...)     //引用展开.防止拷贝
			                               //可以通过成员函数接收展开的参数包   
										   //A<otherargs...>(val2...)初始化列表构造父类,确定父类类模板的参数类型 并且 传入参数包val2...进行构造
		{            
			printf("构造调用 A::A() this= %p\n", this);
			cout << "m_val= " << m_val << endl;
		}
	private:
		firstarg m_val;
	};
	template<> class A <>
	{
	public:
		A()
		{
			printf("空类模板构造 A::A() this= %p\n", this);
			cout << "template<> class A <> 为祖父类" << endl;
		}

	};
}
int main()
{
	using namespace VarianceFunc;
	using namespace VarianceClass;
	cout <<"-----------------递归类继承调用展开参数包--------------------------------" << endl;
	A<int,char*,char*,char>obj(10,"hellow", "Word", '6');   //参数包的传参数数量为0-任意个
	cout <<"--------------------------结束继承---------------------------------------" << endl;

	cout<<"-------------------递归函数调用展开参数包--------------------------------" << endl;
	Variance(1, 2.0, 3, "HELLOW", 'A', 5.5f);				//参数包的传参数数量为0-任意个
	cout <<"--------------------------结束调用---------------------------------------" << endl;
	system("PAUSE");
	return 0;
}
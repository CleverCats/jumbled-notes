#include<iostream>
#include<string>
#include<tuple>
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

	template<typename...args> class A			 //泛化模板,这里用来形成特例化类模板(存在特例化与泛化都可以构建/调用时,优先会选择特例化,所以会进行特例化的自我递归继承
	{
		/*public:                                    //可以当作一个祖父类的空模板,被继承,用来终止递归继承;
		A()
		{
		printf("空类模板构造 A::A() this= %p\n", this);
		cout << "template<> class A <> 为祖父类" << endl;
		}*/
	};
	template<typename firstarg, typename...otherargs>	//祖父辈模板的特例化  将类型参数包 args  拆分为 firtsargs 和剩下的 otherargs 两部分的类型参数
	class A <firstarg, otherargs...> :private A<otherargs...>   //递归继承,每次继承将参数包中除第一个参数的其他参数传入父辈
		//机制:当构造该特例化类模板的对象时,调用该特例化模板,这时发现该模板存在私有继承父类
		//然后通过模板参数列表  A<otherargs...> 确定了父类的类模板类型,进而开始先构造该父类
		//然而父类也就是特例化类模板本身,将传来的参数包又再一次做了拆分,再次继承.再次拆分,直至参数包为空 < >
		//祖父类为可变参泛化模板可以作为参数包为空的模板,于是继承后终止继承(因为class A <firstarg, otherargs...> 至少需要指定一个参数类型 )
	{										//也可以自己特例化也空模板参数的类模板,进行操作
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
	template<> class A <>   //特例化空类模板,作为祖父模板被继承,也可以直接写在泛化类模板中,因为泛化可变参数类模板也可以传入空参数,与该特例化达到同样效果                      
	{                       //如果写了该特例化空模板,那么就会优先调用该特例化版本
	public:
		A()
		{
			printf("空类模板构造 A::A() this= %p\n", this);
			cout << "template<> class A <> 为祖父类" << endl;
		}

	};
}
//可变参数模板(递归组合(类对象相互包含))
namespace VarianceComboClass
{
	//与可变参类模板(递归继承)区别的区别:  
	//递归继承：　一个对象的构造建,导致不断去寻找父类,重而达到递归继承,每次父类的参数包参数数量减一
	//递归组合:   一个对象构造时构造该对象的类成员函数，类成员函数构造时,构建该类成员函数的类成员函数,达到递归构建,每次构建传递的参数包参数数量减一
	//直到参数包为0,调用可变参数泛化类模板进行构造

	template<typename...args> class B
	{
	public:
		B()
		{
			printf("空类模板构造 B::B() this = %p\n");
		}
	};
	template<typename firstarg, typename...otherargs>
	class B <firstarg, otherargs...>

	{
	public:
		B(firstarg val, otherargs...val2) :m_val(val), obj(val2...)  //初始化列表构造类成员对象,该类成员构建时,构建的是该特例化可变参模板
			//所以会把参数包 otherargs... 拆分为 firstarg val, otherargs... val2 
			//然后再次构造类成员,进而再次拆分,直到参数包为空,调用可变参泛化版本(空参版本),或者额外特例化的空参版本
		{
			printf("构造调用 B::B() this= %p\n", this);
			cout << "m_val= " << m_val << endl;
		}
	private:
		firstarg m_val;
		B<otherargs...> obj;        //机制:构建时发生obj包含B<otherargs...> obj,进而再次构建obj,直到找到不含类成员对象的成员类模板,然后依次构建该对象
		//这时候的构造obj其实是想构造泛化类,但因为泛化和特化都适合,所以优先构造特化
	};

}
//通过tuple(元组)递归调用static静态成员函数展开参数包
namespace VarianceTupleClass
{
	template<int mycount, int maxcount, typename...T>
	class C
	{
	public:
		static void Func(const tuple<T...>& tub)
		{
			cout << "tuple静态成员 展开参数  value= " << get<mycount>(tub) << endl;
			C<mycount + 1, maxcount, T...>::Func(tub);
		}
	};
	//当mycount==maxcount时调用特例化类结束递归调用类静态成员
	template<int maxcount, typename...T>
	class C<maxcount, maxcount, T...>
	{
	public:
		static void Func(const tuple<T...>& tub)
		{
			cout << "以通过tuple(元组)完全展开参数包" << endl;
		}
	};
	template<typename...T>
	void FunStartCall(const tuple<T...>&tub)
	{
		//传入起始展开位置,和参数包总数
		C<0, sizeof...(T), T...>::Func(tub);  //开始调用
	}
	template<typename...T>
	void FunSentTuple(T...args)             //接收参数
	{
		std::tuple<T...>mytuple(args...);
		FunStartCall<T...>(mytuple);
	}
}

int main()
{
	using namespace VarianceFunc;
	using namespace VarianceClass;
	using namespace VarianceComboClass;
	using namespace VarianceTupleClass;
	cout << "-----------------递归类继承调用展开参数包--------------------------------" << endl;
	A<int, char*, char*, char>obj(10, "hellow", "Word", '6');   //参数包的传参数数量为0-任意个
	cout << "--------------------------结束继承---------------------------------------" << endl;

	cout << "-------------------递归函数调用展开参数包--------------------------------" << endl;
	Variance(1, 2.0, 3, "HELLOW", 'A', 5.5f);
	cout << "--------------------------结束调用---------------------------------------" << endl;

	cout << "-------------递归类组合构建类对象展开参数包-----------------------------" << endl;
	B<int, char*, char*>m_obj(10, "hellow", "Word");
	cout << "------------------------结束组合----------------------------------------" << endl;

	cout << "-------------------tuple(元祖递归成员函数展开)--------------------------" << endl;
	FunSentTuple("Hellow world", 'A', 1.5, 2008);
	cout << "-----------------------结束tuple展开------------------------------------" << endl;
	system("PAUSE");
	return 0;
}
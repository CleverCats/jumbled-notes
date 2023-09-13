/*1，unique_ptr的数组智能指针，没有*和->操作，但支持下标操作[]

2，shared_ptr的数组智能指针，有*和->操作，但不支持下标操作[]，只能通过get()去访问数组的元素。

3，shared_ptr的数组智能指针，必须要自定义deleter 或者使用自定义删除器 也可以使用 default_delete可调用类模板
————————————————*/


#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;
template<typename T>
void DeletePtr(T* ptr);  //函数模板声明.用作自定义删除器 在底部实现
template<typename T>     //函数模板声明,用作生成指定的shared_ptr智能指针,并return回去
shared_ptr<T> make_shared_ptr(size_t size);  //size_t相当于无符号整形 0 - number
template<typename T>
T Fptr(T& ptr)   //引用接受,strong ref计数不变
{
	return ptr;  //参数临时对象 strong ref计数加一
}
int main()
{
	//shared_ptr类型智能指针允许被拷贝,每多一个该类型的指针拷贝(也就是说引用接收不会改变)
	//智能指针模板类部便会有 strong ref(用于计算存在几个指向同一块内存的该类型指针的值) 加一

	//每当少一个该类型的指针拷贝，strong ref 便会 加一 ,若为0时,则会调用该类模板的析构函数,释放这块指针指向内存
	shared_ptr<int>p3(new int(10));
	//make_shared<int>内模板可以取代new 且更安全
	shared_ptr<int> p=make_shared<int>(10);
	auto ptr(p);    //拷贝智能指针
	Fptr(p);
	//1.
	int count = p.use_count();       //成员函数,use_cout()返回 strong ref 当前数量
	cout << "strong ref = "<<count << endl;
	//2.
	if (p.unique() == true)  //成员函数 unique() 判断是否有多个拷贝shared_ptr地址指向同一块内存,即 strong ref = 1 存在返回false   strong ref =0 或者 >1返回false
	{
		cout << "当前 strong ref = 1 指针被独占" << endl;
	}
	else
	{
		cout << "当前 strong ref >1 指针存在被拷贝,内存存在共享" << endl;
	}
	//3.
	//成员函数reset(重置 / 初始化) 智能指针
	//reset()不带参时
	//p.reset();        // 若 strong ref = 1（=0时啥也不干） 则释放指针指向内存并且置空
					  // 若 strong ref >1 则 将 该指针置空(共享者减一) (***不释放***)  然后 strong ref 减一,
	//带参时
	p.reset(new int(2020));        //若  strong ref = 1 则释放该智能指针指向对象 ,让智能指针指向等于 20020 ,即使智能指针接收 new出来的指针
	                                //若   strong ref >1 则不释放该指针指向对象, 然后使该副本指针指向  20020,此时 strong ref  减一
	//4.解*
	cout << *p << endl;         //像普通指针一样解*但是注意不能直接delete p,需要在默认删除器或者自定义删除器中delete p;
	
	//5.成员函数get()
	int *m_p = p.get();        //将指针指针保存的裸指针获取出来(智能指针仍然保存的有)(注意不要delete该指针,指针的释放还是由智能指针管理)
	                           //使用情况:有些函数的内置参数需要普通裸指针而不可以是智能指针的情况使用 此处m_p相当于裸指针
	//6.std::swap()交换指针
	shared_ptr<string>pt1(new string("HELLOW"));
	shared_ptr<string>pt2(new string("HI"));
	std::swap(pt1, pt2);     //交换指针

	//7.=nullptr
	auto pt3(pt1);
	pt3 = nullptr;    //置空pt3且使  strong ref减一  如果pt3没有其他任何拷贝副本, strong ref -1  =0 也就释放了指针指向的内存 

	//8.智能指针名字作为是否为空 判断条件 if(ptr1!=nullptr) {} else {};

	//9.自定义指针删除器,取代智能指针的缺省删除器(可以用来打印一些日志(自己想做的操作)),当strong ref=0时,就会调用参数二的可调用对象
	//******注意: shared_ptr<string>pt4=make_shared<string>("I love china");这种方式不可以指定自定义删除器******

	//使用情况:因为shared_ptr中的默认删除器中的delete没有delete[]的版本,因此不能释放数组指针
	shared_ptr<string>pt4(new string("HI"),DeletePtr<string>);  //参数二为可调用对象,作为自定义删除器
	//因为是可调用对象,所以参数二也可以是lambda表达式
	shared_ptr<string>pt5(new string("I am a good boy"), [](string* p5)
	{
		cout << "Lambda作为自定义删除器 delete 指针" << endl;
		delete p5;  //Lambda表达式可调用对象作为自定义删除器
	});
	pt5.reset();
	pt4.reset();

	//10.使用std:;default_delete类模板做删除器，内部重载了(),因此可以作为可调用对象
	//同时它也支持数组类指针的视频
	shared_ptr<string>pt6(new string("你好啊"),std::default_delete<string>());
	//只需要在类模板实参列表中传入string[]就能识别string类型指针数组进行delete
	shared_ptr<string>pt7(new string[10], std::default_delete<string[]>());

	//11.C++17中可以不在依赖自定义删除器或者std::default_delete<string>对数组指针进行delete、
	//C++17中  shared_ptr增加了opreator[]，并可以使用int[]类的数组类型做模板参数
	//只需要在智能指针类模板的模板参数列表显示声明 int[]的数组类型就可以进行delete[]的操作
	//shared_ptr<int[]> pt8(new int[10]);   
	//pt8[0] = 10; pt8[1]=9; 在C++17中可以使用  在C++11 则只能使用 pt8.get()[index]  get()返回数组首地址,可以当数组名使用,进而可以使用[]
	//总结:  不建议使用,标准过新

	//12.使用封装好的函数模板来生成智能指针
	shared_ptr<int>pt9 = make_shared_ptr<int>(4);//也可以使用auto接收
	auto pt10 = make_shared_ptr<string>(3);
	string StrArray = "ABC";
	for (int i = 0; i < 3; i++)  //使用赋值初始化
	{
		// get()返回数组首地址,可以当数组名使用,进而可以使用[]
		pt10.get()[i] = StrArray[i];
		cout << pt10.get()[i] << endl;
	}
	system("pause");
	return 0;
}
//指定删除器额外说明: 
//就算两个shared_ptr指定了不同的删除器,只要他们指向的对象类型相同,那么这两个shared_ptr也属于同一种类型,这和unique_ptr不同
//因为属于同一种类型,所以两者直接可以进行 = 这种赋值运算
template<typename T>
void DeletePtr(T* ptr)
{
	//........打印日志
	cout << "可调用函数作为自定义删除器 delete 指针" << endl;
	delete ptr;
}
template<typename T>     //函数模板声明,用作生成指定的shared_ptr智能指针,并return回去
shared_ptr<T> make_shared_ptr(size_t size)  //size_t相当于无符号整形 0 - number
{
	return shared_ptr<T>(new T[size], std::default_delete<T[]>());  //返回生成的匿名智能指针,在主函数中接收
}
#include<iostream>
#include<memory>
using namespace std;
class A:public enable_shared_from_this<A>   //继承标准库中的类模板  enable_shared_from_this ,以便调用其成员函数  shared_from_this() 成功返回this指针
{
public:
	//陷阱一:
	shared_ptr<A> Func()
	{	
		cout << " this adress=" << this << endl;

		//使用this裸指针再次初始化shared_ptr  ( this = new A )
		//strong ref = 1，导致多个智能指针指向同一块内存,但是strong ref 却等于 1
		//return shared_ptr<A>(this);;

		//应该使用 shared_from_this()
		return shared_from_this();   //返回this智能指针
		//原理: enable_shared_from_this 中有一个弱指针 week_ptr 监视 this指针,调用成员函数 shared_from_this()
		//实际上是 这个成员函数的返回值是  week_ptr 的 lock()函数被调用所返回的智能指针 即实际上 week_ptr<A>pw = ptr; 一直监视该智能指针,此时调用lock()返回该只能指针的副本
		//从而实现strong ref + 1,避免同一个裸指针多次被指针指针封装却强引用计数=1的情况
	}
};
//陷阱二:
class C; //声明
class B
{
public:
	shared_ptr<C>c_ptr;  //B类对象包含有封装C类指针的智能指针,作为成员变量
};
class C
{
public:
	//shared_ptr<B>b_ptr; //C类对象包含有封装B类指针的智能指针, 作为成员变量
	//解决方法:将其中一个成员变量改为week_ptr 不会导致strong ref增加,这样在当B类的智能neg指针strong ref仅为1 得到释放后,B对象被释放,成员变量shared_ptr<C>c_ptr;也得到一次释放
	//C类智能neg指针从而减 1 ,还剩 1 当B类对象销毁时,strong ref再次减 1 对象销毁成功, 若A类智能指针先销毁,A类 strong ref - 1同样可以达到相同效果
	weak_ptr<B>b_weekptr;
};
int main()
{
	//警告:不要将同一个裸指针,同时初始化多个智能指针,会导致多个智能指针指向同一块内存,但是strong ref 却等于 1


	//使用裸指针初始化 shared_ptr
	//strong ref = 1
	shared_ptr<A>ptr(new A);

	//shared_ptr<A>ptr2=ptr->Func();    
	//strong ref 仍然 = 1,因为返回的是一个被同一个裸指针初始化的智能指针,而不是智能指针的拷贝 

	//结果:会导致相同内存二次释放

	//采用shared_from_this()后Func()返回的是 shared_ptr<A>ptr(new A); 的副本(由week_ptr的lock()获取的)
	shared_ptr<A>ptr2 = ptr->Func();

	shared_ptr<B>ptr3(new B);
	//new B初始化智能指针对象ptr3 此时ptr3中 强引用=1
	shared_ptr<C>ptr4(new C);
	//new C初始化智能指针对象ptr4 此时ptr4中 强引用=1

	//骚操作开始了:
	ptr3->c_ptr = ptr4;   //c_ptr 为 shared_ptr<C>c_ptr; 作为*ptr3的成员变量,此时   ptr4中 强引用 = 2
	//ptr4->b_ptr = ptr3;	  //b_ptr 为 shared_ptr<B>b_ptr; 作为*ptr4的成员变量,此时   ptr3中 强引用 = 2

	//此时存在两个强引用,程序结束只能释放个,然后强引用还剩1,成员变量不能得到释放.当结束程序时,只会销毁 shared_ptr<B>ptr3(new B);与 shared_ptr<C>ptr4(new C); 生成的ptr3与ptr4
	//强引用减1 但因为还剩1 所以对象内存不会被释放,导致内存泄漏

	//解决:
	ptr4->b_weekptr = ptr3;  //ptr4->b_weekptr为弱引用接收  shared_ptr<B>ptr3
	system("PAUSE");
	return 0;
}
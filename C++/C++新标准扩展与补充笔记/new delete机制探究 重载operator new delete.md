#include<iostream>                                  
using namespace std;
class A
{
public:
	A()
	{
		cout << "构造" << endl;
	}
	~A()
	{
		cout << "析构" << endl;
	}
	static void* operator new(rsize_t size);  //分配单个对象内存 size=1
											  //这里仅仅分配一个对象的内存,也就是A类对象的内存1字节,因为仅有一个对象,所以不需要分配4字节计数),调用完后调用一次构造函数
	static void operator delete(void* p);     //同上1次,调用后调用1次析构函数
	static void* operator new[](rsize_t size) //分配对象数组内存,只调用一次,一次分配完3个对象所需内存大小 szie=7，但是调用完后会连续调用3次构造函数
	{										  //(这里在除了3个A类对象所需的3个字节外会额外分配4个字节,这4个字节用来记录创建了几个对象,以便在析构时准确调用多少次析构)
		A*ptr = (A*)malloc(size);
		cout << "return ptr = " << ptr << endl;
		return ptr;
	}
		static void operator delete[](void* p) //同上1次,调用后调用3次析构函数
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

	// ::全局操作符,指定调用系统的 operator new 和 operator delete，不调用自己的
	/*A*ptr = ::new A();
	::delete ptr;*/

	A*ptr2 = new A[3];
	cout << "receive ptr = " << ptr2 << endl;
	cout << "记录数组包含的对象个数占用字节数(receive ptr - return ptr):  4" << endl;
	delete[]ptr2;
	system("PAUSE");
	return 0;
}
#include<iostream>
using namespace std;
class Base
{
public:
	Base()
	{
		//因为vptr的指向会在执行构造函数体之前被指定到虚函数表(相当于在初始化列表中）
		//这里的memset函数使vptr被清为0x000000;导致无法通过vptr在vtable中寻址
		memset(this, 0, sizeof(Base)); 
		/*void *memset(void *s, int ch, size_t n);
		函数解释:将s中当前位置后面的n个字节 (typedef unsigned int size_t )用 ch 替换并返回 s*/
	}
	virtual void f(){ cout << "Base f() Called" << endl; }
	virtual void g(){ cout << "Base g() Called" << endl; }
	void h(){ cout << "Base h() Called" << endl; }
	virtual~Base(){ cout << "Base ~Base() Called" << endl; };
};
int main()
{
	Base bas;
	bas.f();//静态联编.当不采用new生成对象时,成员函数的地址在编译阶段就被记录下来
//(正常调用)当调用base.f()时,执行 call  Base::f (01081339h)  这里01081339h直接通过函数地址调用该函数（无论是虚函数还是普通函数）
			//而不是通过虚函数指针,找到虚函数表中该虚函数的地址,在通过此地址调用指定虚函数.这里直接跳过了通过虚函数指针中转的步骤


																				    /*静态联编下的虚函数调用(反汇编代码)*/
																				    /*00D461EF	     lea  ecx, [bas]
														 						      00D461F2		 call   Base::f(0D4133Eh)*/
																				    /*未通过vptr中转到vtable虚函数表寻址后调用而是直接通过地址调用*/
	/*------------------------验证------------------------*/
	int*bas_this = (int*)(&bas);
	//提取出vptr
	int*bas_vptr = (int*)(*bas_this);  //可以预见vptr=0x000000
	printf("bas_vptr= %p\n", bas_vptr);
	//bas_vptr[0];无法在vtable寻址
	//(无效调用)
	/*------------------------结束(结论正确vptr=0x000000)---------------------------*/
	Base*bas2 = new Base; //动态联编.采用new生成对象时,成员函数地址虽然也会在编译时确定下来,调用普通函数时同上相同,但是在调用虚函数时会通过vptr在虚函数表中寻找虚函数地址
	                      //然后通过寻找到的虚函数地址调用对应的虚函数;所以如果在构造函数中使用memset(this, 0, sizeof(Base));会导致vptr=0x00000导致无法寻找到虚函数表
	/*-----------vptr=0x00000导致无法通过vptr寻找vtable------------*/
	bas2->h();//正常调用
	//bas2->f();//通过虚函数指针中转到虚函数表寻址后调用 因vptr==0x000000所以出错 
	//delete bas2;//同理delete在动态联编下也对通过vptr在vtable中寻虚析构地址进行调用,因而出错
																							 /*动态联编下的虚函数调用(反汇编代码)*/
																					/*00AA6265  mov         edx,dword ptr [eax]  
																					00AA6267  mov         esi,esp  
																					00AA6269  mov         ecx,dword ptr [bas2]  
																					00AA626C  mov         eax,dword ptr [edx]  
																					00AA626E  call        eax  
																					00AA6270  cmp         esi,esp  
																					00AA6272  call        __RTC_CheckEsp (0AA134Dh)  */
																					//以上代码即为内部实现通过vptr在vtable寻址调用的过程
	//除此之外,用引用的方式接收对象,使用引用的类型的对象调用虚函数也会通过vptr在vtable寻址
	/*--------------------验证-------------------------*/
	Base bas3;
	bas3.f(); //正常调用
	Base &bas4 = bas3;
	//bas4.f();  //error说明引用也会实现vptr在vtable寻址(多态的表现形式)     
	/*通过空指针vptr寻址*/																/*引用对象实现的虚函数调用(反汇编代码)*/
																					/*00EA6278  mov         edx, dword ptr[eax]
																					00EA627A  mov         esi, esp
																					00EA627C  mov         ecx, dword ptr[bas4]
																					00EA627F  mov         eax, dword ptr[edx]
																					00EA6281  call        eax
																					00EA6283  cmp         esi, esp
																					00EA6285  call        __RTC_CheckEsp(0EA134Dh)*/
																					//以上代码即为内部实现通过vptr在vtable寻址调用的过程
	/*------------------验证正确-----------------------*/
														
																	/*总结:虚函数,多态这种概念实际是是专门为指针,引用服务的
																		   多态的表现形式即通过vptr在vtable寻址*/	

	/* 1.静态联编
静态联编是指联编工作在编译阶段完成的，这种联编过程是在程序运行之前完成的，又称为早期联编。
要实现静态联编，在编译阶段就必须确定程序中的操作调用（如函数调用）与执行该操作代码间的关系，
确定这种关系称为束定，在编译时的束定称为静态束定。静态联编对函数的选择是基于指向对象的指针或者引用的类型。其优点是效率高，但灵活性差。*
	2. 动态联编
动态联编是指联编在程序运行时动态地进行，根据当时的情况来确定调用哪个同名函数，实际上是在运行时虚函数的实现。
这种联编又称为晚期联编，或动态束定。动态联编对成员函数的选择是基于对象的类型，针对不同的对象类型将做出不同的编译结果。
C++中一般情况下的联编是静态联编，但是当涉及到多态性和虚函数时应该使用动态联编。动态联编的优点是灵活性强，但效率低。
动态联编规定，只能通过指向基类的指针或基类对象的引用来调用虚函数，其格式为：指向基类的指针变量名->虚函数名（实参表）或基类对象的引用名.虚函数名（实参表）*/
	system("PAUSE");
	return 0;
}
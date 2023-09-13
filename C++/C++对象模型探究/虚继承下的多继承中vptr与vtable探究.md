#include<iostream>
using namespace std;
class Base1  //基类1
{
public:
	virtual void f1(){ cout << "Base1::f1() Called" << endl; };
	virtual void g1(){ cout << "Base1::g1() Called" << endl; };
};
class Base2  //基类2
{
public:
	virtual void f2(){ cout << "Base2:: f2() Called" << endl; };
	virtual void g2(){ cout << "Base2:: g2() Called" << endl; };
};
//继承Base1与Base2的虚函数指针,Derive中包含两个虚函数指针,共占据内存的前8个字节，同时该类中也存在基于该类的两个虚函数表
class Derive :public Base1, public Base2
{
public:
	//重写部分虚函数
	virtual void f1(){ cout << "Derive:: f1() Called" << endl; }//重写Base1::f1()
	virtual void g2(){ cout << "Derive:: g2() Called" << endl; }//重写Base2::g2()

	//自己的2个虚函数
	virtual void m_f(){ cout << "Derive::m_f() Called" << endl; }
	virtual void m_g(){ cout << "Derive::m_g() Called" << endl; }
};
int main()
{
	cout << "sizeof(Derive)="<<sizeof(Derive) << endl;
	//父类指针接收子类指针,实现多态
	Base1*bas1 = new Derive;//父类被子类初始化,因为子类包含父类全部属性,  /*最新验证,多态的实现实际上是指针偏移,这里的结论有待确定*
				//此时会"分割"出包含父类部分的属性,用来初始化父类(注意,此时虚函数指针的指向不会发生改变,父类的虚函数指针指向还是指向父类的虚函数表)
				//不过父类的虚函数表被子类覆盖
	bas1->f1();
	bas1->g1();
	Derive div;
	int*Derive_vptr = (int*)&div;
	//提取出第一个Vptr（即第一个虚函数表的首地址)(******************注意:类本身的虚函数会放在第一个虚函数表里面(尾部位置)**********************)
	int*vptr = (int*)(*Derive_vptr);
	typedef void(*Func)(void);
	Func De_f1 = (Func)vptr[0];
	Func B1_g1 = (Func)vptr[1];
	Func De_m_f = (Func)vptr[2];
	Func De_m_g = (Func)vptr[3];
	De_f1();
	B1_g1();
	De_m_f();
	De_m_g();
	cout << "----------------------------------------------------" << endl;
	//提取出第二个Vptr(即虚函数表的首地址)
	int*Derive_vptr2 = Derive_vptr+1; //偏移4个字节到第二个vbtable的首地址
	int*vptr2 = (int*)(*Derive_vptr2);
	Func B2_f2 = (Func)vptr2[0];
	Func De_g2 = (Func)vptr2[1];
	B2_f2();
	De_g2();
	system("PAUSE");
	return 0;
}

/*总结:本例多继承中,两个父类分别各有两个虚函数,子类生成两个虚函数表,如果不重写父类虚函数,那么这两个虚函数表内容与两个父类的虚函数表分别相同
  同时继承的两个虚函数指针,占用内存的前八个字节,分别指向两个虚函数表的首地址() 类似与static int A[4];static int B[2];(类似静态成员,不占用对象内存,当然这里应该为类似指针数组而不是int)
  这等于两个虚函数表;void(*vptr1)()=A; void(*vptr2)()=B;分别代表这两个虚函数表的首地址，这两个首地址紧挨着,也就是相隔4个字节
  每个虚函数表可以看作一个指针数组(且可以使用数组的方式调用)每个数组中的元素可以看作为一个函数指针(可以当作函数名),每个指针对应一个虚函数
  在多继承下,子类本身的虚函数会放入第一个虚函数表中(头部为父类虚函数尾部为子类虚函数,子类重写父类虚函数会替换父类虚函数的位置),所以这里第一个虚函数表有4个虚函数,第二个虚函数表只有2个虚函数
  所以第二个虚函数表就不会在包含子类本身的虚函数,在默认下该虚函数内容与第二基类中的虚函数表内容相同(同样,重写虚函数会发生替换);*/
	   
	   
	   
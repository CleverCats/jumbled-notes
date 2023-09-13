																//探 究 std::move

#include<iostream>
#include<vector>
#include<string>
using namespace std;
class A
{
public:
	int* m_i;
	A(int* i);  //普通构造
	A( A&& a );  //移动构造
	A(const A&t);  //拷贝构造
	~A();
};
A::A(int* i)
{
	cout << "普通构造函数开始 " << endl;
	cout << "构造前" << endl;
	cout << "&n_1=" << i << endl;
	cout << "m_i=" << m_i << endl;
	//防止n_1内存的二次释放
	this->m_i = new int(*i);
	cout << "构造后" << endl;
	cout << "&n_1="<<i << endl;
	cout << "m_i=" << m_i << endl;
	cout << "普通构造函数结束" <<endl;
};
A::A(A&& a)
{
	cout << "移动构造开始" << endl;
	//移动构造
	cout << "构造前" << endl;
	cout << "源对象 m_i="<<a.m_i<<endl;
	cout << "目标对象 m_i=" << this->m_i << endl;
	
	//赋值
	cout << "源对象窃取目标对象的指针,使源对象 m_i = 目标对象 m_j,然后置空源对象m_i达到指针接管的目的,避免相同内存的重复释放与使用拷贝构造函数new的消耗"<< endl;
	this->m_i = a.m_i;    
	a.m_i = NULL;

	cout << "构造后" << endl;
	cout << "源对象 m_i=" << a.m_i << endl;
	cout << "目标对象 m_i=" << this->m_i << endl;

	cout << "移动构造结束" << endl;
}
A::A(const A&t)
{
	//需要new进行深拷贝
	cout << "拷贝构造开始" << endl;   
	cout << "构造前" << endl;
	cout << "源对象 m_i=" << t.m_i << endl;
	cout << "目标对象 m_i=" << this->m_i << endl;
	if (m_i != NULL)//释放目标对象空间
	{
		delete m_i;
		m_i = NULL;
	}
	this->m_i = new int(*t.m_i);
	
	cout << "构造后" << endl;
	cout << "源对象 m_i=" << t.m_i << endl;
	cout << "目标对象 m_i=" << this->m_i << endl;
	cout << "拷贝构造结束" << endl;
}
A::~A()
{
		cout << "即将析构指针m_i=" << m_i << endl;
	if (m_i != NULL)
	{
		cout << "已经析构指针m_i=" << m_i << endl;
		delete m_i;
		m_i = NULL;
	}
	//delete m_i;    //释放内存  //delete Null;如果不进行空指针筛除系统会也自动跳过该语句,所以不会造成重复释放
	//m_i = NULL;
}
void test()
{
	int n_1 = 10;
	A obj1(&n_1);  //构造对象obj1
	A obj2(obj1);  //拷贝构造
	A obj3(std::move(obj2));  //移动构造     //类模板中已经写好了具有 交换后，置空源指针的功能 的移动构造函数,所以对类模板对象使用std::move相当于移动对象
	cout << "返回主线程" << endl;
	//cout << "obj2.m_j=" << obj2.m_i << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}
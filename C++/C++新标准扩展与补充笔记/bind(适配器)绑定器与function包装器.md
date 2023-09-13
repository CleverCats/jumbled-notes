```cpp
#include<iostream>
#include<functional>
using namespace std;
void func(int a, int b, int c,int d)
{
 printf("a=%d b=%d c=%d d=%d\n", a, b, c,d);
}
void func2(int &a, int &b) //引用接收
{
 ++a; //自增1
 ++b;
}
class A
{
public:
 int m_a = 0;
 A(){};
 A(const A &cpa) //拷贝构造
 {
 cout << "--A--拷贝构造调用------" << endl;
 }
 void fun(int n,int m)
 {
 cout << "调用 void fun(int n,int m)" << endl;
 m_a = n;
 }
};
int main()
{
 //std::bind也是一个类模板(适配器中的绑定器),C++11中引用,(与function可调用对象打包器相同)也包含在头文件functional中
 //bind作为一个通用函数适配器接收一个可调用对象,生成一个新的可调用对象来适用改进后的参数列表
 auto fun=std::bind(func, 10, placeholders::_1, 20,placeholders::_2);
 //这里第一个参数绑定为10,第2个参数使用placeholders::_1 表示占位符 调用时,第1个实参为形参的第3个参数 ,第3个 绑定为20 
//同理,第4个参数使用placeholders::_1 表示占位符 调用时,第2个实参为形参的第4个参数
//调用时只需要输入被占用符占用的参数,这里只需要输入2个参数,分别对象形参的第2个与第4个参数
fun(80, 90); //10 80 20 90
cout << "---------------------------------" << endl;

//陷阱: 通过bind绑定的固定参数为值传递!!!!!
//测试:
int m = 11; int n = 12;
//将形参的第一个参数绑定为 m 
auto fc=std::bind(func2, m, placeholders::_1);
fc(n); //调用
//本应预计是 m=12 n=13,但实际上 输出 m=11 ,n=13;
//**************表明绑定m到形参1为值传递,引用并未起作用************
//未绑定的形参正常引用传递
cout << "m= " << m << " n= " << n << endl; //11 13

cout << "------------------------------" << endl;

A obj;
//std::bind作为类成员函数的适配器 std::bind(成员函数地址,类对象,绑定/占位,绑定/占位,绑定/占位);
//因为成员函数属于类,所以可以取址,但是调用必须依赖类对象调用（除静态成员函数）,所以这里的第2个参数为类对象
auto c_obj = std::bind(&A::fun, obj, placeholders::_1, placeholders::_2);
c_obj(10, 20); //这里预测会将m_a赋值为10,但实际上m_a的值并没有发生改变
cout << "obj.m_a ="<< obj.m_a << endl; //0
//因为在bind绑定obj时,bind会绑定一个它的拷贝,这里会产生拷贝构造,实际上改变的是拷贝对象的m_a的值,obj未受到影响.并返回该可调用对象(仿函数类型对象)
//因为std::bind作为适配器中的绑定起,返回的值为可调用对象,这里返回的临时对象为可直接调用参数1(&A::fun)的可调用对象
printf("------------------------------------------\n");
//如果绑定的是 obj的引用,那么则绑定的才是真正的obj
auto c_obj_2 = std::bind(&A::fun, &obj, placeholders::_1, placeholders::_2);
c_obj_2(10, 20);
cout << "obj.m_a ="<<obj.m_a << endl;

cout << "-----------------------------------------" << endl;
//std::function 接收 std::bind的返回的可调用对象(也可以说是仿函数类型对象)
//1.接收绑定的类成员函数
A obj2;
std::function<void(int, int)> f5 = std::bind(&A::fun,obj2,placeholders::_1, placeholders::_2);
f5(20, 30);
//2.接收绑定的类成员变量(函数类型接收 类成员类型，比较奇怪但暂时不深究)
//A obj3;
////std::function<int &()> mf = std::bind(&A::m_a,obj3);绑定拷贝的对象
//std::function<int &()> mf = std::bind(&A::m_a,&obj3); //&obj3绑定引用的对象,保证不产生临时对象,导致操作时时仅改变临时对象的值
//mf() = 10; //赋值时也采用函数调用形式赋值
//cout << obj3.m_a << endl;

/*总结: bind思想 即是延迟调用思想,将可调用对象统一格式,保存起来,在需要的时候在调用
std::function可以绑定可调研对象,但不能直接绑定类成员,因为除了静态类成员,非静态(虽然也属于类,不属于对象)但需要类对象才可以调用
但std::bind能绑定任何可调用对象,甚至可以绑定类成员变量,并且bind返回一个适配器修改后的可调用对象,该对象就可以被std::function接收
由此funtion可以间接的包装类成员函数对象*/
//ps: std::function<>别名可调用对象包装器

system("PAUSE");
return 0;
}
```
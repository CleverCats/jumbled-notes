#include<iostream>            //总结:week_ptr不可以独立于shared_ptr它起到对shared_ptr的监视作用,给shared_ptr添加不影响对象释放的week ref 弱引用
#include<memory>
using namespace std;
int main()
{
    shared_ptr<int>p(new int(10));  
    weak_ptr<int>pw = p;   

//shared_ptr的强引用 strong ref 不变, 弱引用 week_ptr 加一          

//pw不影响shared_ptr所指向对象的正常周期,它只是起到一个监视作用(旁观者),监视指针指向的对象内存是否被释放

//或者weak_ptr<int>pw; pw=p;

    //1. weak_ptr成员函数lock()
    //auto=shared_ptr<int>
    auto ptr = pw.lock();  //如果pw中接收到了shared_ptr的指针,那么lock()函数返回一个 shared_ptr类型的该指针,也就是  strong ref 加一
    if (ptr != nullptr)    //如果没有接收到,会返回一个 空 的shared_ptr指针
    {
        cout << "is not empty , strong ref + 1" << "  Value= " << *ptr << endl;
    }
    else
    {
        cout << "is empty" << endl;
    }
    //2. 成员函数use_count()
    weak_ptr<int>p2(p);
    cout << "strong ref = " << pw.use_count() << endl;
    //3. 成员函数expired() 译:过期  如果弱引用week ref监视的shared_ptr指向的对象内存被释放后(强引用为0),代表监视的过期,返回true,否则返回false
    p.reset();  //置空 p ,strong ref -1
    ptr.reset(); //置空 ptr ,strong ref -1, strong ref=0时释放指针指向对象内存
    if (pw.expired())
    {
        cout << " strong ref = " << pw.use_count() <<" 内存释放 监视过期" << endl;
    }
    //4. 成员函数reset() 指定的弱引用置空nullptr 弱引用week_ptr减一 不影响强引用
    
    system("pause");
    return 0;

}
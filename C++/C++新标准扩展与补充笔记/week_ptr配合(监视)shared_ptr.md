#include<iostream>            //�ܽ�:week_ptr�����Զ�����shared_ptr���𵽶�shared_ptr�ļ�������,��shared_ptr��Ӳ�Ӱ������ͷŵ�week ref ������
#include<memory>
using namespace std;
int main()
{
    shared_ptr<int>p(new int(10));  
    weak_ptr<int>pw = p;   

//shared_ptr��ǿ���� strong ref ����, ������ week_ptr ��һ          

//pw��Ӱ��shared_ptr��ָ��������������,��ֻ����һ����������(�Թ���),����ָ��ָ��Ķ����ڴ��Ƿ��ͷ�

//����weak_ptr<int>pw; pw=p;

    //1. weak_ptr��Ա����lock()
    //auto=shared_ptr<int>
    auto ptr = pw.lock();  //���pw�н��յ���shared_ptr��ָ��,��ôlock()��������һ�� shared_ptr���͵ĸ�ָ��,Ҳ����  strong ref ��һ
    if (ptr != nullptr)    //���û�н��յ�,�᷵��һ�� �� ��shared_ptrָ��
    {
        cout << "is not empty , strong ref + 1" << "  Value= " << *ptr << endl;
    }
    else
    {
        cout << "is empty" << endl;
    }
    //2. ��Ա����use_count()
    weak_ptr<int>p2(p);
    cout << "strong ref = " << pw.use_count() << endl;
    //3. ��Ա����expired() ��:����  ���������week ref���ӵ�shared_ptrָ��Ķ����ڴ汻�ͷź�(ǿ����Ϊ0),������ӵĹ���,����true,���򷵻�false
    p.reset();  //�ÿ� p ,strong ref -1
    ptr.reset(); //�ÿ� ptr ,strong ref -1, strong ref=0ʱ�ͷ�ָ��ָ������ڴ�
    if (pw.expired())
    {
        cout << " strong ref = " << pw.use_count() <<" �ڴ��ͷ� ���ӹ���" << endl;
    }
    //4. ��Ա����reset() ָ�����������ÿ�nullptr ������week_ptr��һ ��Ӱ��ǿ����
    
    system("pause");
    return 0;

}
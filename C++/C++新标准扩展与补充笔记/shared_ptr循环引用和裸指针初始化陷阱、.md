#include<iostream>
#include<memory>
using namespace std;
class A:public enable_shared_from_this<A>   //�̳б�׼���е���ģ��  enable_shared_from_this ,�Ա�������Ա����  shared_from_this() �ɹ�����thisָ��
{
public:
	//����һ:
	shared_ptr<A> Func()
	{	
		cout << " this adress=" << this << endl;

		//ʹ��this��ָ���ٴγ�ʼ��shared_ptr  ( this = new A )
		//strong ref = 1�����¶������ָ��ָ��ͬһ���ڴ�,����strong ref ȴ���� 1
		//return shared_ptr<A>(this);;

		//Ӧ��ʹ�� shared_from_this()
		return shared_from_this();   //����this����ָ��
		//ԭ��: enable_shared_from_this ����һ����ָ�� week_ptr ���� thisָ��,���ó�Ա���� shared_from_this()
		//ʵ������ �����Ա�����ķ���ֵ��  week_ptr �� lock()���������������ص�����ָ�� ��ʵ���� week_ptr<A>pw = ptr; һֱ���Ӹ�����ָ��,��ʱ����lock()���ظ�ֻ��ָ��ĸ���
		//�Ӷ�ʵ��strong ref + 1,����ͬһ����ָ���α�ָ��ָ���װȴǿ���ü���=1�����
	}
};
//�����:
class C; //����
class B
{
public:
	shared_ptr<C>c_ptr;  //B���������з�װC��ָ�������ָ��,��Ϊ��Ա����
};
class C
{
public:
	//shared_ptr<B>b_ptr; //C���������з�װB��ָ�������ָ��, ��Ϊ��Ա����
	//�������:������һ����Ա������Ϊweek_ptr ���ᵼ��strong ref����,�����ڵ�B�������negָ��strong ref��Ϊ1 �õ��ͷź�,B�����ͷ�,��Ա����shared_ptr<C>c_ptr;Ҳ�õ�һ���ͷ�
	//C������negָ��Ӷ��� 1 ,��ʣ 1 ��B���������ʱ,strong ref�ٴμ� 1 �������ٳɹ�, ��A������ָ��������,A�� strong ref - 1ͬ�����Դﵽ��ͬЧ��
	weak_ptr<B>b_weekptr;
};
int main()
{
	//����:��Ҫ��ͬһ����ָ��,ͬʱ��ʼ���������ָ��,�ᵼ�¶������ָ��ָ��ͬһ���ڴ�,����strong ref ȴ���� 1


	//ʹ����ָ���ʼ�� shared_ptr
	//strong ref = 1
	shared_ptr<A>ptr(new A);

	//shared_ptr<A>ptr2=ptr->Func();    
	//strong ref ��Ȼ = 1,��Ϊ���ص���һ����ͬһ����ָ���ʼ��������ָ��,����������ָ��Ŀ��� 

	//���:�ᵼ����ͬ�ڴ�����ͷ�

	//����shared_from_this()��Func()���ص��� shared_ptr<A>ptr(new A); �ĸ���(��week_ptr��lock()��ȡ��)
	shared_ptr<A>ptr2 = ptr->Func();

	shared_ptr<B>ptr3(new B);
	//new B��ʼ������ָ�����ptr3 ��ʱptr3�� ǿ����=1
	shared_ptr<C>ptr4(new C);
	//new C��ʼ������ָ�����ptr4 ��ʱptr4�� ǿ����=1

	//ɧ������ʼ��:
	ptr3->c_ptr = ptr4;   //c_ptr Ϊ shared_ptr<C>c_ptr; ��Ϊ*ptr3�ĳ�Ա����,��ʱ   ptr4�� ǿ���� = 2
	//ptr4->b_ptr = ptr3;	  //b_ptr Ϊ shared_ptr<B>b_ptr; ��Ϊ*ptr4�ĳ�Ա����,��ʱ   ptr3�� ǿ���� = 2

	//��ʱ��������ǿ����,�������ֻ���ͷŸ�,Ȼ��ǿ���û�ʣ1,��Ա�������ܵõ��ͷ�.����������ʱ,ֻ������ shared_ptr<B>ptr3(new B);�� shared_ptr<C>ptr4(new C); ���ɵ�ptr3��ptr4
	//ǿ���ü�1 ����Ϊ��ʣ1 ���Զ����ڴ治�ᱻ�ͷ�,�����ڴ�й©

	//���:
	ptr4->b_weekptr = ptr3;  //ptr4->b_weekptrΪ�����ý���  shared_ptr<B>ptr3
	system("PAUSE");
	return 0;
}
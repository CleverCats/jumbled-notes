#include<iostream>
#include<string>
#include<tuple>
using namespace std;

//�ɱ�κ���ģ��(�ݹ����)
namespace VarianceFunc    //�����ռ�
{

	void Variance()					//��������ֹ����,��args...�������в����ڲ���ʱ,����ø����غ���
	{
		cout << "������չ�����" << endl;
	}
	template<typename T, typename...T2>             //T ��Ĳ�������:  ��ȡ typename...���� T2 (����T2Ϊ���Ͳ��������ܵĸ�����)  ���������յĸ��ֲ��� 
	void Variance(const T& firstarg, T2...args)     //ע��: ���� T2 ���� 0-����� ��ͬ���߸�����ͬ��ͬ �������Ͷ�����һ���������� ,args ... ���� 0-��������� ������һ������  
	{                 /*һ������ һ���β�*/
		cout << "������ : " << sizeof...(T2) << endl;    //��ͬ�� sizeof...(T/args)  ��ò������в�������,����T������
		cout << "չ��������: " << firstarg << endl;
		//if (sizeof...(T2) == 1) return;
		Variance(args...);          //�ݹ���ô��������,�������еĵ�һ�������ᴫ���firstarg  ���������ᴫ�� ...args  ���²����������ݼ�,ֱ��Ϊ�պ������ֹ����,��ϵݹ�

	}
}
//�ɱ����ģ��(�ݹ�̳�)
namespace VarianceClass
{

	template<typename...args> class A			 //����ģ��,���������γ���������ģ��(�����������뷺�������Թ���/����ʱ,���Ȼ�ѡ��������,���Ի���������������ҵݹ�̳�
	{
		/*public:                                    //���Ե���һ���游��Ŀ�ģ��,���̳�,������ֹ�ݹ�̳�;
		A()
		{
		printf("����ģ�幹�� A::A() this= %p\n", this);
		cout << "template<> class A <> Ϊ�游��" << endl;
		}*/
	};
	template<typename firstarg, typename...otherargs>	//�游��ģ���������  �����Ͳ����� args  ���Ϊ firtsargs ��ʣ�µ� otherargs �����ֵ����Ͳ���
	class A <firstarg, otherargs...> :private A<otherargs...>   //�ݹ�̳�,ÿ�μ̳н��������г���һ�������������������븸��
		//����:���������������ģ��Ķ���ʱ,���ø�������ģ��,��ʱ���ָ�ģ�����˽�м̳и���
		//Ȼ��ͨ��ģ������б�  A<otherargs...> ȷ���˸������ģ������,������ʼ�ȹ���ø���
		//Ȼ������Ҳ������������ģ�屾��,�������Ĳ���������һ�����˲��,�ٴμ̳�.�ٴβ��,ֱ��������Ϊ�� < >
		//�游��Ϊ�ɱ�η���ģ�������Ϊ������Ϊ�յ�ģ��,���Ǽ̳к���ֹ�̳�(��Ϊclass A <firstarg, otherargs...> ������Ҫָ��һ���������� )
	{										//Ҳ�����Լ�������Ҳ��ģ���������ģ��,���в���
	public:
		A(firstarg val, otherargs... val2) :m_val(val), A<otherargs...>(val2...)     //����չ��.��ֹ����
			//����ͨ����Ա��������չ���Ĳ�����   
			//A<otherargs...>(val2...)��ʼ���б��츸��,ȷ��������ģ��Ĳ������� ���� ���������val2...���й���
		{
			printf("������� A::A() this= %p\n", this);
			cout << "m_val= " << m_val << endl;
		}
	private:
		firstarg m_val;
	};
	template<> class A <>   //����������ģ��,��Ϊ�游ģ�屻�̳�,Ҳ����ֱ��д�ڷ�����ģ����,��Ϊ�����ɱ������ģ��Ҳ���Դ���ղ���,����������ﵽͬ��Ч��                      
	{                       //���д�˸���������ģ��,��ô�ͻ����ȵ��ø��������汾
	public:
		A()
		{
			printf("����ģ�幹�� A::A() this= %p\n", this);
			cout << "template<> class A <> Ϊ�游��" << endl;
		}

	};
}
//�ɱ����ģ��(�ݹ����(������໥����))
namespace VarianceComboClass
{
	//��ɱ����ģ��(�ݹ�̳�)���������:  
	//�ݹ�̳У���һ������Ĺ��콨,���²���ȥѰ�Ҹ���,�ض��ﵽ�ݹ�̳�,ÿ�θ���Ĳ���������������һ
	//�ݹ����:   һ��������ʱ����ö�������Ա���������Ա��������ʱ,���������Ա���������Ա����,�ﵽ�ݹ鹹��,ÿ�ι������ݵĲ���������������һ
	//ֱ��������Ϊ0,���ÿɱ����������ģ����й���

	template<typename...args> class B
	{
	public:
		B()
		{
			printf("����ģ�幹�� B::B() this = %p\n");
		}
	};
	template<typename firstarg, typename...otherargs>
	class B <firstarg, otherargs...>

	{
	public:
		B(firstarg val, otherargs...val2) :m_val(val), obj(val2...)  //��ʼ���б������Ա����,�����Ա����ʱ,�������Ǹ��������ɱ��ģ��
			//���Ի�Ѳ����� otherargs... ���Ϊ firstarg val, otherargs... val2 
			//Ȼ���ٴι������Ա,�����ٴβ��,ֱ��������Ϊ��,���ÿɱ�η����汾(�ղΰ汾),���߶����������Ŀղΰ汾
		{
			printf("������� B::B() this= %p\n", this);
			cout << "m_val= " << m_val << endl;
		}
	private:
		firstarg m_val;
		B<otherargs...> obj;        //����:����ʱ����obj����B<otherargs...> obj,�����ٴι���obj,ֱ���ҵ��������Ա����ĳ�Ա��ģ��,Ȼ�����ι����ö���
		//��ʱ��Ĺ���obj��ʵ���빹�췺����,����Ϊ�������ػ����ʺ�,�������ȹ����ػ�
	};

}
//ͨ��tuple(Ԫ��)�ݹ����static��̬��Ա����չ��������
namespace VarianceTupleClass
{
	template<int mycount, int maxcount, typename...T>
	class C
	{
	public:
		static void Func(const tuple<T...>& tub)
		{
			cout << "tuple��̬��Ա չ������  value= " << get<mycount>(tub) << endl;
			C<mycount + 1, maxcount, T...>::Func(tub);
		}
	};
	//��mycount==maxcountʱ����������������ݹ�����ྲ̬��Ա
	template<int maxcount, typename...T>
	class C<maxcount, maxcount, T...>
	{
	public:
		static void Func(const tuple<T...>& tub)
		{
			cout << "��ͨ��tuple(Ԫ��)��ȫչ��������" << endl;
		}
	};
	template<typename...T>
	void FunStartCall(const tuple<T...>&tub)
	{
		//������ʼչ��λ��,�Ͳ���������
		C<0, sizeof...(T), T...>::Func(tub);  //��ʼ����
	}
	template<typename...T>
	void FunSentTuple(T...args)             //���ղ���
	{
		std::tuple<T...>mytuple(args...);
		FunStartCall<T...>(mytuple);
	}
}

int main()
{
	using namespace VarianceFunc;
	using namespace VarianceClass;
	using namespace VarianceComboClass;
	using namespace VarianceTupleClass;
	cout << "-----------------�ݹ���̳е���չ��������--------------------------------" << endl;
	A<int, char*, char*, char>obj(10, "hellow", "Word", '6');   //�������Ĵ���������Ϊ0-�����
	cout << "--------------------------�����̳�---------------------------------------" << endl;

	cout << "-------------------�ݹ麯������չ��������--------------------------------" << endl;
	Variance(1, 2.0, 3, "HELLOW", 'A', 5.5f);
	cout << "--------------------------��������---------------------------------------" << endl;

	cout << "-------------�ݹ�����Ϲ��������չ��������-----------------------------" << endl;
	B<int, char*, char*>m_obj(10, "hellow", "Word");
	cout << "------------------------�������----------------------------------------" << endl;

	cout << "-------------------tuple(Ԫ��ݹ��Ա����չ��)--------------------------" << endl;
	FunSentTuple("Hellow world", 'A', 1.5, 2008);
	cout << "-----------------------����tupleչ��------------------------------------" << endl;
	system("PAUSE");
	return 0;
}
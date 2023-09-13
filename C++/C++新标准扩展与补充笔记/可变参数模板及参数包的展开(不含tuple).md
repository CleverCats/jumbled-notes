#include<iostream>
#include<string>
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
	
	template<typename...args> class A{};			 //����ģ��,������������γ���������ģ��(�����������뷺�������Թ���/����ʱ,���Ȼ�ѡ��������,���Ի������������ģ������ҵݹ�̳�
	template<typename firstarg, typename...otherargs>//�游��ģ���������  �����Ͳ����� args  ���Ϊ firtsargs ��ʣ�µ� otherargs �����ֵ����Ͳ���
	class A <firstarg, otherargs...> :private A<otherargs...>   //�ݹ�̳�,ÿ�μ̳н��������г���һ�������������������븸��
																//����:���������������ģ��Ķ���ʱ,���ø�������ģ��,��ʱ���ָ�ģ�����˽�м̳и���
																//Ȼ��ͨ��ģ������б�  A<otherargs...> ȷ���˸������ģ������,������ʼ�ȹ���ø���
	                                                            //Ȼ������Ҳ������������ģ�屾��,�������Ĳ���������һ�����˲��,�ٴμ̳�.�ٴβ��,ֱ��������Ϊ�� < >
																//������Ϊ�յĸ��಻����,������ֹ�̳�(��Ϊclass A <firstarg, otherargs...> ֻ����Ҫָ��һ���������� )
	{															//Ȼ��Ҳ�����Լ�������Ҳ�ɿ�ģ���������ģ��,���в���
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
	template<> class A <>
	{
	public:
		A()
		{
			printf("����ģ�幹�� A::A() this= %p\n", this);
			cout << "template<> class A <> Ϊ�游��" << endl;
		}

	};
}
int main()
{
	using namespace VarianceFunc;
	using namespace VarianceClass;
	cout <<"-----------------�ݹ���̳е���չ��������--------------------------------" << endl;
	A<int,char*,char*,char>obj(10,"hellow", "Word", '6');   //�������Ĵ���������Ϊ0-�����
	cout <<"--------------------------�����̳�---------------------------------------" << endl;

	cout<<"-------------------�ݹ麯������չ��������--------------------------------" << endl;
	Variance(1, 2.0, 3, "HELLOW", 'A', 5.5f);				//�������Ĵ���������Ϊ0-�����
	cout <<"--------------------------��������---------------------------------------" << endl;
	system("PAUSE");
	return 0;
}
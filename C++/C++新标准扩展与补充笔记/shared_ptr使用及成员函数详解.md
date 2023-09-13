/*1��unique_ptr����������ָ�룬û��*��->��������֧���±����[]

2��shared_ptr����������ָ�룬��*��->����������֧���±����[]��ֻ��ͨ��get()ȥ���������Ԫ�ء�

3��shared_ptr����������ָ�룬����Ҫ�Զ���deleter ����ʹ���Զ���ɾ���� Ҳ����ʹ�� default_delete�ɵ�����ģ��
��������������������������������*/


#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;
template<typename T>
void DeletePtr(T* ptr);  //����ģ������.�����Զ���ɾ���� �ڵײ�ʵ��
template<typename T>     //����ģ������,��������ָ����shared_ptr����ָ��,��return��ȥ
shared_ptr<T> make_shared_ptr(size_t size);  //size_t�൱���޷������� 0 - number
template<typename T>
T Fptr(T& ptr)   //���ý���,strong ref��������
{
	return ptr;  //������ʱ���� strong ref������һ
}
int main()
{
	//shared_ptr��������ָ����������,ÿ��һ�������͵�ָ�뿽��(Ҳ����˵���ý��ղ���ı�)
	//����ָ��ģ���ಿ����� strong ref(���ڼ�����ڼ���ָ��ͬһ���ڴ�ĸ�����ָ���ֵ) ��һ

	//ÿ����һ�������͵�ָ�뿽����strong ref ��� ��һ ,��Ϊ0ʱ,�����ø���ģ�����������,�ͷ����ָ��ָ���ڴ�
	shared_ptr<int>p3(new int(10));
	//make_shared<int>��ģ�����ȡ��new �Ҹ���ȫ
	shared_ptr<int> p=make_shared<int>(10);
	auto ptr(p);    //��������ָ��
	Fptr(p);
	//1.
	int count = p.use_count();       //��Ա����,use_cout()���� strong ref ��ǰ����
	cout << "strong ref = "<<count << endl;
	//2.
	if (p.unique() == true)  //��Ա���� unique() �ж��Ƿ��ж������shared_ptr��ַָ��ͬһ���ڴ�,�� strong ref = 1 ���ڷ���false   strong ref =0 ���� >1����false
	{
		cout << "��ǰ strong ref = 1 ָ�뱻��ռ" << endl;
	}
	else
	{
		cout << "��ǰ strong ref >1 ָ����ڱ�����,�ڴ���ڹ���" << endl;
	}
	//3.
	//��Ա����reset(���� / ��ʼ��) ����ָ��
	//reset()������ʱ
	//p.reset();        // �� strong ref = 1��=0ʱɶҲ���ɣ� ���ͷ�ָ��ָ���ڴ沢���ÿ�
					  // �� strong ref >1 �� �� ��ָ���ÿ�(�����߼�һ) (***���ͷ�***)  Ȼ�� strong ref ��һ,
	//����ʱ
	p.reset(new int(2020));        //��  strong ref = 1 ���ͷŸ�����ָ��ָ����� ,������ָ��ָ����� 20020 ,��ʹ����ָ����� new������ָ��
	                                //��   strong ref >1 ���ͷŸ�ָ��ָ�����, Ȼ��ʹ�ø���ָ��ָ��  20020,��ʱ strong ref  ��һ
	//4.��*
	cout << *p << endl;         //����ָͨ��һ����*����ע�ⲻ��ֱ��delete p,��Ҫ��Ĭ��ɾ���������Զ���ɾ������delete p;
	
	//5.��Ա����get()
	int *m_p = p.get();        //��ָ��ָ�뱣�����ָ���ȡ����(����ָ����Ȼ�������)(ע�ⲻҪdelete��ָ��,ָ����ͷŻ���������ָ�����)
	                           //ʹ�����:��Щ���������ò�����Ҫ��ͨ��ָ���������������ָ������ʹ�� �˴�m_p�൱����ָ��
	//6.std::swap()����ָ��
	shared_ptr<string>pt1(new string("HELLOW"));
	shared_ptr<string>pt2(new string("HI"));
	std::swap(pt1, pt2);     //����ָ��

	//7.=nullptr
	auto pt3(pt1);
	pt3 = nullptr;    //�ÿ�pt3��ʹ  strong ref��һ  ���pt3û�������κο�������, strong ref -1  =0 Ҳ���ͷ���ָ��ָ����ڴ� 

	//8.����ָ��������Ϊ�Ƿ�Ϊ�� �ж����� if(ptr1!=nullptr) {} else {};

	//9.�Զ���ָ��ɾ����,ȡ������ָ���ȱʡɾ����(����������ӡһЩ��־(�Լ������Ĳ���)),��strong ref=0ʱ,�ͻ���ò������Ŀɵ��ö���
	//******ע��: shared_ptr<string>pt4=make_shared<string>("I love china");���ַ�ʽ������ָ���Զ���ɾ����******

	//ʹ�����:��Ϊshared_ptr�е�Ĭ��ɾ�����е�deleteû��delete[]�İ汾,��˲����ͷ�����ָ��
	shared_ptr<string>pt4(new string("HI"),DeletePtr<string>);  //������Ϊ�ɵ��ö���,��Ϊ�Զ���ɾ����
	//��Ϊ�ǿɵ��ö���,���Բ�����Ҳ������lambda���ʽ
	shared_ptr<string>pt5(new string("I am a good boy"), [](string* p5)
	{
		cout << "Lambda��Ϊ�Զ���ɾ���� delete ָ��" << endl;
		delete p5;  //Lambda���ʽ�ɵ��ö�����Ϊ�Զ���ɾ����
	});
	pt5.reset();
	pt4.reset();

	//10.ʹ��std:;default_delete��ģ����ɾ�������ڲ�������(),��˿�����Ϊ�ɵ��ö���
	//ͬʱ��Ҳ֧��������ָ�����Ƶ
	shared_ptr<string>pt6(new string("��ð�"),std::default_delete<string>());
	//ֻ��Ҫ����ģ��ʵ���б��д���string[]����ʶ��string����ָ���������delete
	shared_ptr<string>pt7(new string[10], std::default_delete<string[]>());

	//11.C++17�п��Բ��������Զ���ɾ��������std::default_delete<string>������ָ�����delete��
	//C++17��  shared_ptr������opreator[]��������ʹ��int[]�������������ģ�����
	//ֻ��Ҫ������ָ����ģ���ģ������б���ʾ���� int[]���������;Ϳ��Խ���delete[]�Ĳ���
	//shared_ptr<int[]> pt8(new int[10]);   
	//pt8[0] = 10; pt8[1]=9; ��C++17�п���ʹ��  ��C++11 ��ֻ��ʹ�� pt8.get()[index]  get()���������׵�ַ,���Ե�������ʹ��,��������ʹ��[]
	//�ܽ�:  ������ʹ��,��׼����

	//12.ʹ�÷�װ�õĺ���ģ������������ָ��
	shared_ptr<int>pt9 = make_shared_ptr<int>(4);//Ҳ����ʹ��auto����
	auto pt10 = make_shared_ptr<string>(3);
	string StrArray = "ABC";
	for (int i = 0; i < 3; i++)  //ʹ�ø�ֵ��ʼ��
	{
		// get()���������׵�ַ,���Ե�������ʹ��,��������ʹ��[]
		pt10.get()[i] = StrArray[i];
		cout << pt10.get()[i] << endl;
	}
	system("pause");
	return 0;
}
//ָ��ɾ��������˵��: 
//��������shared_ptrָ���˲�ͬ��ɾ����,ֻҪ����ָ��Ķ���������ͬ,��ô������shared_ptrҲ����ͬһ������,���unique_ptr��ͬ
//��Ϊ����ͬһ������,��������ֱ�ӿ��Խ��� = ���ָ�ֵ����
template<typename T>
void DeletePtr(T* ptr)
{
	//........��ӡ��־
	cout << "�ɵ��ú�����Ϊ�Զ���ɾ���� delete ָ��" << endl;
	delete ptr;
}
template<typename T>     //����ģ������,��������ָ����shared_ptr����ָ��,��return��ȥ
shared_ptr<T> make_shared_ptr(size_t size)  //size_t�൱���޷������� 0 - number
{
	return shared_ptr<T>(new T[size], std::default_delete<T[]>());  //�������ɵ���������ָ��,���������н���
}
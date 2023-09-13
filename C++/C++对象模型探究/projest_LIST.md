#ifndef __FORWARD__LIST
#define __FORWARD__LIST
#include<iostream>
using namespace std;
																/*Ƕ��ʽ�ڴ��ʵ�ֵ�������*/
/*------------------�ڴ�ؽӿ�------------------
static myallocator m_allocator			 �����ڴ�ض���,���ڵ����ڴ����ӿ�
static void*operator new(size_t size)    ����operator new ʵ���ڴ���ڴ����ӿڵĵ���
static void operator delete(void*phead)  ����operator delete ʵ���ڴ�ʵ�α���սӿڵ��� 
----------------------------------------------*/
#define CALL_MALLOCATOR_()\
public:\
	static myallocator m_allocator; \
	static void*operator new(size_t size)\
	{\
	return m_allocator.my_allocator(size);\
	}\
	static void operator delete(void*phead)\
	{\
	m_allocator.mydeallocator(phead); \
	}\

/*-----------------�ڴ�ʽӿڵ���------------------
myallocator classname::m_allocator;	    classname�����Ͳ��� �����������¾�̬�ڴ����ӿ�
--------------------------------------------------*/
#define IMPLEMENT_ALLOCATOR(classname)\
myallocator classname::m_allocator;
/*------------------�ڴ��ʵ��--------------------*/
class myallocator {
public:
	//ÿ��Ϊ�ڴ�ط�����ڴ汶��   
	static int multiple;
	//��¼�ڴ����ӿڵ��ô���
	static int NewObjCount;
	//��¼�����ڴ�������
	static int AllocatorCount;
	//�ڴ���ڴ����ӿ�
	void*my_allocator(size_t& size) 
	{
		//��ʼ��
		tmplink = nullptr;
		if (free_ptr == nullptr)
		{
			//��ʶ�ڴ�ش����ٿռ�
			int capacity = multiple*size;
			//�����ڴ�ռ�,tmlink��¼�¿����ڴ�ռ���׵�ַ
			tmplink = (obj*)malloc(capacity);
			//ָ���������ڴ��׵�ַ
			free_ptr = tmplink;
			//�����ڴ��ʵ���ڴ�����
			for (int i = 0; i < multiple - 1; ++i)
			{
				//���Ƶ�����ڴ��
				tmplink->next = (obj*)((char*)(tmplink)+size);
				//��ǰ�ڴ��ָ����ָ�����ڴ��
				tmplink = tmplink->next;
			}
			//β���ڴ��ָ���
			tmplink->next = nullptr;
			//��¼�����ڴ�������
			++AllocatorCount;
		}
		//��¼�ڴ����ӿڵ��ô���
		++NewObjCount;
		//��ȡ��ǰδ�����ڴ���׵�ַ
		tmplink = free_ptr;   
		//ָ�����ָ����һ��δ�����ڴ���ַ
		free_ptr = free_ptr->next;  
		//���ؿ����ڴ���ַ
		return tmplink;
	}
	void mydeallocator(void* phead)  //�ڴ���սӿ�
	{
		((obj*)phead)->next = free_ptr;
		free_ptr = ((obj*)phead);
	}
private:
	//Ƕ��ʽָ��
	struct obj
	{
		obj*next;
	};
	//����ṹ��ָ�����,����ʵ�������ڴ�,�����ڷ��ؿ����ڴ���׵�ַ
	static obj* tmplink;
	//ʼ��ָ��һ��ɷ����ڴ����ĵ�ַ,��ʼ��ָ���
	obj*free_ptr = nullptr;   
};
				//�����ʼ��
myallocator::obj* myallocator::tmplink = nullptr;
int myallocator::multiple = 50000;
int myallocator::NewObjCount = 0;
int myallocator::AllocatorCount = 0;


template<typename DataType> struct Node {
	//������
	DataType m_data;
	//ָ����
	Node* next;
	//���ú�����ڴ�ؽӿ�
	CALL_MALLOCATOR_()   
};
template<typename DataType> IMPLEMENT_ALLOCATOR(Node<DataType>)
template<typename DataType> class m_List {
public:
	//������������
	typedef Node<DataType>* Link;
	//����ͷָ��
	Link L;
	//����ͷ���
	Link HeaderNode;
	//��¼������
	int m_size=0;
	//���ڱ�����β���,ʵ��β����
	Link m_Temp;
	//�����ձ�
	m_List()
	{
		//����ͷָ��
		//L = (Link)malloc(sizeof(Node<DataType>));
		L = new Node<DataType>;
		//����ͷ��㣨����ͳһβ�����ײ巽����
		//HeaderNode = (Link)malloc(sizeof(Node<DataType>));
		HeaderNode = new Node<DataType>;
		//ͷ���ָ����ָ���
		HeaderNode->next = nullptr;
		//ͷָ��ָ��ͷ���
		L->next = HeaderNode;
		//���ڱ�����β���,ʵ��β����
		m_Temp = HeaderNode;
	}
	//β��
	void m_push_back(DataType data)
	{
		//ָ�������β���
		while (m_Temp->next != nullptr) m_Temp = m_Temp->next;
		//��ʼ���½ڵ�
		Link NewNode = new Node<DataType>;
/*-----------------------------------------------------------------------------*/
		/*cout << typeid(data).name() << endl;
		cout << typeid(NewNode->m_data).name() << endl;*/
		//string�������ݿ���
		NewNode->m_data = data;                 //Error
/*------------------------------------------------------------------------------*/
		//�½��ָ����ָ���
		NewNode->next = nullptr;
		//�½��β������
		m_Temp->next = NewNode;
		//��������+1
		++m_size;
	}
	//ͷ��
	void m_push_front(DataType data)
	{
		//�����½��
		//Link NewNode = (Link)malloc(sizeof(Node<DataType>));
		Link NewNode = new Node<DataType>;
		NewNode->m_data = data;
		//�½��ָ����ָ���̽ڵ�
		NewNode->next = HeaderNode->next;
		//ͷ���ָ����ָ���½��
		HeaderNode->next = NewNode;
		//��������+1
		++m_size;
	}
	//��ȡԪ������
	int m_list_size()
	{
		return m_size;
	}
	DataType operator[](int index)
	{
		//�������Ա���,��Ч����
		if (index >= m_size|| index < 0)return{};
		int i = 0;
		Link m_Temp=HeaderNode->next;
		while(i < index)
		{
			m_Temp = m_Temp->next;
			++i;
		}
		return m_Temp->m_data;
	}
	//�����ͷ��ڴ�
	~m_List()
	{
		//��¼��ǰ���ͷ�ָ��
		Link m_free = L;
		//��¼��һ�����ͷ�ָ��
		Link m_Next_free = m_free;
		while (m_free!= nullptr)
		{
			//��¼��һ�����ͷ�ָ��
			m_Next_free = m_Next_free->next;
			//�ͷŵ�ǰָ��
			//free(m_free);
			delete(m_free);
			//ָ����ͷ�ָ��
			m_free = m_Next_free;
		}
	}
};
#endif
#include<iostream>
using namespace std;
template<typename DataType> class m_Forward_List{
public:
	//声明结点
	struct Node
	{
		//数据域
		DataType m_data;
		//指针域
		Node* next;
	};
public:
	//声明链
	typedef Node* LinkList;  
	//链表
	LinkList L;
	//头结点
	LinkList HeadNode;
	//当前结点数量
	int CurrentNodeSize;
public:
	int m_Size()
	{
		return CurrentNodeSize;
	}
	LinkList m_begin()
	{
		return HeadNode;
	}
	LinkList m_end()
	{
		while (L->next != nullptr)
		{
			L = L->next;
		}
		return L;
	}
	m_Forward_List()
	{
		//初始化空表
		L = (LinkList)malloc(sizeof(Node));
		CurrentNodeSize = 0;
		HeadNode = nullptr;
		L->next = nullptr;
	}
	void m_Insert(DataType data)
	{
		//指针后移到尾端结点
		while (L->next!=nullptr)
		{
			L = L->next;
		}
		//初始化新结点
		LinkList p = (LinkList)malloc(sizeof(Node));
		/*LinkList p = new Node;*/
		p->m_data = data;
		//当前结点的指针域指向新结点
		L->next = p;
		//新结点的指针域指向nullptr
		p->next = nullptr;
		//当前结点后移置新结点
		L = p;
		//储存头结点
		if (HeadNode == nullptr)
			HeadNode = L;
		++CurrentNodeSize;
	}
	DataType operator[](int index)
	{
		L = HeadNode;
		for (int i = 0; i < index;++i)
		{
			L = L->next;
		}
		LinkList Result = L;
		L = HeadNode;
		return Result->m_data;
	}
	~m_Forward_List()
	{
		//从头结点开始free
		L = HeadNode;
		while(L!=nullptr)
		{
			LinkList temp = L->next;
			free(L);
			/*delete(L);*/
			L = nullptr;
			L = temp;
		}
	}

};

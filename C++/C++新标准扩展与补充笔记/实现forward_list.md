#include<iostream>
using namespace std;
template<typename DataType> class m_Forward_List{
public:
	//�������
	struct Node
	{
		//������
		DataType m_data;
		//ָ����
		Node* next;
	};
public:
	//������
	typedef Node* LinkList;  
	//����
	LinkList L;
	//ͷ���
	LinkList HeadNode;
	//��ǰ�������
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
		//��ʼ���ձ�
		L = (LinkList)malloc(sizeof(Node));
		CurrentNodeSize = 0;
		HeadNode = nullptr;
		L->next = nullptr;
	}
	void m_Insert(DataType data)
	{
		//ָ����Ƶ�β�˽��
		while (L->next!=nullptr)
		{
			L = L->next;
		}
		//��ʼ���½��
		LinkList p = (LinkList)malloc(sizeof(Node));
		/*LinkList p = new Node;*/
		p->m_data = data;
		//��ǰ����ָ����ָ���½��
		L->next = p;
		//�½���ָ����ָ��nullptr
		p->next = nullptr;
		//��ǰ���������½��
		L = p;
		//����ͷ���
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
		//��ͷ��㿪ʼfree
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

#ifndef __FORWARD__LIST
#define __FORWARD__LIST
#include<iostream>
using namespace std;
																/*嵌入式内存池实现单向链表*/
/*------------------内存池接口------------------
static myallocator m_allocator			 定义内存池对象,用于调用内存分配接口
static void*operator new(size_t size)    重载operator new 实现内存池内存分配接口的调用
static void operator delete(void*phead)  重载operator delete 实现内存词的伪回收接口调用 
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

/*-----------------内存词接口调用------------------
myallocator classname::m_allocator;	    classname类类型参数 调用作用域下静态内存分配接口
--------------------------------------------------*/
#define IMPLEMENT_ALLOCATOR(classname)\
myallocator classname::m_allocator;
/*------------------内存池实现--------------------*/
class myallocator {
public:
	//每次为内存池分配的内存倍数   
	static int multiple;
	//记录内存分配接口调用次数
	static int NewObjCount;
	//记录开辟内存总数量
	static int AllocatorCount;
	//内存池内存分配接口
	void*my_allocator(size_t& size) 
	{
		//初始化
		tmplink = nullptr;
		if (free_ptr == nullptr)
		{
			//标识内存池待开辟空间
			int capacity = multiple*size;
			//分配内存空间,tmlink记录新开辟内存空间的首地址
			tmplink = (obj*)malloc(capacity);
			//指向待分配的内存首地址
			free_ptr = tmplink;
			//遍历内存块实现内存链接
			for (int i = 0; i < multiple - 1; ++i)
			{
				//下移到后继内存块
				tmplink->next = (obj*)((char*)(tmplink)+size);
				//当前内存块指针域指向后继内存块
				tmplink = tmplink->next;
			}
			//尾部内存块指向空
			tmplink->next = nullptr;
			//记录开辟内存总数量
			++AllocatorCount;
		}
		//记录内存分配接口调用次数
		++NewObjCount;
		//获取当前未分配内存块首地址
		tmplink = free_ptr;   
		//指针后移指向下一块未分配内存块地址
		free_ptr = free_ptr->next;  
		//返回空闲内存块地址
		return tmplink;
	}
	void mydeallocator(void* phead)  //内存回收接口
	{
		((obj*)phead)->next = free_ptr;
		free_ptr = ((obj*)phead);
	}
private:
	//嵌入式指针
	struct obj
	{
		obj*next;
	};
	//定义结构体指针变量,用于实现链接内存,并用于返回空闲内存块首地址
	static obj* tmplink;
	//始终指向一块可分配内存链的地址,初始化指向空
	obj*free_ptr = nullptr;   
};
				//类外初始化
myallocator::obj* myallocator::tmplink = nullptr;
int myallocator::multiple = 50000;
int myallocator::NewObjCount = 0;
int myallocator::AllocatorCount = 0;


template<typename DataType> struct Node {
	//数据域
	DataType m_data;
	//指针域
	Node* next;
	//调用宏包含内存池接口
	CALL_MALLOCATOR_()   
};
template<typename DataType> IMPLEMENT_ALLOCATOR(Node<DataType>)
template<typename DataType> class m_List {
public:
	//声明链表类型
	typedef Node<DataType>* Link;
	//声明头指针
	Link L;
	//声明头结点
	Link HeaderNode;
	//记录链表长度
	int m_size=0;
	//用于遍历到尾结点,实现尾插结点
	Link m_Temp;
	//建立空表
	m_List()
	{
		//定义头指针
		//L = (Link)malloc(sizeof(Node<DataType>));
		L = new Node<DataType>;
		//定义头结点（用来统一尾插与首插方法）
		//HeaderNode = (Link)malloc(sizeof(Node<DataType>));
		HeaderNode = new Node<DataType>;
		//头结点指针域指向空
		HeaderNode->next = nullptr;
		//头指针指向头结点
		L->next = HeaderNode;
		//用于遍历到尾结点,实现尾插结点
		m_Temp = HeaderNode;
	}
	//尾插
	void m_push_back(DataType data)
	{
		//指针遍历到尾结点
		while (m_Temp->next != nullptr) m_Temp = m_Temp->next;
		//初始化新节点
		Link NewNode = new Node<DataType>;
/*-----------------------------------------------------------------------------*/
		/*cout << typeid(data).name() << endl;
		cout << typeid(NewNode->m_data).name() << endl;*/
		//string类型数据拷贝
		NewNode->m_data = data;                 //Error
/*------------------------------------------------------------------------------*/
		//新结点指针域指向空
		NewNode->next = nullptr;
		//新结点尾接链表
		m_Temp->next = NewNode;
		//链表结点数+1
		++m_size;
	}
	//头插
	void m_push_front(DataType data)
	{
		//定义新结点
		//Link NewNode = (Link)malloc(sizeof(Node<DataType>));
		Link NewNode = new Node<DataType>;
		NewNode->m_data = data;
		//新结点指针域指向后继节点
		NewNode->next = HeaderNode->next;
		//头结点指针域指向新结点
		HeaderNode->next = NewNode;
		//链表结点数+1
		++m_size;
	}
	//获取元素总量
	int m_list_size()
	{
		return m_size;
	}
	DataType operator[](int index)
	{
		//超出线性表长度,无效操作
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
	//析构释放内存
	~m_List()
	{
		//记录当前待释放指针
		Link m_free = L;
		//记录下一个待释放指针
		Link m_Next_free = m_free;
		while (m_free!= nullptr)
		{
			//记录下一个待释放指针
			m_Next_free = m_Next_free->next;
			//释放当前指针
			//free(m_free);
			delete(m_free);
			//指向待释放指针
			m_free = m_Next_free;
		}
	}
};
#endif
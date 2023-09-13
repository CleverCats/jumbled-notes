#ifndef _MYVECTOR__
#define _MYVECTOR__

template<typename T>
class my_vector                   //此时的类已经是一个类模板的类的,在继承或者类外用到my_vector时,必须采用my_vector<T>表明这是一个类模板
{
public:
	typedef T* m_iterator;			    	 //自定义T*别名 m_iterator作为迭代器类指针
private:
	int capacity;					     	 //初始容量
	int size=0;							     //元素总数
	m_iterator array = new T[capacity];		 //初始容器
public:
	void m_swap(my_vector<T> &vtr)		     //交换容器
	{
		m_iterator temp_arr =vtr.array;		
		int temp_capacity = vtr.capacity;
		int temp_size = vtr.size;

		vtr.array = this->array;
		vtr.capacity = this->capacity;
		vtr.size = this->size;

		this->array = temp_arr;
		this->capacity = temp_capacity;
		this->size = temp_size;
		
	};
	my_vector(int m_capacity = 4):capacity(m_capacity){};  //初始化构造容量;
	inline int m_size() { return size; };    //返回总数
	inline int m_capacity() { return capacity; };		   //返回容量
	void m_clear()										   //清空容器
	{
		if (array != nullptr)   //*****  报错  堆异常 *****
		{
			delete[]array;
			array = nullptr;
		}
		this->size = 0;
		this->capacity = 0;
	}
	m_iterator m_push_back(T m);			 //进队列
	
	inline m_iterator m_pop_back()			 //出队列
	{
		this->size = this->size - 1;         //假装尾删
		return &array[size-1];
	}
	 inline m_iterator begin()				   		       //返回起始迭代器
	{ 
		return &array[0];
	}
	 inline m_iterator end()							   //返回结束迭代器
	 {	  
		 return &array[size];
	 }
	my_vector& operator=(const my_vector& vtr);			   //赋值拷贝
	inline T& operator[](int idx){ return array[idx]; }	   //重载[]返回指定位置元素
	virtual~my_vector();							   	   //析构函数
};
template<typename T>
my_vector<T>::~my_vector()
{
														   //释放内存
	if (array != nullptr)
	{
		delete[]array;
		array = nullptr;
	}
		size = 0;
		capacity = 0;
}
template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector& vtr) //注意:类外实现需要添加模板参数列表
{
	if (this == &vtr) return *this;						   //自我赋值无效
	if (array != nullptr)								   //释放原始内存
	{
		delete[]array;
		array = nullptr;
	}
	capacity = vtr.size;								   //初始化
	size = vtr.size;

	array = new T[capacity];              
	
	for (; index < size; index++)						   //拷贝
	{
		array[index] = vtr.array[index];
	}
	return *this;
}
template<typename T>
//类外使用typedef声明的别名 需要加typename接具体作用域下的别名
typename my_vector<T>::m_iterator  my_vector<T>::m_push_back(T m)   
{
	if (size < capacity)
	{
		array[size] = m;
		++size;											   //元素总数加一
	}
	else
	{
		this->capacity = capacity * 2+1;				    //扩充容器容量(*2)
		typename m_iterator temp = new T[capacity];		    //临时内存
		for (int i = 0; i < size; i++)
		{
			temp[i] = array[i];
		}
		delete[]array;     //释放原内存
		array = temp;      //交接内存
		temp = nullptr;    //置空临时内存
		array[size] = m;
		++size;			   //元素总数加一
	}
	return &array[size];
}

#endif
#include<iostream>
#include<string>
#include<vector>   //vector容器头文件
#include<algorithm>  //STL算法使用必须包含的头文件
using namespace std;  
void print(int Ve)
{
	cout << Ve << endl;
}
void test()
{
	vector<int>v;  //定义一个整形容器,可以看作数组
	v.push_back(10);   //push_back 插入语法
	v.push_back(11);
	v.push_back(12);
	v.push_back(13);
	v.push_back(14);
	v.push_back(15);                             //迭代器是算法与容器之间的粘合剂,通过它才算法才能访问容器中的元素
	v.push_back(16);   
							//可以把迭代器看作一个指针
	            //通过迭代器访问容器中的数据 ,每个容器都有自己的迭代器,通过迭代器来遍历容器中的元素
	cout << "第一种方法" << endl;
	//vector<int>::iterator 这个容器的迭代器的类型
	vector<int>::iterator Vbegin = v.begin();  //begin()是vector的一个迭代器(看作指针),指向容器的第一个元素
	vector<int>::iterator Vend = v.end();        //end()是vector的一个迭代器(看作指针), 指向容器的***最后一个元素的下一位***
	while (Vbegin != Vend)
	{
		cout << *Vbegin << endl;
		Vbegin++;
	}
	cout << "第二种方法" << endl;

	for (vector<int>::iterator Vbegin = v.begin(); Vbegin != v.end(); Vbegin++)
	{
		cout << *Vbegin << endl;
	}
	
	cout << "第三种方法" << endl; //利用STL提供的遍历算法 这里用了for_each遍历算法
	for_each(v.begin(), v.end(), print);  
//采用的回调的技术  原理本质是一个for循环  取出每个数据传递 即将*v.begin()作为实参传递给print 即print(*v.begin()),然后v.begin()++直到v.begin=v.end;
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}

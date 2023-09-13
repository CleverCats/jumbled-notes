#include<iostream>      //swap两容器进行互换的操作,可以达到收缩内存的效果
#include<string>
#include<vector>
using namespace std;
void test()
{
	vector<int>v;
	for (int i = 0; i < 99999; i++)
	{
		v.push_back(i);
	}
	cout << "v的容量:" << v.capacity() << "  " << "v的大小:" << v.size() << endl;
	v.resize(3);                        
	cout << "v的容量:" << v.capacity() << "  " << "v的大小:" << v.size() << endl; //此时容量不变造成空间浪费
	vector<int>(v).swap(v);  //调用了一个匿名对象的拷贝操作(拷贝后初始化的容量等于大小),拷贝结束后匿名对象的capacity和size都是v.size()
	                       //交换后匿名对象的内存会自动回收   
	cout << "v的容量:" << v.capacity() << "  " << "v的大小:" << v.size() << endl;
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}
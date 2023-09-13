strcpy(s1,s2);strcpy函数的意思是：把字符串s2中的内容copy到s1中，连字符串结束标志也一起copy.
这样s1在内存中的存放为：ch\0;
在cout<<s1<<endl时，结果为ch;事实上，在内存里面是这样的存储结构：ch\0na
如果说s1的长度是6，那是错误的.你没有弄清strlen与sizeof的意思。
strlen函数的意思是测试字符串的字符长度，不含字符串结束标志的。
sizeof是个运算符，它的结果是字符串在内存中的所占字节大小，它要把\0算进去的。

strcpy函数原型1
char * strcpy(char *a,char *b)
{ while((*(a++)=*(b++))!=0);return a;}
strcpy函数原型2
char *strcpy(char *strDest, const char *strSrc);//strDest为目标,strSrc为源
{
     assert((strDest!=NULL) && (strSrc !=NULL)); //如果两个为空则不用复制,直接中止
     char *address = strDest;       //用address指向strDest开始地址
     while( (*strDest++ = * strSrc++) != ‘\0’ ) //复制,直到源串结束;
        NULL ; //空操作
     return address ;    //返回strDest开始地址                       
     }
}
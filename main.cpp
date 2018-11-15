#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void func3(int& a)
{
    printf("func3 = %d\n",a);
	int* c = (int*)malloc(sizeof(int)); // 调用malloc
	*c = 10;
	printf("p = %p\n",c);
///	while(1)
//	{}
	free(c);
}

void func2(int& a)
{
    printf("func2 = %d\n",a);
    func3(a);
}

void func1(int& a)
{
    printf("func1 = %d\n",a);
    func2(a);
}
   
void func(int& a)
{  
    printf("func = %d\n",a);
    func1(a);
}  
   
int main(int argn,char** argv)
{
    int a=4;
    func(a);
    printf("main=%d\n",a);
}   
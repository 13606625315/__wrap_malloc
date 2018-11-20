#include <stdio.h>
#include <stdlib.h>
extern "C" void* _start ; 
extern "C" void* _fini ; 

#define SIZE 4
#define CALLSIZE 5
#define CALL 0xe8
extern "C" {

void addstack(int* tmp,int* p)
{
	for(int i = 0;i< SIZE;i++)
	{
		p[i] = 0;
		
	}
	
	int* fp[2] = {0,0};
	for(int i=0; i < SIZE; i++)
	{
		while(1)
		{	
			if((void*)(*tmp)> &_start && (void*)(*tmp) < &_fini)
			{
				if(*(int*)(*tmp - CALLSIZE) & 0xff == CALL);
				{
					p[i] = *tmp;
					fp[0] = fp[1];
					fp[1] = tmp - 1;
					printf("p[%d] = %p\n",i,p[i]);
					//printf("fp[0] = %p,fp[1] == %p  %p  \n",fp[0],fp[1],*fp[1]);
					break;
				}
			}
			tmp = tmp + 1;
		}
		
		if(fp[0]!=0 && *fp[0] != (int)fp[1])
		{
			printf("reach top\n");
			break;
		}
		tmp = tmp + 1;
	}
}

void* __real_malloc(size_t size); 
void* __wrap_malloc(size_t size) 
{
	size += SIZE * sizeof(void*);
	int* p = (int*)__real_malloc(size);
	int tmp = 0;
	addstack(&tmp,p);
	
    return p + SIZE; 
}

void* __real_free(void* ptr);
void* __wrap_free(void* p)
{
	p = (int*)p - SIZE;
	return __real_free(p);
}













}
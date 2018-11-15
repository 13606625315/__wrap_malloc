#include <stdio.h>
#include <stdlib.h>
extern "C" void* _start ; 
extern "C" void* _fini ; 

extern "C" {

void addstack(int* tmp,int* p)
{
	p[0] = 0;p[1] = 0;p[2] = 0;p[3] = 0;
	
	for(int i=0; i < 4; i++)
	{
		while(1)
		{	
			if((void*)(*tmp)> &_start && (void*)(*tmp) < &_fini)
			{
				
				int* call = tmp - 1;
				if(((*call) & 0xff000000) == 0xe8000000);
				{
					printf("break *tmp = %p\n",p);
					p[i] = *tmp;
					break;
				}
			}
			tmp = tmp + 1;
		}
		tmp = tmp + 1;
	}
}

void* __real_malloc(size_t size); 
void* __wrap_malloc(size_t size) 
{
	size += 4 * sizeof(void*);
	int* p = (int*)__real_malloc(size);
	int tmp = 0;
	addstack(&tmp,p);
	
    return p + 4; 
}

void* __real_free(void* ptr);
void* __wrap_free(void* p)
{
	p = p - 4*4;
	return __real_free(p);
}













}
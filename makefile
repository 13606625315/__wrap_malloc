CC = g++ 

objects = main.o malloc.o 

server: $(objects)
	cc -g -o test $(objects) -Wl,--wrap=malloc -Wl,--wrap=free -m32
	
main.o:
	cc -c main.cpp -m32
	
malloc.o:
	cc -c malloc.cpp -m32
#比较稳健的clean做法，表示clean是一个伪目标
.PHONY: clean

#前面-的意思是：也许某些文件出现问题，忽略，继续执行
clean:
	-rm test $(objects) 
	
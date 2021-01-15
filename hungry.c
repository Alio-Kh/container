	
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void){
	int i=0;
	int *p;
	while(1){
	    i++;
	    // Allocate 1Mb
	    p= (int *)malloc(1000000);
	    if(p)
		printf("%dMB Allocated\n",i);
	    else
		printf("out of memory\n");
	    //  Fill a block of memory with a particular value
	    memset(p,0,1000000);
	}
	return 0;
}

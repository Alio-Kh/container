	
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
            int i=0;
            int *p;
            while(1){
                        i++;
                        p= (int *)malloc(1000000);
                        if(p)
                                    printf("1MB allocated i=%d\n",i);
                        else
                                    printf("out of memory\n");
                        memset(p,0,1000000);
                       // sleep(1);
       }
       return 0;
}

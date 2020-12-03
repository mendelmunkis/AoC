#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    char buf[40];
    char *p;
    char policy;
    int min,max,count;
    FILE * fp;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 40, fp) != NULL)
    {
        min=strtol(buf,&p,10);
        max=strtol(p+1,&p,10);
        count=0;
        p++;
        policy=*p;
        p+=2;
        if(part ==1)
        {
            while(*p!='\0')
            {
                if(*p==policy)
                    count++;
                p++;
            }
            if((count<=max)&&(count>=min))
                 result++;
        }
        else
            if((*(p+min)==policy)!=(*(p+max)==policy))
                result++;
    }
    printf("%d\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int comp (const void *p1, const void *p2);

int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    char buf[16];
    int input[200];
    int x=0,temp;
    int y=199;
    int *z=&x, *p=&temp;
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
    while(fgets(buf, 16, fp) != NULL)
    {
        input[x]=atoi(buf);
        x++;
    }
    qsort(input,200,sizeof(int),comp);
    x=0;
    if (part==1)
    {
        while(input[x]+input[y]!=2020)
            if(input[x]+input[y] > 2020)
                y--;
            else
                x++;
       result=input[x]*input[y];
    }
    else
    {
        while(1)
        {
            temp = 2020-(input[x]+input[y]);
            if ((z=bsearch(p,input+x,y-x,sizeof(int),comp))!=NULL)
                break;
            else if(input[x]+(2*input[y]) <= 2020)
                x++;
            else
                y--;
        }
        result=input[x]*input[y]* *z;
    }
    printf("%d\n",result);
    return 0;
}
static int comp (const void *p1, const void *p2)
{
    int a =*(int *)p1;
    int b =*(int *)p2;
    if(a<b)
    return -1;
    if(a>b)
    return 1;
    return 0;
}

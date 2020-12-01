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
    int x=0, z=0;
    int y=199;
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
        while(input[x]+input[y]+input[z]!=2020)
            if(input[x]+input[y]+input[z] > 2020)
            {
                y--;
                z=x+1;
            }else if(z=y)
                z=++x+1;
            else
                z++;
        result=input[x]*input[y]*input[z];
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

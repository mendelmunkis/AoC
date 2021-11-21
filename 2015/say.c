#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char in[10000000];
char out[10000000];

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    int num, run, len, y, x=0;
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
        while(x<16 && buf[x]!='\0' && buf[x]!='\n')
        {
            in[x]=buf[x]-48;
            x++;
        }
    }
    if(part==1)
        len=20;
    else
        len=25;
    for(int i =0; i<len; i++)
    {
        run=x=y=0;
        num=in[x];
        while(num!=0)
        {
            if(in[x]==num)
                run++;
            else
            {
                out[y++]=run;
                out[y++]=num;
                run=1;
                num=in[x];
            }
            x++;
        }
        run=x=y=0;
        num=out[x];
        while(num!=0)
        {
            if(out[x]==num)
                run++;
            else
            {
                in[y++]=run;
                in[y++]=num;
                run=1;
                num=out[x];
            }
            x++;
        }
    }
    for(x=0; in[x]!=0; x++);
    result=x;
    printf("%ld\n",result);
    return 0;
}

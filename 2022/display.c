#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    int x=1,c=0,op;
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
    for(int cycle=1;cycle<=240;cycle++)
    {
        if(part==1)
        {
            if(cycle%40==20)
                result+=cycle*x;
        }
        else
        {
            if((cycle%40==x)||(cycle%40==(x+1))||(cycle%40==(x+2)))
                printf("#");
            else
                printf(".");
            if(!(cycle%40))
                printf("\n");
        }
        if(c)
        {
            x+=op;
            c--;
        }
        else
        {
            fgets(buf, 16, fp);
            if(buf[0]=='a')
            {
                c=1;
                op=atoi(buf+4);
            }
        }
    }
    printf("%ld\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myround (int a);

void main (int argc, char * argv[])
{
    long result=0;
    int part=0;
    int toround;
    char buf[16];
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    while(fgets(buf, 16, fp) != NULL)
    {
        toround = atoi(buf);
        if(part)
            while(toround > 0)
            {
                toround=myround(toround);
                if(toround > 0)
                    result+=toround;
            }
        else
        {
            toround=myround(toround);
            if(toround > 0)
                result+=toround;
        }
        memset(buf, 0, 16);
    }
    printf("%d\n",result);
}
int myround (int a)
{
    a/=3;
    a-=2;
    return a;
}

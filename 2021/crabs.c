#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CRABS 1000

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=7654444444444456, check;
    int part=1;
    char buf[4000], *bufp;
    FILE * fp;
    int crabs[CRABS],tmp;
    int crab=0;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 4000, fp) != NULL)
    {
        bufp=buf;
        for(int i =0;*bufp != '\0'; i++)
        {
            switch(*bufp)
            {
              case '\n':
                  bufp++;
                  break;
              case '\0':
                  break;
              case ',':
                  bufp++;
              default:
                crabs[i]=strtol(bufp,&bufp,10);
                crab++;
            }
        }
    }
    for(int i=0;i<10000;i++)
    {
        check=0;
        for(int j=0;j<crab;j++)
        {
            tmp=abs(crabs[j]-i);
            if(part==2)
                tmp=tmp*(tmp+1)/2;
            check+=tmp;
        }
        if(check<result)
        {
            result=check;
            //result=i;
        }
    }
    printf("%ld\n",result);
    return 0;
}

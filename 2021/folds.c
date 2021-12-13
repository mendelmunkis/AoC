#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[18], *bufp;
    char dots[1500][1500]={0};
    int x,y,maxx=0,maxy=0,dir,crease;
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
    while(fgets(buf, 18, fp) != NULL)
    {
        bufp=buf;
        if(*bufp=='\n')
            break;
        x=strtol(bufp,&bufp,10);
        y=strtol(bufp+1,&bufp,10);
        dots[y][x]=1;
        if(x>maxx)
            maxx=x;
        if(y>maxy)
            maxy=y;
    }
    maxx++;
    maxy++;
    while(fgets(buf, 18, fp) != NULL)
    {
        bufp=strtok(buf," ");
        bufp=strtok(NULL," ");
        bufp=strtok(NULL,"=");
        if(*bufp=='x')
            dir=1;
        if(*bufp=='y')
            dir=0;
        bufp=strtok(NULL," ");
        crease=strtol(bufp,NULL,10);
        for(int i=0;(crease+i)<(dir==0?maxy:maxx);i++)
            for(int j=0;j<(dir==1?maxy:maxx);j++)
                if(dots[dir?j:(crease+i)][dir?(crease+i):j])
                    dots[dir?j:(crease-i)][dir?(crease-i):j]=1;
        if(dir)
            maxx=crease;
        else
            maxy=crease;
        if(part==1)
        {
            for(x=0;x<maxx;x++)
                for(y=0;y<maxy;y++)
                    if(dots[y][x])
                        result++;
            break;
        }
    }
    if(part==2)
            for(y=0;y<maxy;y++)
        {
        for(x=0;x<maxx;x++)
                if(dots[y][x])
                    printf("*");
                else
                   printf(" ");
            printf("\n");
        }
    printf("%ld\n",result);
    return 0;
}

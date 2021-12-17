#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[40], *bufp;
    FILE * fp;
    int minx, miny, maxx, maxy, high=0,tmp;
    int x,y,currx,curry,vx,vy;
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
        bufp=strtok(buf,"=");
        bufp=strtok(NULL,".");
        minx=strtol(bufp,&bufp,10);
        maxx=strtol(bufp+2,&bufp,10);
        bufp=strtok(NULL,"=");
        bufp=strtok(NULL,".");
        miny=strtol(bufp,&bufp,10);
        maxy=strtol(bufp+2,&bufp,10);
    }
    for(x=0;x<1000;x++)
        for(y=-1000;y<1000;y++)
        {
            vx=x;
            vy=y;
            currx=curry=tmp=0;
            while((currx<=maxx)&&(curry>miny))
            {
                currx+=vx;
                curry+=vy;
                if(vx)
                    if(abs(vx)==vx)
                        vx--;
                    else
                        vx++;
                vy--;
                if(!vy)
                    tmp=curry;
                if((currx>=minx)&&(curry<=maxy)&&(currx<=maxx)&&(curry>=miny))
                {
                    result++;
                    if(tmp>high)
                        high=tmp;
                    break;
                }
            }
        }
    if(part==1)
        result=high?high:0; //ternary covers edgecaase where all solutions have vy<=0;
    printf("%ld\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    int depth,window;
    int windowa=0,windowb=0,windowc=0,windowd,i=1;
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
    fgets(buf, 16, fp);
    depth=strtol(buf,NULL,10);
    window=depth;
    if(part==2)
    {
        windowa+=depth;
        fgets(buf, 16, fp);
        depth=strtol(buf,NULL,10);
        windowa+=depth;
        windowb+=depth;
        fgets(buf, 16, fp);
        depth=strtol(buf,NULL,10);
        windowa+=depth;
        windowb+=depth;
        windowc+=depth;
        window=windowa;
        windowa=0;
    }
    while(fgets(buf, 16, fp) != NULL)
    {
    depth=strtol(buf,NULL,10);
    if(part==1)
    {
        windowd=depth;
    }
    else
    {
        windowa+=depth;
        windowb+=depth;
        windowc+=depth;
        if(!i)
        {
            i++;
            windowd=windowa;
            windowa=0;
        }
        else if(i==1)
        {
            i++;
            windowd=windowb;
            windowb=0;
        }
        else
        {
            windowd=windowc;
            windowc=i=0;
        }
    }
    if(window<windowd)
        result++;
    window=windowd;
    }
    printf("%ld\n",result);
    return 0;
}

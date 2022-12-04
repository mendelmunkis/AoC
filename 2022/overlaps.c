#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    char *p;
    int starta,startb,enda,endb;
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
        p=strtok(buf,"-");
        starta=atoi(p);
        p=strtok(NULL,",");
        enda=atoi(p);
        p=strtok(NULL,"-");
        startb=atoi(p);
        p=strtok(NULL,",");
        endb=atoi(p);
        if(part==1)
        {
            if((starta<=startb&&endb<=enda)||(starta>=startb&&endb>=enda))
                result++;
        }
        else
            if(!((starta<startb&&enda<startb)||(starta>startb&&starta>endb)))
                result++;
    }
    printf("%ld\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[150];
    char east[137][139];
    char south[137][139];
    int x=0,y,flag=1;
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
    while(fgets(buf, 150, fp) != NULL)
    {
        memcpy(east[x++],buf,139);
    }
    for(;flag;result++)
    {
        flag=0;
        for(x=0;x<137;x++)
            for(y=0;y<139;y++)
            {
                if((east[x][y]=='>')&&(east[x][(y+1)%139]=='.'))
                {
                    flag=1;
                    south[x][y]='.';
                    south[x][(y+1)%139]='>';
                    y++;
                }
                else
                    south[x][y]=east[x][y];
            }
        for(y=0;y<139;y++)
            for(x=0;x<137;x++)
            {
                if((south[x][y]=='v')&&(south[(x+1)%137][y]=='.'))
                {
                    flag=1;
                    east[x][y]='.';
                    east[(x+1)%137][y]='v';
                    x++;
                }
                else
                    east[x][y]=south[x][y];
            }
    }

    printf("%ld\n",result);
    return 0;
}

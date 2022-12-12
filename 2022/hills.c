#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char map[150][150];
int dist[150][150];

void check(int x, int y);
void check2(int x, int y);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    char buf[160];
    char sx,sy,ex,ey;
    int part=1;
    int x=1;
    FILE * fp;
    memset(dist,50000,sizeof(dist));
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    memset(map,part==1?50:-50,sizeof(map));
    while(fgets(buf, 160, fp) != NULL)
    {
        for(int y=0;buf[y]!='\n';y++)
            if(buf[y]=='S')
            {
                map[x][y+1]=1;
                sx=x;
                sy=y+1;
            }
            else if(buf[y]=='E')
            {
                map[x][y+1]=26;
                ex=x;
                ey=y+1;
            }
            else
                map[x][y+1]=buf[y]-96;
            x++;
    }
    if(part==1)
    {
        dist[sx][sy]=0;
        check(sx,sy);
        result=dist[ex][ey];
    }
    else
    {
        dist[ex][ey]=0;
        check2(ex,ey);
        result=dist[sx][sy];
        for(int x=1;x<150;x++)
            for(int y=1;y<150;y++)
                if((map[x][y]==1) && (dist[x][y]<result))
                    result=dist[x][y];

    }
    printf("%ld\n",result);
    return 0;
}

void check(int x, int y)
{
    if((map[x+1][y]<=map[x][y]+1)&&(dist[x+1][y]>dist[x][y]+1))
    {
        dist[x+1][y]=dist[x][y]+1;
        check(x+1,y);
    }
    if((map[x-1][y]<=map[x][y]+1)&&(dist[x-1][y]>dist[x][y]+1))
    {
        dist[x-1][y]=dist[x][y]+1;
        check(x-1,y);
    }
    if((map[x][y+1]<=map[x][y]+1)&&(dist[x][y+1]>dist[x][y]+1))
    {
        dist[x][y+1]=dist[x][y]+1;
        check(x,y+1);
    }
    if((map[x][y-1]<=map[x][y]+1)&&(dist[x][y-1]>dist[x][y]+1))
    {
        dist[x][y-1]=dist[x][y]+1;
        check(x,y-1);
    }
}
void check2(int x, int y)
{
    if((map[x+1][y]+1>=map[x][y])&&(dist[x+1][y]>dist[x][y]+1))
    {
        dist[x+1][y]=dist[x][y]+1;
        check2(x+1,y);
    }
    if((map[x-1][y]+1>=map[x][y])&&(dist[x-1][y]>dist[x][y]+1))
    {
        dist[x-1][y]=dist[x][y]+1;
        check2(x-1,y);
    }
    if((map[x][y+1]+1>=map[x][y])&&(dist[x][y+1]>dist[x][y]+1))
    {
        dist[x][y+1]=dist[x][y]+1;
        check2(x,y+1);
    }
    if((map[x][y-1]+1>=map[x][y])&&(dist[x][y-1]>dist[x][y]+1))
    {
        dist[x][y-1]=dist[x][y]+1;
        check2(x,y-1);
    }
}

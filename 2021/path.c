#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUARE 100

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[105], *bufp;
    int spots[SQUARE*5][SQUARE*5][2];
    int x=0,y,flag=1,end,tile;
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
    memset(spots,10,50*SQUARE*SQUARE*sizeof(int));
    while(fgets(buf, 105, fp) != NULL)
    {
        bufp=buf;
        for(int i=0;*bufp!='\n';i++)
            spots[x][i][0]=(*(bufp++))-48;
        x++;
    }
    end=(part==1?SQUARE-1:SQUARE*5-1);
    if(part==2)
        for(x=0;x<=end;x++)
            for(y=0;y<=end;y++)
            {
                tile=x/SQUARE+y/SQUARE;
                spots[x][y][0]=spots[x%SQUARE][y%SQUARE][0]+tile;
                if(spots[x][y][0]>9)
                    spots[x][y][0]-=9;
            }
    spots[end][end][1]=spots[end][end][0];
    while(flag)
    {
        flag=0;
        for(x=end;x>=0;x--)
            for(y=end;y>=0;y--)
            {
                if((x<end)&&(spots[x+1][y][1]+spots[x][y][0]<spots[x][y][1]))
                {
                    flag=1;
                    spots[x][y][1]=spots[x+1][y][1]+spots[x][y][0];
                }
                if((x)&&(spots[x-1][y][1]+spots[x][y][0]<spots[x][y][1]))
                {
                    flag=1;
                    spots[x][y][1]=spots[x-1][y][1]+spots[x][y][0];
                }
                if((y<end)&&(spots[x][y+1][1]+spots[x][y][0]<spots[x][y][1]))
                {
                    flag=1;
                    spots[x][y][1]=spots[x][y+1][1]+spots[x][y][0];
                }
                if((y)&&(spots[x][y-1][1]+spots[x][y][0]<spots[x][y][1]))
                {
                    flag=1;
                    spots[x][y][1]=spots[x][y-1][1]+spots[x][y][0];
                }
            }
    }
    result=spots[0][0][1]-spots[0][0][0];
    printf("%ld\n",result);
    return 0;
}

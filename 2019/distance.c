#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void genlines(FILE * fp, int grid[40000][40000][2]);

int maxx=0, maxy=0, minx=39999, miny=39999;

int main (int argc, char * argv[])
{
    char part=1;
    int x=0, y=0,ans=9999999;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    static int grid[40000][40000][2] ={0};
    genlines(fp, grid);
    maxx++;
    maxy++;
    if((maxx>40000)||(maxy>40000))
        printf("Error: Lines are bigger then grid.\n");
    if(part == 1)
        for(x=minx;x<maxx;x++)
            for(y=miny;y<maxy;y++)
                if(grid[x][y][0] == 3)
                    if((abs(x-10000)+abs(y-10000) < ans))
                        ans = abs(x-10000)+abs(y-10000);
    if(part==2)
        for(x=minx;x<maxx;x++)
            for(y=miny;y<maxy;y++)
                if(grid[x][y][0] == 3)
                    if(grid[x][y][1] < ans)
                        ans = grid[x][y][1];
    if(ans < 999999)
        printf("%d\n", ans);
    else
        printf("Error: Answer out of range.\n");
    return(0);
}

void genlines(FILE *fp, int grid[40000][40000][2])
{
    char buf[7], line=1;
    int x =10000, y=10000, length=0, steps=1, size;
    while(fgets(buf, 8, fp)!= NULL)
    {
        size = atoi(&buf[1]);
        switch(buf[0])
        {
            case 'U':
                while(length <size)
                {
                    x++;
                    if(!(grid[x][y][0] & line))
                    {
                        grid[x][y][0] += line;
                        grid[x][y][1] +=steps;
                    }
                    length++;
                    steps++;
                }
                length =0;
                break;
            case 'D':
                while(length <size)
                {
                    x--;
                    if(!(grid[x][y][0] & line))
                    {
                        grid[x][y][0] += line;
                        grid[x][y][1] +=steps;
                    }
                    length++;
                    steps++;
                }
                length =0;
                break;
            case 'L':
                while(length <size)
                {
                    y--;
                    if(!(grid[x][y][0] & line))
                    {
                        grid[x][y][0] += line;
                        grid[x][y][1] +=steps;
                    }
                   length++;
                   steps++;
                }
                length =0;
                break;
            case 'R':
                while(length <size)
                {
                    y++;
                    if(!(grid[x][y][0] & line))
                    {
                        grid[x][y][0] += line;
                        grid[x][y][1] +=steps;
                    }
                   length++;
                   steps++;
                }
                length =0;
                break;
            case '\n':
                x = y =10000;
                length=0;
                steps=1;
                line++;
                break;
            default:
                printf("Error: Bad Direction.\n");
                exit(1);
        }
        if(x>maxx)
            maxx=x;
        if(x<minx)
            minx=x;
        if(y>maxy)
            maxy=y;
        if(y<miny)
            miny=y;
    }
}

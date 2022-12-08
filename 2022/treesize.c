#include <stdio.h>
#include <stdlib.h>
#include <string.h>


signed char grid[102][102];

int check(int part, int a, int b);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    char buf[105];
    int part=1;
    int x=1,out;
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
    memset(grid,-5,sizeof(grid));
    while(fgets(buf, 105, fp) != NULL)
    {
        for(int y=0;buf[y]!='\n';y++)
            grid[x][y+1]=buf[y]-48;
        x++;
    }
    for(x=1;grid[x][1]!=-5;x++)
        for(int y=1;grid[x][y]!=-5;y++)
        {
            out=check(part, x,y);
            if(part==1)
                result+=out;
            else if(out>result)
                result=out;
        }
    printf("%ld\n",result);
    return 0;
}

int check(int part, int a, int b)
{
    int x,y,sum,flag;
    sum=1;
    flag=0;
    x=a;
    for(y=b+1;grid[x][y]<grid[a][b];y++)
        if(grid[x][y]==-5)
        {
            y--;
            flag =1;
            break;
        }
    sum*=(y-b);
    for(y=b-1;grid[x][y]<grid[a][b];y--)
        if(grid[x][y]==-5)
        {
            y++;
            flag =1;
            break;
        }
    sum*=(b-y);
    y=b;
    for(x=a-1;grid[x][y]<grid[a][b];x--)
        if(grid[x][y]==-5)
        {
            x++;
            flag =1;
            break;
        }
    sum*=(a-x);
    for(x=a+1;grid[x][y]<grid[a][b];x++)
        if(grid[x][y]==-5)
        {
            x--;
            flag =1;
            break;
        }
    sum*=(x-a);
    return part==1?flag:sum;
}

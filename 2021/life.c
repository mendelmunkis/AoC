#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[105], *bufp;
    char key[515];
    char grid[300][300]={0};
    char out[300][300];
    int x=100,y;
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
    fgets(key, 515, fp);
    fgets(buf, 105, fp);
    while(fgets(buf, 105, fp) != NULL)
    {
        bufp=buf;
        for(y=100;*bufp!='\n';y++)
            grid[x][y]=*(bufp++)=='#'?1:0;
        x++;
    }
    for(int i=0;i<515;i++)
        key[i]=key[i]=='#'?1:0;
    for(int i=0;i<(part==1?1:25);i++)
    {
        for(x=1;x<299;x++)
            for(y=1;y<299;y++)
                out[x][y]=key[(grid[x-1][y-1]<<8)+(grid[x-1][y]<<7)+(grid[x-1][y+1]<<6)+(grid[x][y-1]<<5)+(grid[x][y]<<4)+(grid[x][y+1]<<3)+(grid[x+1][y-1]<<2)+(grid[x+1][y]<<1)+(grid[x+1][y+1])];
        for(x=1;x<299;x++)
            for(y=1;y<299;y++)
                grid[x][y]=key[(out[x-1][y-1]<<8)+(out[x-1][y]<<7)+(out[x-1][y+1]<<6)+(out[x][y-1]<<5)+(out[x][y]<<4)+(out[x][y+1]<<3)+(out[x+1][y-1]<<2)+(out[x+1][y]<<1)+(out[x+1][y+1])];
    }
    for(x=50;x<250;x++)
        for(y=50;y<250;y++)
            if(grid[x][y])
                result++;
    printf("%ld\n",result);
    return 0;
}

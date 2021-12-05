#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[20], *bufp;
    int grid[1000][1000]={0};
    int lines[500][4]={0};
    int i=0, tmp,a;
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
    while(fgets(buf, 20, fp) != NULL)
    {
        bufp=buf;
        lines[i][0]=strtol(bufp,&bufp,10);
        lines[i][1]=strtol(bufp+1,&bufp,10);
        lines[i][2]=strtol(bufp+3,&bufp,10);
        lines[i][3]=strtol(bufp+1,&bufp,10);
        i++;
    }
    for(i=0;i<500;i++)
    {
        if(lines[i][0]==lines[i][2])
        {
            if(lines[i][1]>lines[i][3])
            {
                tmp=lines[i][3];
                lines[i][3]=lines[i][1];
                lines[i][1]=tmp;
            }
            for(int z =lines[i][1];z <= lines[i][3];z++)
                grid[lines[i][0]][z]++;
        }
        else if(lines[i][1]==lines[i][3])
        {
            if(lines[i][0]>lines[i][2])
            {
                tmp=lines[i][2];
                lines[i][2]=lines[i][0];
                lines[i][0]=tmp;
            }
            for(int z =lines[i][0];z <= lines[i][2];z++)
                grid[z][lines[i][1]]++;
        }
        else if(part==2)
        {
            if(lines[i][0]>lines[i][2])
            {
                tmp=lines[i][3];
                lines[i][3]=lines[i][1];
                lines[i][1]=tmp;
                tmp=lines[i][0];
                lines[i][0]=lines[i][2];
                lines[i][2]=tmp;
            }
            for(int z=lines[i][0], a=lines[i][1];z <= lines[i][2];z++)
            {
                grid[z][a]++;
                if(lines[i][1]<lines[i][3])
                    a++;
                else
                    a--;
            }
        }
    }
    for(int x=0;x<1000;x++)
        for(int y=0;y<1000;y++)
            if(grid[x][y]>=2)
                result++;
    printf("%ld\n",result);
    return 0;
}

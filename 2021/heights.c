#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char map [102][102];

int wall(int i, int j);

int cmp(const void *a, const void*b);

int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long result=0;
    int part=1;
    char buf[105], *bufp;
    int basins[300]={0};
    int i,j=1,x=0;
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
    memset(map, 9, 102*102);
    while(fgets(buf, 105, fp) != NULL)
    {
        bufp=buf;
        if(*bufp=='\n')
            break;
        for(i=1;i<101;i++)
            map[j][i]=*(bufp++)-48;
        j++;
    }
    for(i=1;i<101;i++)
        for(j=1;j<101;j++)
            if(map[i][j]!=9)
                if(part==1)
                {
                    if((map[i][j]<map[i-1][j])&&(map[i][j]<map[i][j-1])&&(map[i][j]<map[i][j+1])&&(map[i][j]<map[i+1][j]))
                        result+=map[i][j]+1;
                }
                else
                {
                    basins[x++]=wall(i,j);
                }
    if(part==2)
    {
        qsort(basins,300,sizeof(int), cmp);
        result=basins[299]*basins[298]*basins[297];
    }
    printf("%lu\n",result);
    return 0;
}

int wall(int i, int j)
{
    int x=1;
    map[i][j]=9;
    if(map[i+1][j]!=9)
        x+=wall(i+1,j);
    if(map[i-1][j]!=9)
        x+=wall(i-1,j);
    if(map[i][j+1]!=9)
        x+=wall(i,j+1);
    if(map[i][j-1]!=9)
        x+=wall(i,j-1);
    return x;
}

int cmp(const void *a, const void*b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    if (x <y)
        return -1;
    if (x >y)
        return 1;
    return 0;
}

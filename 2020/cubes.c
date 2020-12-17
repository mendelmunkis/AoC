#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bench.h"

#define SIZE 23

void iterate(int distance);

char cube[23][23][23][23]={0};
char out[23][23][23][23]={0};
int part=1;

int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    char buf[16];
    int i=1;
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
        for(int j=0;buf[j]!='\0';j++)
            if(buf[j]=='#')
                cube[i+7][j+7][11][11]=1;
        i++;
    }START
    for(int i=5;i>=0;i--)
        iterate(i);END
    for(int r=1;r<SIZE;r++)
        for(int c=1;c<SIZE;c++)
            for(int z=1;z<SIZE;z++)
                for(int w=1;w<SIZE;w++)
                    if(cube[r][c][z][w])
                        result++;
//    printf("%d\n",result);
    printf("%f\n",TIME);
    return 0;
}

void iterate(int distance)
{
    int temp;
    int x,y;
    if(part==1)
    {
        x=11;
        y=12;
    }else
    {
        x=1+distance;
        y=SIZE-1;
    }
    memset(out,0,sizeof(char)*279841);
    for(int r=1+distance;r<SIZE-(distance+1);r++)
        for(int c=1+distance;c<SIZE-(distance+1);c++)
            for(int z=1+distance;z<SIZE-1;z++)
                for(int w=x;w<y;w++)
                {
                    temp=0;
                    for(int i=r-1;i<=r+1;i++)
                        for(int j=c-1;j<=c+1;j++)
                            for(int k=z-1;k<=z+1;k++)
                                for(int l=w-1;l<=w+1;l++)
                                    if(cube[i][j][k][l])
                                        temp++;
                    if(cube[r][c][z][w])
                    {
                        if((temp==3)||(temp==4))
                            out[r][c][z][w]=1;
                    }
                    else
                        if(temp==3)
                            out[r][c][z][w]=1;
                }
    memcpy(cube,out,(sizeof(char)*279841));
}

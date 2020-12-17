#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

void iterate(void);
//int iterate2(char room[94][94]);

char cube[30][30][30][30]={0};
char out[30][30][30][30]={0};
int part=1;

//#pragma GCC push_options
//#pragma GCC optimize (0)

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
                cube[i+12][j+12][15][15]=1;
        i++;
    }
    for(int i=0;i<6;i++)
        iterate();
    for(int r=1;r<SIZE;r++)
        for(int c=1;c<SIZE;c++)
            for(int z=0;z<SIZE;z++)
                for(int w=0;w<SIZE;w++)
                    if(cube[r][c][z][w])
                        result++;
    printf("%d\n",result);
    return 0;
}

void iterate(void)
{
    int temp;
    int x,y;
    if(part==1)
    {
        x=15;
        y=16;
    }else
    {
        x=1;
        y=SIZE-1;
    }
    memset(out,0,sizeof(char)*810000);
    for(int r=1;r<SIZE-1;r++)
        for(int c=1;c<SIZE-1;c++)
            for(int z=1;z<SIZE-1;z++)
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
    memcpy(cube,out,(sizeof(char)*810000));
}

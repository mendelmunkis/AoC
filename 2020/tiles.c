#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 150

char grid[SIZE][SIZE][SIZE]={0};
char temp [SIZE][SIZE][SIZE];

void life(int day);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[50];
    char *bufp;
    int r,c,w;
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
    while(fgets(buf, 50, fp) != NULL)
    {
        bufp=buf;
        r=c=w=(SIZE/2);
        while((*bufp!='\n')&&(*bufp!='\0'))
        {
            if(*bufp=='e')
            {
                r++;
                c--;
            }
            else if(*bufp=='w')
            {
                r--;
                c++;
            }
            else if(*bufp=='n')
            {
                bufp++;
                if(*bufp=='e')
                {
                    r++;
                    w--;
                }
                else if(*bufp=='w')
                {
                    c++;
                    w--;
                }
            }
            else if(*bufp=='s')
            {
                bufp++;
                if(*bufp=='e')
                {
                    c--;
                    w++;
                }
                else if(*bufp=='w')
                {
                    r--;
                    w++;
                }
            }
            bufp++;
        }
        if(grid[r][c][w])
            grid[r][c][w]--;
        else
            grid[r][c][w]++;
        //printf("%d,%d,%d\n",r,c,w);
    }
    if(part==2)
        for(int i=0;i<100;i++)
            life(i);
    for(r=0;r<SIZE;r++)
        for(c=0;c<SIZE;c++)
            for(w=0;w<SIZE;w++)
                if(grid[r][c][w])
                    result++;
    printf("%ld\n",result);
    return 0;
}

void life(int day)
{
    int neighbors;
    int max = day>60?SIZE-1:(SIZE/2)+40+(day/2);
    int min = day>60?1:(SIZE/2)-(40+(day/2));
    memset(temp, 0, SIZE*SIZE*SIZE*sizeof(char));
    for(int r=min;r<max;r++)
        for(int c=min;c<max;c++)
            for(int w=min;w<max;w++)
            {
                neighbors=
                  grid[r+1][c-1][w]+
                  grid[r+1][c][w-1]+
                  grid[r-1][c+1][w]+
                  grid[r-1][c][w+1]+
                  grid[r][c-1][w+1]+
                  grid[r][c+1][w-1];
                if(grid[r][c][w])
                {
                    if((neighbors==1)||(neighbors==2))
                        temp[r][c][w]=1;
                }else
                    if(neighbors==2)
                        temp[r][c][w]=1;
            }
    memcpy(grid, temp, SIZE*SIZE*SIZE*sizeof(char));
}

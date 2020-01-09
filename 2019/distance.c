#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "timsort.h"


int genlines1(FILE * fp);
int genlines2(FILE * fp);
int compare(const void *lefta, const void *righta);
int scompare(const void *lefta, const void *righta);

//#define DEBUG

int main (int argc, char * argv[])
{
    char part=1;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    int ans;
    if(part==1)
        ans=genlines1(fp);
    else
        ans=genlines2(fp);
    if(ans < 999999)
        printf("%d\n", ans);
    else
        printf("Error: Answer out of range.\n");
    return(0);
}

int genlines1(FILE *fp)
{
    char buf[9]={0}, direction;
    static short grid[200000][2];
    short coords[2]={0}, axis;
    int z, length=0, size, steps=1, a=0, ans=999999;
    while(buf[a]!='\n')
    {
        for(buf[a=0]=fgetc(fp);(buf[a]!=',')&&(buf[a]!='\n');buf[++a]=fgetc(fp));
        size = atoi(&buf[1]);

        axis = ((buf[0] == 'U') || (buf[0] == 'D'))? 0 : 1;
        direction = ((buf[0] == 'U') || (buf[0] == 'R'))? 1 : -1;

        for(int len=0;len <size;len++)
        {
            coords[axis]+=direction;
            memcpy(grid[steps], coords, sizeof(coords));
            steps++;
        }
    }
    coords[0]=coords[1]=a=0;
    grid[steps][1]=grid[steps][0]=25000;
    grid[steps+1][1]=grid[steps+1][0]=0;
    grid[0][0]=grid[0][1]=-10000;
    timsort((void *)grid,steps+2,sizeof(grid[0]),*scompare);

    #ifdef DEBUG
    for(int x=0;x<steps;x++)
    {
        for(int y=0;y<2;y++)
            printf("%d, " ,grid[x][y]);
        printf("\b\b\n");
    }
    #endif

    for(z=0; grid[z][0]<0;z++);

    while(buf[a]!='\n')
    {
        for(buf[a=0]=fgetc(fp);(buf[a]!=',')&&(buf[a]!='\n');buf[++a]=fgetc(fp));
        size = atoi(&buf[1]);

        axis = ((buf[0] == 'U') || (buf[0] == 'D'))? 0 : 1;
        direction = ((buf[0] == 'U') || (buf[0] == 'R'))? 1 : -1;
        length=0;

        for(short *pos=&coords[axis];length <size;length++)
        {
            *pos+=direction;
            for(; grid[z][0]>=coords[0];z--);
            z++;
            for(; (grid[z][1]<coords[1])&&(grid[z][0]<=coords[0]);z++);
#ifdef DEBUG
            printf("%d,%d,%d,%d,%d,%d\n",grid[z][0],grid[z][1],grid[z][2],coords[0],coords[1],z);
#endif
            if(!memcmp(grid[z],coords, sizeof(coords)))
                ans =(abs(grid[z][0]) + abs(grid[z][1]))<ans ? abs(grid[z][0]) + abs(grid[z][1]) : ans;
        }
    }
    return ans;
}

int genlines2(FILE *fp)
{
    char buf[9]={1};
    int direction, coords[3]={0,0,1};
    static int grid[200000][3];
    int z, steps=1, axis, size, a=0, ans=999999;
    while(buf[a]!='\n')
    {
        for(buf[a=0]=fgetc(fp);(buf[a]!=',')&&(buf[a]!='\n');buf[++a]=fgetc(fp));
        size = atoi(&buf[1]);

        axis = ((buf[0] == 'U') || (buf[0] == 'D'))? 0 : 1;
        direction = ((buf[0] == 'U') || (buf[0] == 'R'))? 1 : -1;

        for(int len=0;len <size;len++)
        {
            coords[axis]+=direction;
            memcpy(grid[coords[2]], coords, sizeof(coords));
            coords[2]++;
        }

    }
    coords[0]=coords[1]=a=0;
    steps=coords[2];
    grid[steps][1]=grid[steps][0]=25000;
    grid[steps+1][1]=grid[steps+1][0]=0;
    grid[0][0]=grid[0][1]=-10000;
    timsort((void *)grid,steps+2,sizeof(grid[0]),*compare);

    #ifdef DEBUG
    for(int x=0;x<steps;x++)
    {
        for(int y=0;y<2;y++)
            printf("%d, " ,grid[x][y]);
        printf("\b\b\n");
    }
    #endif

    coords[2]=1;
    for(z=0; grid[z][0]<0;z++);

    while(buf[a]!='\n')
    {
        for(buf[a=0]=fgetc(fp);(buf[a]!=',')&&(buf[a]!='\n');buf[++a]=fgetc(fp));
        size = atoi(&buf[1]);

        axis = ((buf[0] == 'U') || (buf[0] == 'D'))? 0 : 1;
        direction = ((buf[0] == 'U') || (buf[0] == 'R'))? 1 : -1;

        for(int length=0, *pos=&coords[axis];length <size;length++)
        {
            *pos+=direction;
            for(; grid[z][0]>=coords[0];z--);
            z++;
            for(; (grid[z][1]<coords[1])&&(grid[z][0]<=coords[0]);z++);
#ifdef DEBUG
            printf("%d,%d,%d,%d,%d,%d\n",grid[z][0],grid[z][1],grid[z][2],coords[0],coords[1],z);
#endif
            if(!memcmp(grid[z],coords, 2*sizeof(int)))
                if((grid[z][2] +=coords[2])<ans)
                    ans=grid[z][2];
            coords[2]++;
        }
    }
    return ans;
}

int compare(const void *lefta, const void *righta)
{
    if(((int *)lefta)[0] < ((int *)righta)[0])
        return 1;
    if(((int *)lefta)[0] > ((int *)righta)[0])
        return 0;
    if(((int *)lefta)[1] < ((int *)righta)[1])
        return 1;
    return 0;
}

int scompare(const void *lefta, const void *righta)
{
    if(((short *)lefta)[0] < ((short *)righta)[0])
        return 1;
    if(((short *)lefta)[0] > ((short *)righta)[0])
        return 0;
    if(((short *)lefta)[1] < ((short *)righta)[1])
        return 1;
    return 0;
}

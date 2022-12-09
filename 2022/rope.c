#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    int grid[1000][1000]={0};
    int rope[10][2]={0};
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
    for(int i=0;i<10;i++)
    {
        rope[i][0]=10;
        rope[i][1]=5;
    }
    int length = part==1?1:9;
    while(fgets(buf, 16, fp) != NULL)
    {
        int dist=atoi(buf+2);
            switch(buf[0])
            {
               case 'R':
                   rope[0][0]+=dist;
                   break;
               case 'L':
                   rope[0][0]-=dist;
                   break;
               case 'U':
                   rope[0][1]+=dist;
                   break;
               case 'D':
                   rope[0][1]-=dist;
                   break;
            }
        for(int i=0;i<dist;i++)
        {
            for(int j=0;j<length;j++)
            {
                if(rope[j][0]-rope[j+1][0]>1)
                {
                    if(rope[j][1]>rope[j+1][1])
                        rope[j+1][1]++;
                    else if(rope[j][1]<rope[j+1][1])
                        rope[j+1][1]--;
                    rope[j+1][0]++;
                }
                else if(rope[j+1][0]-rope[j][0]>1)
                {
                    if(rope[j][1]>rope[j+1][1])
                        rope[j+1][1]++;
                    else if(rope[j][1]<rope[j+1][1])
                        rope[j+1][1]--;
                    rope[j+1][0]--;
                }
                else if(rope[j+1][1]-rope[j][1]>1)
                {
                    if(rope[j][0]>rope[j+1][0])
                        rope[j+1][0]++;
                    else if(rope[j][0]<rope[j+1][0])
                        rope[j+1][0]--;
                    rope[j+1][1]--;
                }
                else if(rope[j][1]-rope[j+1][1]>1)
                {
                    if(rope[j][0]>rope[j+1][0])
                        rope[j+1][0]++;
                    else if(rope[j][0]<rope[j+1][0])
                        rope[j+1][0]--;
                    rope[j+1][1]++;
                }
            }
            if(!grid[rope[part==1?1:9][0]+500][rope[part==1?1:9][1]+500])
            {
                grid[rope[part==1?1:9][0]+500][rope[part==1?1:9][1]+500]++;
                result++;
            }
        }
    }
    printf("%ld\n",result);
    return 0;
}


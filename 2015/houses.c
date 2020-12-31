#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char houses[4000][4000]={0};

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    int turn=0;
    char buf[16];
    int x[2],y[2];
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
    x[0]=x[1]=y[0]=y[1]=2000;
    while(fgets(buf, 16, fp) != NULL)
    {
        for(int i=0;i<15;i++)
        {
            houses[x[turn]][y[turn]]++;
            switch(buf[i])
            {
              case '^':
                  y[turn]++;
                  break;
              case 'v':
                  y[turn]--;
                  break;
              case '>':
                  x[turn]++;
                  break;
              case '<':
                  x[turn]--;
                  break;
              case '\0':
                  i=16;
                  break;
              default:
                  printf("Bad direction %c\n",buf[i]);
                  return 1;
            }
            if(part==2)
            {
                turn++;
                turn%=2;
            }
        }
    }
    for(int r=0;r<4000;r++)
        for(int c=0;c<4000;c++)
            if(houses[c][r])
                    result++;
    printf("%ld\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARDS 100

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[300], *bufp;
    int draw[300], x=0, y,z,i;
    int bingo[CARDS][5][5];
    int complete[CARDS]={0};
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
    fgets(buf, 300, fp);
    for(bufp = strtok(buf, ","); bufp ; bufp = strtok(NULL, ","))
    {
            draw[x] = atol(bufp);
            x++;
    }
    x=y=z=0;
    fgets(buf, 50, fp);
    while(fgets(buf, 50, fp) != NULL)
    {
        bufp=buf;
        if(*buf == '\n')
        {
            z++;
            y=0;
            continue;
        }
        for(x=0;x<5;x++)
            bingo[z][x][y]=strtol(bufp,&bufp,10);
        y++;
    }
    for(i=0;i<300;i++)
    {
        for(z=0;z<CARDS;z++)
        {
            for(x=0;x<5;x++)
            {
                for(y=0;y<5;y++)
                    if(bingo[z][x][y]==draw[i])
                    {
                        bingo[z][x][y]=255;
                        if(((bingo[z][x][0]+ bingo[z][x][1]+ bingo[z][x][2]+ bingo[z][x][3] +bingo[z][x][4])==1275)
                          ||((bingo[z][0][y]+ bingo[z][1][y]+ bingo[z][2][y]+ bingo[z][3][y] +bingo[z][4][y])==1275))
                          {
                            if(part==2)
                            {
                                if(complete[z])
                                    continue;
                                if((CARDS-1)!=result)
                                {
                                    result++;
                                    complete[z]=1;
                                    continue;
                                }
                            }
                            y=3;
                            break;
                          }
                    }
                if(y==3)
                    break;
             }
            if(y==3)
                break;
         }
         if(y==3)
            break;
    }
    result=0;
    for(x=0;x<5;x++)
        for(y=0;y<5;y++)
            if(bingo[z][x][y]<200)
                result+=bingo[z][x][y];
    result*=draw[i];
    printf("%ld\n",result);
    return 0;
}



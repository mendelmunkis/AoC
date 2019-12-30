#include "intcode.h"
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>*/



char grid[100][100]={0};
char paint[100][100]={0};
int painted=0;
int gridx=50;
int gridy=50;
char outflag=0;
char direction=0;

int  getinput(void);
void sendoutput(long output);

int main (int argc, char *argv[])
{
    char part=1;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    long  ram[RAM_SIZE];
    loadram(fp, ram);
    if(part==2)
    {
        gridx=gridy=10;
        grid[gridx][gridy]=1;
    }
    runcompute(ram, 0);
    if(part==2)
        for(gridx=20;gridx>=0;gridx--)
        {
            for(gridy=0;gridy<100;gridy++)
                if(grid[gridx][gridy])
                    printf("\x1b[30m" "ש");
                else
                    printf("\x1b[37m" "ש");
            printf("\n");
        }
    else
        printf("%d\n",painted);
    return(0);
}

int getinput(void)
{
    return grid[gridx][gridy];
}

void sendoutput(long output)
{
    if((gridx >= 100)||(gridx < 0)||(gridy >= 100)||(gridy < 0))
        printf("OOM\n");
    if (outflag)
    {
        if(output)
            direction+=1;
        else
            direction -=1;
//        direction%=4;
        if(direction == -1)
            direction = 3;
        if(direction == 4)
            direction = 0;
        switch(direction)
        {
            case 0:
                gridx++;
                break;
            case 1:
                gridy++;
                break;
            case 2:
                gridx--;
                break;
            case 3:
                gridy--;
                break;
        }
        outflag=0;
    }
    else
    {
        grid[gridx][gridy]=output;
        if(!paint[gridx][gridy])
        {
            paint[gridx][gridy]=1;
            painted++;
        }
        outflag=1;
    }
}


#include "intcode.h"

//#define VISUALIZE

char grid[100][100]={0};
int score=0;
int gridx=50;
int gridy=50;
char outflag=0;
char part=1;

int  getinput(void);
void sendoutput(long output);

int main (int argc, char *argv[])
{
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    long  ram[RAM_SIZE];
    loadram(fp, ram);
    if(part==2)
        ram[0]=2;
    runcompute(ram, 0);
#ifdef VISUALIZE
    printf("\x1b[21A");
    printf("\x1b[21D");
    for(gridy=0;gridy<20;gridy++)
    {
        for(gridx=0;gridx<52;gridx++)
            switch(grid[gridx][gridy])
            {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("█");
                    break;
                case 2:
                    printf("*");
                    if(part==1)
                        score++;
                    break;
                case 3:
                    printf("-");
                    break;
                case 4:
                    printf(".");
                    break;
            }
        printf("\n");
    }
    printf("\n");
#else
    if(part==1)
        for(gridy=0;gridy<20;gridy++)
            for(gridx=0;gridx<50;gridx++)
                switch(grid[gridx][gridy])
                {
                    case 2:
                        score++;
                    default:
                        break;
                }
#endif
    if(part==1)
        printf("Blocks:%d\n",score);
    else
        printf("Score:%d\n",score);
    return(0);
}

int getinput(void)
{
    int tem,temp,in=0;
    for(gridy=0;gridy<50;gridy++)
    {
        for(gridx=0;gridx<50;gridx++)
            switch(grid[gridx][gridy])
            {
                case 3:
                    tem=gridx;
                    break;
                case 4:
                    temp=gridx;
                    break;
            }
    }
    if(tem>temp)
        in=-1;
    if(tem<temp)
        in=1;
#ifdef VISUALIZE
    usleep( 10000);
    printf("\x1b[21A");
    printf("\x1b[21D");
    for(gridy=0;gridy<20;gridy++)
    {
        for(gridx=0;gridx<38;gridx++)
            switch(grid[gridx][gridy])
            {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("█");
                    break;
                case 2:
                    printf("*");
                    break;
                case 3:
                    printf("-");
                    break;
                case 4:
                    printf(".");
                    break;
            }
        printf("\n");
    }
    printf("\x1b[1B");
    printf("Score:%d",score);
#endif
    return in;
}

void sendoutput(long output)
{
//    if((gridx >= 100)||(gridx < -1)||(gridy >= 100)||(gridy < 0))
//        printf("OOM %d,%d\n",gridx,gridy);
    if (outflag == 0)
    {
        gridx=output;
        outflag=1;
    }
    else if(outflag == 1)
    {
        gridy=output;
        outflag++;
    }else if((gridx==-1)&&(gridy==0))
    {
            outflag=0;
            score=output;

    }else
    {
        grid[gridx][gridy]=output;
        outflag=0;
    }
    
}


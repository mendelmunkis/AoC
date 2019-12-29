#include "intcode.h"


static  char inflag = 0;
static  int input = 0;
static  int ans  = 0;
static  char phase;


int main (int argc, char * argv[])
{
    char part=1;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    char test[5] = {5};
    char start=5,end=10;
    if(part==1)
        start=0,end=5;
    int ip[5];
    long rams[5][RAM_SIZE];
    long ram[RAM_SIZE];
    loadram(fp, ram);
    for(test[0]=start;test[0] < end;test[0]++)
        for(test[1]=start;test[1] < end;test[1]++)
        {
            if(test[0]==test[1])
                continue;
            for(test[2]=start;test[2]<end;test[2]++)
            {
                if((test[2] == test[1]) || (test[2] == test[0]))
                    continue;
                for(test[3]=start;test[3]<end;test[3]++)
                {
                    if( (test[3] == test[2]) || (test[3] == test[1]) || (test[3] == test[0]))
                        continue;
                    for(test[4]=start;test[4]<end;test[4]++)
                    {
                        if( (test[4] == test[3]) ||(test[4] ==test[2]) || (test[4] == test[1]) || (test[4] == test[0]) )
                            continue;
                        for(int i=0;i<5;i++)
                        {
                            ip[i]=inflag=0;
                            phase=test[i];
                            memcpy(rams[i], ram, sizeof(long)*RAM_SIZE);
                            runcompute(rams[i],&ip[i]);
                        }
                        while(rams[4][ip[4]] != 99)
                            for(int i=0;i<5;i++)
                                runcompute(rams[i], &ip[i]);
                        if(input > ans)
                            ans = input;
                        input = 0;
                    }
                }
            }
        }
    printf("%d\n", ans);
    return(0);
}

int getinput(void)
{
    if (!inflag)
    {
        inflag=1;
        return phase;
    }
    else
    {
        return input;
    }
}

void sendoutput(long output)
{
    input = output;
    halt=1;
}


#include "intcode.h"
#include "time.h"

#define INFILE   "inputs/input2"


int main (int argc, char *argv[])
{
    int n,v,part=0;
    if((argc == 2)&&(argv[1][0] == '2'))
        part++;
    FILE * fp;
    if((fp = fopen (INFILE, "r")) == NULL)
    {
        printf("Error opening file %s\n", INFILE);
        return 1;
    }
    long  ram[RAM_SIZE];
    loadram(fp, ram);
    if(!part)
    {
        ram[1]=12;
        ram[2]=2;
        runcompute(ram, 0);
        printf("%d\n", ram[0]);
    }
    else
    {
        for(n=0;n<100;n++)
            for(v=0;v<100;v++)
            {
                loadram(fp, ram);
                ram[1]=n;
                ram[2]=v;
                runcompute(ram, 0);
                if(ram[0] == 19690720)
                    printf("%d\n", 100*n+v);
            }
    }
    return(0);
}

int getinput(void)
{
    return defaultinput();
}

void sendoutput(long output)
{
    defaultoutput(output,0);
}

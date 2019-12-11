#include "intcode.h"

#define INFILE   "program.ic"

char ascii=0;

int main (int argc, char *argv[])
{
    if((argc == 2)&&(!strcmp(argv[1],"a")))
        ascii=1;
    FILE * fp;
    if((fp = fopen (INFILE, "r")) == NULL)
    {
        printf("Error opening file %s\n", INFILE);
        return 1;
    }
    long  ram[RAM_SIZE];
    loadram(fp, ram);
    runcompute(ram, 0);
    return(0);
}

int getinput(void)
{
    return defaultinput();
}

void sendoutput(long output)
{
    defaultoutput(output,ascii);
}

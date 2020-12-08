#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    FILE *infp, *outfp;
    if((infp = fopen (argv[1], "r"))==NULL)
    {
        printf("error opening file %s\n", argv[1]);
        return 1;
    }
    if((outfp = fopen (argv[2], "w"))==NULL)
    {
        printf("error opening file %s\n", argv[2]);
        return 1;
    }

    char buf[16];
    int counter=0;
    fputs("1106,0,4,0,",outfp);
    while(fgets(buf, 16, infp) != NULL)
    {
        if(strncmp(buf, "nop",3)==0)
            fprintf(outfp,"101,0,3,3,109,0,");
        if(strncmp(buf, "acc",3)==0)
            fprintf(outfp,"101,%d,3,3,109,0,",strtol(buf+3,NULL,10));
        if(strncmp(buf, "jmp",3)==0)
            fprintf(outfp,"1106,0,%d,1106,1,1,",(4+(strtol(buf+3,NULL,10)+counter)*6));
        counter++;
    }
    fputs("4,3,99",outfp);
    return 0;
}

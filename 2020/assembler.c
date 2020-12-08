#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int digits(int in);

int main (int argc, char * argv[])
{
    FILE *infp, *outfp;
    if((infp = fopen (argv[1], "r"))==NULL)
    {
        printf("error opening file %s\n", argv[1]);
        return 1;
    }
    if((outfp = fopen (argv[2], "w+"))==NULL)
    {
        printf("error opening file %s\n", argv[2]);
        return 1;
    }

    short location[1000][2]={0};
    char buf[16];
    int counter=0,pc=0;
    int target,total,jump;
    fputs("1106,0,4,0,",outfp);
    pc+=4;
    while(fgets(buf, 16, infp) != NULL)
    {
        if(strncmp(buf, "acc",3)==0)
        {
            fprintf(outfp,"101,%d,3,3,",strtol(buf+3,NULL,10));
            location[counter][0]=pc;
            pc+=4;
        }
        if(strncmp(buf, "jmp",3)==0)
        {
            fprintf(outfp,"1106,0,0000,");
            location[counter][1]=strtol(buf+3,NULL,10)+counter;
            location[counter][0]=pc;
            pc+=3;
        }
        counter++;
    }
    fputs("4,3,99",outfp);
    total=pc+3;
    location[counter][0]=pc;
    pc=0;
    rewind(outfp);
    for(int i=0;i<counter;i++)
    {
        jump=location[i][1];
        if(jump)
        {
             if((jump<0)||(jump>counter))
                 target=total;
             else
             {
                 while(!location[jump][0])
                     jump++;
                 target=location[jump][0];
             }
             for(;pc<location[i][0]+2;pc++)
                 while(fgetc(outfp)!=','){}
             for(int j=0;j<(4-digits(target));j++)
                 fgetc(outfp);
             fprintf(outfp,"%d",target);
        }
    }
    return 0;
}

int digits(int in)
{
    int counter=1;
    while(in/=10)
        counter++;
    return counter;
}

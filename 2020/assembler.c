#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

int main (int argc, char * argv[])
{
    FILE *infp, *outfp;
    if((infp = fopen (argv[1], "r"))==NULL)
    {
        printf("error opening file %s\n", argv[1]);
        return 1;
    }
    if(argc>=3)
    {
        if((outfp = fopen (argv[2], "w+"))==NULL)
        {
            printf("error opening file %s\n", argv[2]);
            return 1;
        }
    }else
        outfp = stdout;

    int location[MAX_LEN][3]={0};
    char buf[16];
    int counter=0,pc=0;
    int target,total,jump,acc;
    fputs("1106,0,4,0,",outfp);
    pc+=4;
    while(fgets(buf, 16, infp) != NULL)
    {
        if(strncmp(buf, "acc",3)==0)
        {
            location[counter][2]=strtol(buf+3,NULL,10);
            location[counter][0]=1;
        }
        if(strncmp(buf, "jmp",3)==0)
        {
            location[counter][2]=strtol(buf+3,NULL,10)+counter;
            location[counter][0]=2;
            location[location[counter][2]][1]=1;
        }
        counter++;
    }
    for(int i=0;i<counter;i++)
    {
        if(location[i][0]==1)
        {
            if(!location[i][1])
            {
                for(acc=i-1;!(location[acc][0]||location[acc][1]);acc--);
                if(location[acc][0]==1)
                {
                    location[acc][2]+=location[i][2];
                    location[i][0]=0;
                }
                else
                {
                    location[i][1]=pc;
                    pc+=4;
                }
            }
            else
            {
                location[i][1]=pc;
                pc+=4;
            }
        }
        else if(location[i][0]==2){
            location[i][1]=pc;pc+=3;}//removethis
    }
    total=pc+3;
    location[counter][0]=2;
    location[counter][1]=pc;
    for(int i=0;i<counter;i++)
    {
        if(location[i][0]==1)
            fprintf(outfp,"101,%d,3,3,",location[i][2]);
        else if(location[i][0]==2)
        {
             jump=location[i][2];
             if((jump<0)||(jump>counter))
                 target=total;
             else
             {
                 while(!location[jump][0])
                     jump++;
                 target=location[jump][1];
             }
             fprintf(outfp,"1106,0,%d,",target);
        }
    }
    fputs("4,3,99",outfp);
    return 0;
}

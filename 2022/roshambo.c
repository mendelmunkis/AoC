#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    int score =0;
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
    while(fgets(buf, 16, fp) != NULL)
    {
        buf[2]-=87;
        buf[0]-=64;
        if(part==1)
        {
            score+=buf[2];
            if(buf[0]==buf[2])
                score+=3;
            buf[0]++;
            buf[0]%=3;
            buf[2]%=3;
            if(buf[0]==buf[2])
                score+=6;
        }else
        {
            score+=(buf[2]-1)*3;
            if(buf[0]==1)
            {
                if(buf[2]==1)
                    score+=3;
                else if(buf[2]==2)
                    score+=1;
                else if(buf[2]==3)
                    score+=2;
            }
            else if(buf[0]==2)
                score+=buf[2];
            else
                score+=buf[2]%3+1;
        }
    }
    result=score;
    printf("%ld\n",result);
    return 0;
}

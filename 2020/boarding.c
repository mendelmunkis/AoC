#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    char buf[16];
    char *cp;
    char seats[1024]={0};
    int row,col,sid=0;
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
        cp=buf;
        row=col=0;
        for(int i=0;i<7;i++)
        {
            if(*(cp+i)=='B')
                row+=pow(2,(6-i));
        }
        cp+=7;
        for(int i=0;i<3;i++)
            if(*(cp+i)=='R')
                col+=pow(2,(2-i));
            sid=(8*row)+col;
            if(part==2)
                seats[sid]=1;
            if(((8*row)+col)>result)
                result=sid;
    }
    if(part==2)
        for(int i=0;i<1024;i++)
            if(!seats[i])
                if(seats[i+1]&& seats[i-1])
                    result=i;
          //  printf("%d",seats[i]);  Visulazation code
          //  if(!(i%8))printf("\n");}
    printf("%d\n",result);
    return 0;
}

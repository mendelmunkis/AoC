#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[20], *bufp;
    long fish[9]={0}, tmp;
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
    while(fgets(buf, 20, fp) != NULL)
    {
        bufp=buf;
        while(1)
        {
            if(*bufp=='\n')
                break;
            if(*bufp==',')
                bufp++;
            if(*bufp=='\0')
                break;
            tmp=strtol(bufp,&bufp,10);
            fish[tmp]++;
        }
    }
    for(int i=0;i<(part==1?80:256);i++)
    {
        tmp=fish[0];
        fish[0]=fish[1];
        fish[1]=fish[2];
        fish[2]=fish[3];
        fish[3]=fish[4];
        fish[4]=fish[5];
        fish[5]=fish[6];
        fish[6]=fish[7];
        fish[7]=fish[8];
        fish[8]=tmp;
        fish[6]+=tmp;
    }
    result=fish[0]+fish[1]+fish[2]+fish[3]+fish[4]+fish[5]+fish[6]+fish[7]+fish[8];
    printf("%ld\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long result=0;
    int part=1;
    char buf[25], *bufp;
    unsigned long in[26][26]={0},out[26][26], subs[26][26];
    unsigned long max=0,min=86543345667834,tmp,last;
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
    fgets(buf, 25, fp);
    bufp=buf;
    while(*(bufp+1)!='\n')
    {
        in[(*bufp)-65][*(bufp+1)-65]++;
        bufp++;
    }
    last=(*bufp)-65;
    fgets(buf, 25, fp);
    while(fgets(buf, 25, fp) != NULL)
        subs[buf[0]-65][buf[1]-65]=(buf[6]-65);
    for(int i=0;i<(part==1?5:20);i++)
    {
        memset(out,0,26*26*sizeof(unsigned long));
        for(int x=0;x<26;x++)
            for(int y=0;y<26;y++)
            {
                out[x][subs[x][y]]+=in[x][y];
                out[subs[x][y]][y]+=in[x][y];
            }
        memset(in,0,26*26*sizeof(unsigned long));
        for(int x=0;x<26;x++)
            for(int y=0;y<26;y++)
            {
                in[x][subs[x][y]]+=out[x][y];
                in[subs[x][y]][y]+=out[x][y];
            }
    }
    in[last][0]++;
    for(int x=0;x<26;x++)
    {
        tmp=0;
        for(int y=0;y<26;y++)
           tmp+=in[x][y];
        if(tmp>max)
            max=tmp;
        if((tmp<min)&&tmp)
            min=tmp;
    }
    result=max-min;
    printf("%lu\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char conn[15][15]={0};
int part=1, flag=0;


int find(int spot, char in[45]);
char hash(char *bufp);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    char buf[16],*bufp;
    char path[45]={0};
    int in,out,x;
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
        bufp=strtok(buf,"-");
        in=hash(bufp);
        bufp=strtok(NULL,"\n");
        out=hash(bufp);
//        if(out!=0)
            for(x=0;conn[in][x]!=0;x++);
                conn[in][x]=out;
//        if(in!=0)
            for(x=0;conn[out][x]!=0;x++);
                conn[out][x]=in;
    }
    result=find(0, path);
    printf("%ld\n",result);
    return 0;
}

int find(int spot, char in[45])
{
    int x;
    int total=0;
    char path[45];
    int small=0;
    if(spot==10)
        return 1;
    if(spot==0)
        if(in[0]!=0)
            return 0;
    memcpy(path,in,45);
    for(x=0;path[x]!=0;x++)
        if(path[x]==spot)
            if(spot<10)
                if((part==1) || flag)
                    return 0;
                else
                    flag=small=1;
    path[x]=spot;
    for(int i=0; conn[spot][i]!=0;i++)
        total+=find(conn[spot][i], path);
    if(small)
        flag=0;
    return total;
}

char hash(char *bufp)
{
    switch(*(++bufp))
    {
      case 'g':
        return 1;
        break;
      case 'j':
        return 2;
        break;
      case 'k':
        return 3;
        break;
      case 'l':
        return 4;
        break;
      case 'n':
        if(*(bufp+1)=='\0')
            return 5;
        else
            return 10;
        break;
      case 't':
        if(*(bufp+1)=='\0')
            return 6;
        else
            return 0;
        break;
      case 'x':
        return 7;
        break;
      case 'A':
        return 11;
        break;
      case 'D':
        return 12;
        break;
      case 'M':
        return 13;
        break;
      case 'W':
        return 14;
        break;
      default :
        printf("ERROR\n");
    }
}


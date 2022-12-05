#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(char p, int s);
char pop(int s);


char crates[10][60];


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[50];
    char c;
    int from,to,i=0;
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
    memset(crates,'\0',sizeof(crates));
    while(fgets(buf, 50, fp) != NULL)
    {
        if(buf[1]=='1')
            break;
        crates[1][i]=buf[1];
        crates[2][i]=buf[5];
        crates[3][i]=buf[9];
        crates[4][i]=buf[13];
        crates[5][i]=buf[17];
        crates[6][i]=buf[21];
        crates[7][i]=buf[25];
        crates[8][i]=buf[29];
        crates[9][i]=buf[33];
        i++;
    }
    for(i=1;i<=9;i++)
    {
        memset(crates[0],'\0',sizeof(crates[0]));
        for(c=pop(i);c!='\0';c=pop(i))
            push(c,0);
        memccpy(crates[i],crates[0],' ',50);
        for(c=pop(i);c==' ';c=pop(i));
        push(c,i);
    }
    memset(crates[0],'\0',sizeof(crates[0]));
    fgets(buf, 50, fp);
    while(fgets(buf, 50, fp) != NULL)
    {
        if(buf[0]=='\n')
            break;
        sscanf(buf,"move %d from %d to %d", &i,&from,&to);
        for(;i>0;i--)
        {
            if(part==1)
                push(pop(from),to);
            else
                push(pop(from),0);
        }
        if(part==2)
        for(c=pop(0);c!='\0';c=pop(0))
            push(c,to);
    }
    for(i=1;i<=9;i++)
        printf("%c", pop(i));
    printf("\n");
    return 0;
}

void push(char p, int s)
{
    int i;
    for(i=0;crates[s][i]!='\0';i++);
    crates[s][i]=p;
}

char pop(int s)
{
    int i;
    for(i=0;crates[s][i]!='\0';i++);
    if(i==0)
        return '\0';
    char r = crates[s][--i];
    crates[s][i]='\0';
    return r;
}

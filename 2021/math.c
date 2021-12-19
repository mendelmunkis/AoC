#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 2000
char pr[LEN];

void explode(void);
int split(void);
int magnitude(int off);
void add(char *bufp);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[60], *bufp;
    int lines=0, x;
    char problems[100][60]={0};
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
    memset(pr,102,LEN);
    while(fgets(buf, 60, fp) != NULL)
    {
        bufp=buf;
        add(bufp);
        strcpy(problems[lines],buf);
        lines++;
#ifdef DEBUG
        for(int x=0;x<LEN;x++)
        {
            if(pr[x]==102)
            {
                printf("\n");
                break;
            }
            else if(pr[x]==101)
            {
                printf("]");
                if(pr[x+1]<101)
                printf(",");
            }
            else if(pr[x]==100)
                printf("[");
            else
            {
                printf("%d",pr[x]);
                if(pr[x+1]<101)
                printf(",");
            }
        }
#endif
    }
    result=magnitude(1);
    if(part==2)
    {
       result=0;
       for(int i=0;i<lines;i++)
           for(int j=i;j<lines;j++)
           {
               memset(pr,102,LEN);
               bufp=problems[i];
               add(bufp);
               bufp=problems[j];
               add(bufp);
               x=magnitude(1);
               if(x>result)
                   result=x;
               memset(pr,102,LEN);
               bufp=problems[j];
               add(bufp);
               bufp=problems[i];
               add(bufp);
               x=magnitude(1);
               if(x>result)
                   result=x;
           }
    }
    printf("%ld\n",result);
    return 0;
}

void explode(void)
{
    int depth=0;
    int x=-1, y,out=0;
    for(int i=0;i<LEN;i++)
    {
        x++;
        if(pr[i]==100)
            depth++;
        if(pr[i]==101)
            depth--;
        if(depth>4)
        {
            for(y=x;y>0;y--)
            if(pr[y]<100)
                break;
            if(y)
                pr[y]+=pr[i+1];
            pr[x++]=0;
            i+=2;
            out=pr[i];
            i+=2;
            depth--;
            while(i<LEN)
            {
                pr[x++]=pr[i++];
                if((out)&&(pr[x-1]<100))
                {
                    pr[x-1]+=out;
                    out=0;
                }
            }
            depth=0;
            i=x=-1;
            continue;
        }
        if(depth==0)
            break;
    }
    x++;
    while(x<LEN)
        pr[x++]=102;
}

int split(void)
{
    char out[LEN];
    int i,o;

    o=-1;
    memset(out,102,LEN);
    for(i=0;i<LEN;i++)
    {
        o++;
        if((i==o)&&(pr[i]<100)&&(pr[i]>=10))
        {
            out[o++]=100;
            out[o++]=pr[i]/2;
            out[o]=pr[i]/2;
            if(pr[i]%2)
                out[o]++;
            out[++o]=101;
        }
        else
        out[o]=pr[i];
    }
    if(memcmp(out,pr,LEN))
    {
        memcpy(pr,out,LEN);
        return 1;
    }
    return 0;
}

int magnitude(int off)
{
    int a,b,depth;
    if(pr[off]==100)
        a=3*magnitude(off+1);
    else
        a=3*pr[off];
    if(pr[off++]==100)
    {
        depth=1;
        for(;depth;off++)
        {
            if(pr[off]==100)
                depth++;
            if(pr[off]==101)
                depth--;
        }
    }
    if(pr[off]==100)
        b=2*magnitude(off+1);
    else
        b=2*pr[off];
    return a+b;
}

void add(char *bufp)
{
    int x,add;
    for(x=0;pr[x]<102;x++);
    if(x)
    {
        add=1;
        memmove(pr+1,pr,x++);
        pr[0]=100;
    }
    while(1)
    {
        if(*bufp =='\n')
            break;
        else if(*bufp =='[')
        {
            pr[x++]=100;
            bufp++;
        }
        else if(*bufp ==']')
        {
            pr[x++]=101;
            bufp++;
        }
        else if(*bufp ==',')
            bufp++;
        else
            pr[x++]=(*(bufp++))-48;
    }
    if(add)
        pr[x++]=101;
    for(int flag=1;flag;)
    {
        explode();
        flag=split();
    }
}

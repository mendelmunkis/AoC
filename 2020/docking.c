#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SPACE 150000

long carter(long in);

int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long long result=0;
    int part=1;
    char buf[50];
    long zero[2048],one[2048],x;
    long offset,input, toff,k;
    char *bp;
    int flag=0,j=0;
    FILE * fp;
    long ram[SPACE]={0};
    long location[SPACE]={0};
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    if(part==1)
        while(fgets(buf, 50, fp) != NULL)
        {
            if(buf[1]=='a')
            {
                one[0]=zero[0]=0;
                bp=buf+42;
                for(int i=0;i<36;i++)
                {
                    if(*bp=='1')
                        one[0]+=pow(2,i);
                    else if(*bp=='0')
                        zero[0]+=pow(2,i);
                    bp--;
                }
                zero[0] = ~zero[0];
            }else
            {
                offset=strtol(buf+4,&bp,10);
                input=strtol(bp+3,NULL,10);
                input |= one[0];
                input &= zero[0];
                ram[offset]=input;
            }
        }
    else
        while(fgets(buf, 50, fp) != NULL)
        {
            if(buf[1]=='a')
            {
                one[0]=x=0;
                bp=buf+42;
                for(int i=0;i<36;i++)
                {
                    if(*bp=='1')
                        one[0]+=pow(2,i);
                    else if(*bp=='X')
                        x+=pow(2,i);
                    bp--;
                }
                memset(one+1,0,520*sizeof(long));
                memset(zero+1,0,520*sizeof(long));
                k=1;
                zero[0]=x;
                for(long i=1;i<34359738370;i*=2)
                    if(x&i)
                    {
                        int l=k;
                        for(int j=0;j<l;j++)
                        {
                            one[k]=one[j]+i;
                            zero[k]=zero[j]-i;
                            k++;
                        }
                    }
                for(int i=0;(one[i]||zero[i]);i++)
                    zero[i] =~zero[i];
            }else
            {
                offset=strtol(buf+4,&bp,10);
                input=strtol(bp+3,NULL,10);
                for(int i=0;one[i]||zero[i];i++)
                {
                    toff=offset;
                    toff |= one[i];
                    toff &= zero[i];
                    for(k=carter(toff);location[k];k++)
                        if(location[k]==toff)
                            break;
                        else if(k==SPACE)
                            k=0;
                    ram[k]=input;
                    location[k]=toff;
                }
            }
        }
    for(int i=0;i<SPACE;i++)
        result+=ram[i];
    printf("%lu\n",result);
    return 0;
}

long carter(long in)
{
    long long out;
    out=in*885858;
    out+=8594;
    out%=901471;
    out%=SPACE;
    return out;
}

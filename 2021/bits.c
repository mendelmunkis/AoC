#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned char hex[700];
int part=1,next,max;

unsigned long packet();
int get(int offset, int length);

int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long result=0;
    char buf[1400], read[3]={0}, *bufp;
    int i;
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
    fgets(buf, 1400, fp);
    bufp=buf;
    for(i=0;*bufp&&(*bufp!='\n');i++)
    {
        strncpy(read,bufp,2);
        bufp+=2;
        hex[i]=strtol(read,NULL,16);
    }
    max=8*i;
    result=packet();
    printf("%ld\n",result);
    return 0;
}

unsigned long packet()
{
    long result=0,in,end=0,a,b;
    in=get(next,3);
    if(part==1)
        result+=in;
    next+=3;
    in=get(next,3);
    next+=3;
    switch(in)
    {
      case 0:
        if(get(next++,1))
        {
            end=get(next,11);
            next+=11;
            for(int i=0;i<end;i++)
                result+=packet();
        }
        else
        {
            end=get(next,15);
            next+=15;
            end+=next;
            while(next<end)
                result+=packet();
        }
        break;
      case 1:
        if(part==2)
            result=1;
        if(get(next++,1))
        {
            end=get(next,11);
            next+=11;
            for(int i=0;i<end;i++)
                if(part==2)
                    result*=packet();
                else
                    result+=packet();
        }
        else
        {
            end=get(next,15);
            next+=15;
            end+=next;
            while(next<end)
                if(part==2)
                    result*=packet();
                else
                    result+=packet();
        }
        break;
      case 2:
        if(get(next++,1))
        {
            end=get(next,11);
            next+=11;
            result+=packet();
            for(int i=1;i<end;i++)
            {
                if(part==1)
                    result+=packet();
                else
                {
                    in=packet();
                    if(in<result)
                        result=in;
                }
            }
        }
        else
        {
            end=get(next,15);
            next+=15;
            end+=next;
            result+=packet();
            while(next<end)
                if(part==1)
                    result+=packet();
                else
                {
                    in=packet();
                    if(in<result)
                        result=in;
            }
        }
        break;
      case 3:
        if(get(next++,1))
        {
            end=get(next,11);
            next+=11;
            for(int i=0;i<end;i++)
            {
                if(part==1)
                    result+=packet();
                else
                {
                    in=packet();
                    if(in>result)
                        result=in;
                }
            }
        }
        else
        {
            end=get(next,15);
            next+=15;
            end+=next;
            result+=packet();
            while(next<end)
                if(part==1)
                    result+=packet();
                else
                {
                    in=packet();
                    if(in>result)
                        result=in;
                }
        }
        break;
      case 4:
        in=get(next,5);
        next+=5;
        end+=in&15;
        while(in&16)
        {
            in=get(next,5);
            next+=5;
            end<<=4;
            end+=in&15;
        }
        if(part==2)
            return end;
        break;
      case 5:
        if(get(next++,1))
            next+=11;
        else
            next+=15;
        a=packet();
        b=packet();
        if(part==1)
            return result+a+b;
        return ((a>b)?1:0);
      case 6:
        if(get(next++,1))
            next+=11;
        else
            next+=15;
        a=packet();
        b=packet();
        if(part==1)
            return result+a+b;
        return ((a<b)?1:0);
      case 7:
        if(get(next++,1))
            next+=11;
        else
            next+=15;
        a=packet();
        b=packet();
        if(part==1)
            return result+a+b;
        return ((a==b)?1:0);
    }
    return result;
}


int get(int offset, int length)
{
    unsigned int mask=(1<<length)-1;
    unsigned char *p=hex+(offset/8);
    offset%=8;
    return (((p[0]<<24)+(p[1]<<16)+(p[2]<<8)+p[3])>>32-(length+offset))&mask;
}

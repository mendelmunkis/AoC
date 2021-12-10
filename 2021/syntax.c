#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  chunk();
int cmp(const void *a, const void *b);

char *bufp;
char complete[200];
int  i;

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[200];
    long scores[100]={0};
    long x;
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
    while(fgets(buf, 200, fp) != NULL)
    {
        bufp=buf;
        memset(complete,0,200);
        i=0;
        while(*bufp!='\n')
        {
            x=chunk();
            if(x|i)
                break;
            bufp++;
        }
        if(part==2)
        {
            x=0;
            for(i=0;complete[i]!=0;i++)
            {
                x*=5;
                switch(complete[i])
                {
                  case ')':
                      x+=1;
                      break;
                  case ']':
                      x+=2;
                      break;
                  case '}':
                      x+=3;
                      break;
                  case '>':
                      x+=4;
                      break;
                }
            }
            for(i=0;scores[i]!=0;i++);
            scores[i]=x;
        }
        else
            if(x>0)
                result+=x;
    }
    if(part==2)
    {
        qsort(scores,100,sizeof(long),cmp);
        for(i=0;scores[i]==0;i++);
        result=scores[(100-i)/2+i];
    }
    printf("%ld\n",result);
    return 0;
}


int chunk()
{
    int  x=0;
    char in=*bufp;
    char out;

    switch(in)
    {
      case '{':
        out = '}';
        break;
      case '[':
        out = ']';
        break;
      case '(':
        out = ')';
        break;
      case '<':
        out = '>';
        break;
    }
    while(!x)
        switch(*(++bufp))
        {
          case '{':
          case '[':
          case '(':
          case '<':
            x=chunk();
            break;
          case ')':
            if(out == ')')
                return 0;
            x=3;
            break;
          case ']':
            if(out == ']')
                return 0;
            x=57;
            break;
          case '}':
            if(out == '}')
                return 0;
            x=1197;
            break;
          case '>':
            if(out == '>')
                return 0;
            x=25137;
            break;
          case '\n':
            complete[i++]=out;
            bufp--;
            return 0;
          default:
            return -1;
        }
    return x;
}

int cmp(const void *a, const void *b)
{
    long x =*((long *)a);
    long y =*((long *)b);

    if(x<y)
    return -1;
    if(x>y)
    return 1;
    return 0;
}

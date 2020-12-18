#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long calc(int mult);

char *bufp;
int part=1;

int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long long result=0;
    char buf[160];
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
    while(fgets(buf, 160, fp) != NULL)
    {
        bufp=buf;
        result+=calc(0);
    }
    printf("%llu\n",result);
    return 0;
}

long calc(int mult)
{
    long total=0;
    int op=0;
    while(1)
    {
        switch(*bufp)
        {
          case '\n': // fallthrough
          case '\0': //fallthrough
          case ')':
              if(mult)
                  bufp--;
              return total;
              break;
          case '(':
              bufp++;
              if(!op)
                  total=calc(0);
              else if(op==1)
                  total+=calc(0);
              else if(op==2)
                  total*=calc(0);
              break;
          case '1': //fallthrough
          case '2': //fallthrough
          case '3': //fallthrough
          case '4': //fallthrough
          case '5': //fallthrough
          case '6': //fallthrough
          case '7': //fallthrough
          case '8': //fallthrough
          case '9':
              if(!op)
                  total=atoi(bufp);
              else if(op==1)
                  total+=atoi(bufp);
              else if(op==2)
                  total*=atoi(bufp);
              while(isdigit(*bufp))
                  bufp++;
              if(*bufp!=' ')
                  bufp--;
              break;
          case '+':
              op=1;
              break;
          case '*':
              if(part==1)
                  op=2;
              else
              {
                  bufp++;
                  total*=calc(1);
              }
              break;
        }
        bufp++;
    }
}

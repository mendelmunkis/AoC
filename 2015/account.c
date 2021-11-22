#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char buf[50000];
char str[] = "red";
int part=1;

int sum(char **p, int i);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    char *num;
    FILE * fp;
    int in, tmp, neg=0;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    fgets(buf, 50000, fp);
    num=buf;
    result=sum(&num, 0);
    printf("%ld\n",result);
    return 0;
}

int sum(char **p, int i)
{
    char *c=*p;
    int num, total=0;
    char red=0;
    while(1)
    {
        switch(*c)
        {
          case '{':
            c++;
            total+=sum(&c, 1);
            break;
          case '[':
            c++;
            total+=sum(&c, 0);
            break;
          case '}':
            if((part==2)&&red)
                total=0;
          case ']':
            *p=c+1;
          case '\0':
            return total;
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
          case '0':
          case '-':
          case '+':
            total+=strtol(c, &c, 10);
            break;
          case 34:
             if((strncmp(++c,str,3) == 0)&&i)
                 red=1;
             break;
          default:
            c++;
        }
    }

}

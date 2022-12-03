#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dedupe(char *s);
int cmp(const void *a, const void *b);


int main (int argc, char * argv[])
{
    char *filename = "input";
    char *end;
    long result=0;
    int part=1;
    char buf[50], first[25],second[25], common[25];
    int x=0;
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
    while(fgets(buf, 50, fp) != NULL)
    {
        end=strchr(buf,'\n');
        *end='\0';
        if(part==1)
        {
            x=(end-buf)/2;
            strncpy(common,buf+x,x);
            buf[x]='\0';
            qsort(common, x, 1, cmp);
            qsort(buf, x, 1, cmp);
            dedupe(common);
            x=3;
        }
        else
            qsort(buf, end-buf, 1, cmp);
        dedupe(buf);
        switch(x)
        {
          case 0:
            strcpy(first,buf);
            x++;
            break;
          case 1:
            strcpy(second,buf);
            x++;
            break;
          default:
          if(part==2)
            for(int i =0; first[i]!='\0';i++)
                for(int j =0; second[j]!='\0';j++)
                {
                    if(first[i]==second[j])
                        strncat(common,first+i,1);
                }
            for(int i =0; common[i]!='\0';i++)
                for(int j =0; buf[j]!='\0';j++)
                    if(common[i]==buf[j])
                    {
                        if(common[i]-38>52)
                            result+=common[i]-96;
                        else
                            result+=common[i]-38;
                        memset(common,'\0',sizeof(common));
                        break;
                    }

            x=0;
            break;
        }
    }
    printf("%ld\n",result);
    return 0;
}

void dedupe(char *s)
{
    for(char *e =s; *e!='\0'; e++)
        if(*e != *s)
            *(++s)=*e;
   *(++s)='\0';
}

int cmp(const void *a, const void *b)
{
    if(*(char *)a < *(char *)b)
        return -1;
    if(*(char *)a > *(char *)b)
        return 1;
    return 0;
}

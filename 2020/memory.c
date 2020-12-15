#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int numbers[30000000]={0};

long carter(long in);

int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    char buf[26];
    char *np;
    long age=1,k;
    int curr,next;
    long end=2020;
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
    if(part==2)
        end=30000000;
    fgets(buf, 26, fp);
    np=strtok(buf,",");
    curr=strtol(np,NULL,10);
    numbers[curr]=age;
    while(np=strtok(NULL,","))
    {
        curr=strtol(np,NULL,10);
        numbers[curr]=++age;
    }
    while(age <end)
    {
        next=age-numbers[curr];
        if(next==age)
            next=0;
        numbers[curr]=age;
        age++;
        curr=next;
    }
    result=curr;
    printf("%d\n",result);
    return 0;
}

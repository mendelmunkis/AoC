#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int fdupe(char *s);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[5000]={0};
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
    fgets(buf, 5000, fp);
    int step = part==1?4:14;
    for(int i =0;;i++)
        if(fdupe(buf+i)>step)
        {
            result=i+step;
            break;
        }
    printf("%ld\n",result);
    return 0;
}

int fdupe(char *s)
{
    char *str=s;
    int i,j,k;
    for(i=1;str[i]!='\0';i++)
        if(str[0]==str[i])
            break;
    for(j=1;j<i;j++)
        for(k=j+1;k<i;k++)
            if(str[j]==str[k])
                i=k;
    return i;
}

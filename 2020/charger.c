#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void*, const void*);
long long recurse(int i);
int adaptors[200]={0};
long long reached[200]={0};

int main (int argc, char * argv[])
{
    char *filename = "input";
    long long result=0;
    int part=1;
    char buf[16];
    int i=0,one=0,three=0;
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
    while(fgets(buf, 16, fp) != NULL)
    {
        adaptors[++i]=strtol(buf,NULL,10);
    }
    i++;
    qsort(adaptors,i,sizeof(int),compare);
    adaptors[i]=adaptors[i-1]+3;
    if(part==1)
    {
        for(int j=1;j<i+2;j++)
            if(adaptors[j]-adaptors[j-1]==1)
                one++;
            else if(adaptors[j]-adaptors[j-1]==3)
                three++;
        result=one*three;
    }
    else
        result=recurse(i);
    printf("%lld\n",result);
    return 0;
}

int compare(const void *a, const void *b)
{
    if(*(int *)a<*(int *)b)
        return -1;
    return 1;
}

long long recurse(int i)
{
    long long result=0;
    if(reached[i])
        return reached[i];
    if(!i)
        return 1;
    if((adaptors[i]-adaptors[i-1])<4)
        result+=recurse(i-1);
    if(i>1)
        if((adaptors[i]-adaptors[i-2])<4)
            result+=recurse(i-2);
    if(i>2)
        if((adaptors[i]-adaptors[i-3])<4)
            result+=recurse(i-3);
    reached[i]=result;
    return result;

}

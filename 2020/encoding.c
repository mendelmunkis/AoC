#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    long iv[500];
    long value;
    char buf[16];
    int flag, i=0;
    int min,max;
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
    for(int i=0;i<25;i++)
    {
        fgets(buf, 16, fp);
        iv[i]=strtol(buf,NULL,10);
    }
    while(fgets(buf, 16, fp) != NULL)
    {
        flag=1;
        value=strtol(buf,NULL,10);
        for(int j=0;j<24;j++)
            for(int k=j;k<25;k++)
                if((value-iv[j])==iv[k])
                    flag=0;
        if(flag)
            break;
        flag=1;
        iv[i]=value;
        i++;
        i%=25;
    }
    result=value;
    if(part==2)
    {
        long sum=result;
        long total=0;
        int j=i=0;
        rewind(fp);
        while(fgets(buf, 16, fp) != NULL)
        {
            value=strtol(buf,NULL,10);
            iv[j]=value;
            total+=value;
            while(total>sum)
            {
                total-=iv[i];
                i++;
                i%=500;
            }
            if(total==sum)
                break;
            j++;
            j%=500;
        }
        min=iv[i];
        max=iv[i];
        while(i!=j)
        {
            i++;
            i%=500;
            if(iv[i]<min)
                min=iv[i];
            if(iv[i]>max)
                max=iv[i];
        }
        result=min+max;
    }
    printf("%ld\n",result);
    return 0;
}

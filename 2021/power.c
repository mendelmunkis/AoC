#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 12
#define LIST 1000

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1, i=0,y,flag;
    char buf[16];
    int  numbers[LIST];
    int x=0b100000000000,gamma=0,test=0;
    int epsilon,oxy=0,carbon=0;
    int testb,oxytest=0,carbontest=0;
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
        numbers[i]=strtol(buf,NULL,2);
        i++;
    }
    for(i=0;i<LEN;i++)
    {
        for(int j=0;j<LIST;j++)
            if(numbers[j]&(x))
                test++;
        if(test>=LIST/2)
            gamma+=x;
        x/=2;
        test=0;
    }
    x=0;
    y=0b1000000000000;
    epsilon=((~gamma)&0b111111111111);
    if(part==2)
    {
        for(int j=0;j<=LEN;j++)
        {
             y/=2;
            oxytest=carbontest=test=testb=0;
            for(i=0;i<LIST;i++)
            {
                if((numbers[i]&x)==(oxy&(x)))
                {
                    oxytest++;
                    if(numbers[i]&y)
                            test++;
                 }
                if((numbers[i]&x)==(carbon&(x)))
                {
                    carbontest++;
                    if(numbers[i]&y)
                            testb++;
                            flag=i;
                 }
             }
             if(test>=(oxytest-test))
                 oxy+=y;
             if(!carbontest)
                 carbon=numbers[flag];
             if(testb<(carbontest-testb))
                 carbon+=y;
             x+=y;
        }
        result=carbon*oxy;
    }
    else
        result=gamma*epsilon;
    printf("%ld\n",result);
    return 0;
}


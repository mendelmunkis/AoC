#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    char buf[16];
    int input[200];
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
    int x=0;
    while(fgets(buf, 16, fp) != NULL)
    {
        input[x]=atoi(buf);
        x++;
    }
    for(int x=0;x<200;x++)
        for(int y=x;y<200;y++)
            if(part==2)
                for(int z=y;z<200;z++)
                    if(input[x]+input[y]+input[z]==2020)
                    {
                        result=input[x]*input[y]*input[z];
                        x=y=z=199;
                    };
            else
                if(input[x]+input[y]==2020)
                {
                    result=input[x]*input[y];
                    x=y=z=199;
                }
    printf("%d\n",result);
    return 0;
}

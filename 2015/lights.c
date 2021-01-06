#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char lights[1000][1000]={0};

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[35];
    int operation;
    int xa,xb,ya,yb;
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
    while(fgets(buf, 35, fp) != NULL)
    {
        if(!strcmp(strtok(buf, " "),"toggle"))
            operation=2;
        else if(!strcmp(strtok(NULL, " "),"on"))
            operation=1;
        else
            operation=-1;
        xa=strtol(strtok(NULL, ","),NULL,10);
        ya=strtol(strtok(NULL, " "),NULL,10);
        strtok(NULL, " ");
        xb=strtol(strtok(NULL, ","),NULL,10);
        yb=strtol(strtok(NULL, " "),NULL,10);
        for(int r=xa;r<=xb;r++)
            for(int c=ya;c<=yb;c++)
                if(part==1)
                {
                    if(operation==2)
                        lights[r][c]=~lights[r][c]&1;
                    else if(operation==1)
                        lights[r][c]=1;
                    else if(operation==-1)
                        lights[r][c]=0;
                }
                else
                {
                    lights[r][c]+=operation;
                    if(lights[r][c]<0)
                        lights[r][c]=0;
                }
    }
    for(int r=0;r<1000;r++)
        for(int c=0;c<1000;c++)
                result+=lights[r][c];
    printf("%ld\n",result);
    return 0;
}

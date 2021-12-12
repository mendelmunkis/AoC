#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16],*bufp;
    int octopus[12][12];
    int i=1,x,y,check,oldresult;
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
    memset(octopus,12,144*sizeof(int));
    while(fgets(buf, 16, fp) != NULL)
    {
        bufp=buf;
        if(*bufp=='\n')
            break;
        for(int j=1;*bufp!='\n'&&*bufp!='\0';j++)
            octopus[i][j]=(*(bufp++))-48;
        i++;
    }
    for(i=0;i<(part==1?100:100000);i++)
    {
        oldresult=result;
        for(x=1;x<11;x++)
            for(y=1;y<11;y++)
                octopus[x][y]++;
        check=result-1;
        while(check!=result)
        {
            check=result;
            for(x=1;x<11;x++)
                for(y=1;y<11;y++)
                    if(octopus[x][y]==10)
                    {
                        result++;
                        octopus[x][y]=11;
                        if(octopus[x+1][y]<10)
                            octopus[x+1][y]++;
                        if(octopus[x-1][y]<10)
                            octopus[x-1][y]++;
                        if(octopus[x][y+1]<10)
                            octopus[x][y+1]++;
                        if(octopus[x][y-1]<10)
                            octopus[x][y-1]++;
                        if(octopus[x+1][y+1]<10)
                            octopus[x+1][y+1]++;
                        if(octopus[x-1][y+1]<10)
                            octopus[x-1][y+1]++;
                        if(octopus[x-1][y-1]<10)
                            octopus[x-1][y-1]++;
                        if(octopus[x+1][y-1]<10)
                            octopus[x+1][y-1]++;
                    }
        }
        for(x=1;x<11;x++)
            for(y=1;y<11;y++)
                if(octopus[x][y]==11)
                    octopus[x][y]=0;
        if((result-oldresult)==100)
            break;
    }
    if(part==2)
        result=i+1;
    printf("%ld\n",result);
    return 0;
}

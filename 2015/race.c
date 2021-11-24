#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[80], *bufp;
    FILE * fp;
    int distance,lead,time,deer=0;
    int speed[9][7]={0};
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 80, fp) != NULL)
    {
        bufp=strtok(buf, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        speed[deer][0]=strtol(bufp,NULL,10);
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        speed[deer][1]=speed[deer][4]=strtol(bufp,NULL,10);
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        bufp=strtok(NULL, " ");
        speed[deer][2]=speed[deer][5]=strtol(bufp,NULL,10);
        deer++;
    }
    lead=0;
    //TODO: reimplement using CRT
//#if 0
    for(time=0;time<2503;time++)
    {
        for(deer=0;deer<9;deer++)
        {
            if(!speed[deer][4])
            {
                speed[deer][5]-=1;
                if(!speed[deer][5])
                    speed[deer][4]=speed[deer][1];
                continue;
            }
            speed[deer][3]+=speed[deer][0];
            speed[deer][4]--;
            if(!speed[deer][4])
                speed[deer][5]=speed[deer][2];
        }
        for(deer=0;deer<9;deer++)
            if(speed[deer][3]>speed[lead][3])
                lead=deer;
        for(deer=0;deer<9;deer++)
            if(speed[deer][3]==speed[lead][3])
                speed[deer][6]++;
    }
    #if 0
    for(deer=0;deer<9;deer++)
    {
        distance=time=0;
        while(time<=2503)
        {
            for(int i=0;i<speed[deer][1];i++)
            {
                time++;
                distance+=speed[deer][0];
                if(time>=2503)
                    break;
            }
            time+=speed[deer][2];
        }
                speed[deer][3]=distance;
    }
    #endif
    for(deer=0;deer<9;deer++)
        if(part==1)
        {
            if(speed[deer][3]>speed[lead][3])
                lead=deer;
        }
        else
            if(speed[deer][6]>speed[lead][6])
                lead=deer;
    result=part==1?speed[lead][3]:speed[lead][6];
    printf("%ld\n",result);
    return 0;
}

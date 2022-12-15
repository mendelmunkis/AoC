#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct beacon
{
    long x;
    long y;
    long bx;
    long by;
    long distance;
};

long man(long x1, long y1, long x2, long y2);

int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long long result=0;
    int part=1;
    char buf[75];
    char * bufp;
    struct beacon beacons[20]={0};
    FILE * fp;
    int i=0,j;
    long line =2000000,max=0,min=20000000;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 75, fp) != NULL)
    {
        bufp=strtok(buf, ",:");
        beacons[i].x=strtol(bufp+12,NULL,10);
        bufp=strtok(NULL, ",:");
        beacons[i].y=strtol(bufp+3,NULL,10);
        bufp=strtok(NULL, ",:");
        beacons[i].bx=strtol(bufp+24,NULL,10);
        bufp=strtok(NULL, ",:");
        beacons[i].by=strtol(bufp+3,NULL,10);
        beacons[i].distance=man(beacons[i].x, beacons[i].y, beacons[i].bx, beacons[i].by);
        if(beacons[i].x+beacons[i].distance>max)
            max =beacons[i].x+beacons[i].distance;
        if(beacons[i].x-beacons[i].distance<min)
            min=beacons[i].x-beacons[i].distance;
        i++;
    }
    if(part==2)
    {
        min=0;
        max=4000000;
        //this optimization is probably useless on all inputs
        for(j=0;j<i;j++)
            if((beacons[j].x+beacons[j].distance<min)||(beacons[j].x-beacons[j].distance>max)||(beacons[j].y+beacons[j].distance<min)||(beacons[j].y-beacons[j].distance>max))
                memcpy(beacons+j,beacons+(--i),sizeof(struct beacon));
    }
    for(;min<=max;min++)
    {
        for(int k=(part==1?line:0);k<=(part==1?line:max);k++)
        {
            for(j=0;j<i;j++)
            {
                if((man(min,k,beacons[j].x,beacons[j].y)<=beacons[j].distance)&&(part==1?(!((beacons[j].by==k)&&beacons[j].bx==min)):1))
                {
                    if(part==1)
                        result++;
                    else
                        k+=beacons[j].distance-man(min,k,beacons[j].x,beacons[j].y);
                    break;
                }

            }
            if(j==i&&part==2)
            {
                result=min*4000000+k;
                max=min-1;
                break;
            }
        }
   }
    printf("%llu\n",result);
    return 0;
}

long man(long x1, long y1, long x2, long y2)
{
        return labs(x1-x2)+labs(y1-y2);
}

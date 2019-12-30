#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 24

int sorta(const void *p, const void *q);

typedef struct {
    char x;
    char y;
    float angle;
} asteroid ;

int main (int argc, char * argv[])
{
    char part=1;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    char map[SIZE][SIZE]={0};
    char test[SIZE][SIZE]={0};
    char visionmap[SIZE][SIZE]={0};
    int x,y;
    int x2, y2, x3,y3,transx,transy,ansx,ansy, result,i,gcd;
    int ans=0;
    for(y=0;y < SIZE;y++)
    {
        for(x=0;x<SIZE;x++)
        {
             map[x][y]=fgetc(fp);
             if ((map[x][y] == 10)|| (map[x][y] == 13))
                 map[x][y]=fgetc(fp);
             if (map[x][y] == 35)
                 map[x][y]=1;
             else
                 map[x][y]=0;
        }
    }
    for(y=0;y<SIZE;y++)
        for(x=0;x<SIZE;x++)
        {
            if(!map[x][y])
                continue;
            memcpy(test, map, ((SIZE*SIZE)*sizeof(char)));
            x2=x+1;
            result=0;
            for(y2=y;y2<SIZE;y2++)
            {
                for(;x2<SIZE;x2++)
                {
                    if(!test[x2][y2])
                        continue;
                    result++;
                    x3=x2-x;
                    y3=y2-y;
                    if(x3 == 0)
                    {
                        if(y3 >= 1)
                        {
                            transy=1;
                            transx=0;
                        }
                        else
                        {
                            transy=-1;
                            transx=0;
                        }
                    }
                    else if(y3 == 0)
                    {
                        if(x3  >=1)
                        {
                            transx=1;
                            transy=0;
                        }
                        else
                        {
                            transx=-1;
                            transy=0;
                        }
                    }
                    else
                    {
                        gcd=1;
                        for(i=1;i<SIZE;i++)
                            if(!(x3%i) && !(y3%i))
                                gcd=i;
                        transx=x3/gcd;
                        transy=y3/gcd;
                    }
                    x3=x2+transx;
                    y3=y2+transy;
                    while((x3 < SIZE) && (y3 < SIZE) &&(x3>-1) && (y3>-1))
                    {
                        test[x3][y3]=0;
                        x3+=transx;
                        y3+=transy;
                    }
                }
                x2=0;
            }
            x2=x-1;
            for(y2=y;y2>=0;y2--)
            {
                for(;x2>=0;x2--)
                {
                    if(!test[x2][y2])
                        continue;
                    result++;
                    x3=x2-x;
                    y3=y2-y;
                    if(x3 == 0)
                    {
                        if(y3 >= 1)
                        {
                            transy=1;
                            transx=0;
                        }
                        else
                        {
                            transy=-1;
                            transx=0;
                        }
                    }
                    else if(y3 == 0)
                    {
                        if(x3  >=1)
                        {
                            transx=1;
                            transy=0;
                        }
                        else
                        {
                            transx=-1;
                            transy=0;
                        }
                    }
                    else
                    {
                        gcd=1;
                        for(i=1;i<SIZE;i++)
                            if(!(x3%i) && !(y3%i))
                                gcd=i;
                        transx=x3/gcd;
                        transy=y3/gcd;
                    }
                    x3=x2+transx;
                    y3=y2+transy;
                    while((x3 < SIZE) && (y3 < SIZE) &&(x3>-1) && (y3>-1))
                    {
                        test[x3][y3]=0;
                        x3+=transx;
                        y3+=transy;
                    }
                }
                x2=SIZE-1;
            }
            if(result>ans)
            {
                ans=result;
                ansx=x;
                ansy=y;
                memcpy(visionmap, test, ((SIZE*SIZE)*sizeof(char)));
            }
        }
    if(part == 1)
    {
        printf("%d   (%d,%d)\n",ans,ansx,ansy);
/*        for(y=0;y<SIZE;y++)
        {
            for(x=0;x<SIZE;x++)
                printf("%c", visionmap[x][y]?'*':' ');
            printf("\n");
        }*/// visionmap printing
        return 0;
    }
    if(ans<200)
    {
        printf("Visionmap contains less than 200 asteroids.\n");
        printf("Please file a bug.\n");
        return 1;
    }
    x3=result=gcd=0;
    x=ansx;
    y=ansy;
    asteroid list[300];
    visionmap[x][y]=0;
    for(y2=y;y2<SIZE;y2++)
        for(x2=0;x2<=x;x2++)
            if(visionmap[x2][y2])
                gcd++;
    if((result+=gcd)>=200)
    {
        for(y2=y;y2<SIZE;y2++)
            for(x2=0;x2<=x;x2++)
                if(visionmap[x2][y2])
                {
                    list[x3].x = x2;
                    list[x3].y = y2;
                    list[x3].angle = (float)(ansy-y2)/(ansx-x2);
                    x3++;
                }
        x3=200-(result-gcd);
        result=-1000;
    }
    if(result>=0)
    {
        gcd=0;
        for(y2=y;y2<SIZE;y2++)
            for(x2=x+1;x2<SIZE;x2++)
                if(visionmap[x2][y2])
                    gcd++;
        if((result+=gcd)>=200)
        {
            for(y2=y;y2<SIZE;y2++)
                for(x2=x+1;x2<SIZE;x2++)
                    if(visionmap[x2][y2])
                    {
                        list[x3].x = x2;
                        list[x3].y = y2;
                        list[x3].angle = (float)(ansy-y2)/(ansx-x2);
                        x3++;
                    }
        x3=200-(result-gcd);
        result=-1000;
        }
    }
    if(result)
    {
        gcd=0;
        for(y2=0;y2<y;y2++)
            for(x2=x;x2<SIZE;x2++)
                if(visionmap[x2][y2])
                    gcd++;
        if((result+=gcd)>=200)
        {
            for(y2=0;y2<y;y2++)
                for(x2=x;x2<SIZE;x2++)
                    if(visionmap[x2][y2])
                    {
                        list[x3].x = x2;
                        list[x3].y = y2;
                        list[x3].angle = (float)(ansy-y2)/(ansx-x2);
                        x3++;
                    }
        x3=200-(result-gcd);
        result=-1000;
        }
    }
    if(result)
    {
        gcd=0;
        for(y2=0;y2<y;y2++)
            for(x2=0;x2<x;x2++)
                if(visionmap[x2][y2])
                    gcd++;
        if((result+=gcd)>=200)
        {
            for(y2=0;y2<y;y2++)
                for(x2=0;x2<x;x2++)
                    if(visionmap[x2][y2])
                    {
                        list[x3].x = x2;
                        list[x3].y = y2;
                        list[x3].angle = (float)(ansy-y2)/(ansx-x2);
                        x3++;
                    }
        x3=200-(result-gcd);
        result=-1000;
        }
    }
    qsort(list, gcd, sizeof(asteroid), sorta);
    x3--;
    printf("%d\n",((list[x3].x*100)+(list[x3].y)));
    return 0;
}

int sorta(const void *p, const void *q)
{
    asteroid x = *(const asteroid *)p;
    asteroid y = *(const asteroid *)q;

    if(x.angle < y.angle)
        return -1;
    if(x.angle > y.angle)
        return 1;
    return 0;
}

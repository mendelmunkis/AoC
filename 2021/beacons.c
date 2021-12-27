#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct beacon {
    int x;
    int y;
    int z;
};
struct beacon space[1000];


int cmp(const void *a, const void *b);
int check(struct beacon stat[40], struct beacon comp[40]);
void rotate(struct beacon scanners[40], int round);
void flip(struct beacon scanners[40], int round);
void dedupe(void);


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[20], *bufp;
    struct beacon scanners[35][40]= {0};
    int i=0,x=0,tot;
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
    fgets(buf, 20, fp);
    x=0;
    while(fgets(buf, 20, fp) != NULL)
    {
        bufp=buf;
        if(*bufp=='\n')
        {
            x++;
            i=0;
            fgets(buf, 20, fp);
            continue;
        }
        scanners[x][i].x=strtol(bufp,&bufp,10);
        scanners[x][i].y=strtol(bufp+1,&bufp,10);
        scanners[x][i].z=strtol(bufp+1,&bufp,10);
        i++;
    }
    qsort(scanners[0], 36,sizeof(struct beacon),cmp);
    int flag=0;
    tot=x;
    while(flag<tot)
        for(i=0;i<=tot;i++)
        {
            if(i && !scanners[i][36].x && !scanners[i][36].y && !scanners[i][36].z && !scanners[i][39].x)
                continue;
            for(int j=1;j<=tot;j++)
            {
                if(scanners[j][36].x || scanners[j][36].y || scanners[j][36].z || scanners[j][39].x)
                    continue;
                if(i==j)
                    continue;
                for(int x=0;x<6;x++)
                {
                    if(check(scanners[i],scanners[j]))
                    {
                       flag++;
                       scanners[j][39].x=i;
                       break;
                    }
                    flip(scanners[j],4*x+0);
                    if(check(scanners[i],scanners[j]))
                    {
                       flag++;
                       scanners[j][39].x=i;
                       break;
                    }
                    flip(scanners[j],4*x+1);
                    if(check(scanners[i],scanners[j]))
                    {
                       flag++;
                       scanners[j][39].x=i;
                       break;
                    }
                    flip(scanners[j],4*x+2);
                    if(check(scanners[i],scanners[j]))
                    {
                       flag++;
                       scanners[j][39].x=i;
                       break;
                    }
                    flip(scanners[j],4*x+3);
                }
            }
        }
    for(i=0;i<36;i++)
    {
        space[i].x=scanners[0][i].x;
        space[i].y=scanners[0][i].y;
        space[i].z=scanners[0][i].z;
    }
    qsort(space, 1000,sizeof(struct beacon),cmp);
    flag=0;
    while(flag<tot)
    {
        for(i=1;i<=tot;i++)
            if((!scanners[i][39].x)&&(!scanners[i][38].x)&&(!scanners[i][38].y)&&(!scanners[i][38].z))
            {
                flag++;
                for(x=0;space[x].x||space[x].y||space[x].z;x++);
                if(part==1)
                    for(int j=0;j<35;x++)
                    {
                        if((!scanners[i][j].x)&&(!scanners[i][j].y)&&(!scanners[i][j].z))
                            break;
                        space[x].x=scanners[i][j].x+scanners[i][36].x;
                        space[x].y=scanners[i][j].y+scanners[i][36].y;
                        space[x].z=scanners[i][j++].z+scanners[i][36].z;
                        if(space[x].x==space[x].y)
                        if(space[x].z==space[x].y)
                        if(!space[x].x)
                        space[x].x=space[x].y=space[x].z=1;
                    }
                for(int k=1;k<=tot;k++)
                    if(scanners[k][39].x==i)
                    {
                        scanners[k][39].x=0;
                        scanners[k][36].x+=scanners[i][36].x;
                        scanners[k][36].y+=scanners[i][36].y;
                        scanners[k][36].z+=scanners[i][36].z;
                    }
                scanners[i][38].x=scanners[i][36].x;
                scanners[i][38].y=scanners[i][36].y;
                scanners[i][38].z=scanners[i][36].z;
            }
    }
    if(part==1)
    {
        dedupe();
        for(result=0;(space[result].z)||(space[result].y)||(space[result].x);result++);
    }
    if(part==2)
        for(int i=0;i<tot-1;i++)
            for(int j=i+1;j<tot;j++)
            {
                x=0;
                x+=(scanners[i][38].x>scanners[j][38].x?scanners[i][38].x-scanners[j][38].x:scanners[j][38].x>scanners[i][38].x);
                x+=(scanners[i][38].y>scanners[j][38].y?scanners[i][38].y-scanners[j][38].y:scanners[j][38].y>scanners[i][38].y);
                x+=(scanners[i][38].z>scanners[j][38].z?scanners[i][38].z-scanners[j][38].z:scanners[j][38].z>scanners[i][38].z);
                if(x>result)
                    result=x;
            }
    printf("%ld\n",result);
    return 0;
}

void rotate(struct beacon scanners[40], int round)
{
    int a,b,c;
    for(int i=0; i<36;i++)
    {
        if(round%2)
        {
            a=(-scanners[i].z);
            b=scanners[i].y;
            c=scanners[i].x;
        }
        else
        {
            a=scanners[i].x;
            b=(-scanners[i].z);
            c=scanners[i].y;
        }
        scanners[i].x=b;
        scanners[i].y=c;
        scanners[i].z=a;
    }
}
void flip(struct beacon scanners[40], int round)
{
    int a,b,c;
    for(int i=0; i<36;i++)
    {
        if(round==23){c=scanners[i].y;b=scanners[i].x;a=scanners[i].z;}else{
        if(round==3)
            c=(-scanners[i].z);
        else if(round<7)
                c=scanners[i].z;
        else if(round<11)
                c=(-scanners[i].y);
        else if(round<15)
                c=scanners[i].y;
        else if(round==15)
                c=(-scanners[i].z);
        else if(round<19)
                c=scanners[i].x;
        else
                c=(-scanners[i].x);
        if(round<4)
                b=scanners[i].x;
        else if(round<8)
                b=(-scanners[i].x);
        else if(round<12)
                b=scanners[i].z;
        else if(round<15)
                b=(-scanners[i].z);
        else if(round==15)
                b=(-scanners[i].x);
        else if(round==19)
                b=(-scanners[i].y);
        else
                b=scanners[i].y;
        if(round<3)
            a=(-scanners[i].y);
        else if(round<7)
                a=scanners[i].y;
        else if(round==7)
                a=scanners[i].z;
        else if(round==11)
                a=(-scanners[i].x);
        else if(round<15)
                a=scanners[i].x;
        else if(round<15)
                a=scanners[i].x;
        else if(round==15)
                a=(-scanners[i].y);
        else if(round<20)
                a=(-scanners[i].z);
        else
                a=scanners[i].z;}
        scanners[i].x=a;
        scanners[i].y=b;
        scanners[i].z=c;
    }
}

int cmp(const void *a, const void *b)
{
    struct beacon i=* (struct beacon *)a;
    struct beacon j=* (struct beacon *)b;

    //set 0 to greater then negatives
    if((!i.x)&&(!i.y)&&(!i.z))
        if((!j.x)&&(!j.y)&&(!j.z))
            return 0;
        else
            return 1;
    if((!j.x)&&(!j.y)&&(!j.z))
        return -1;

    if(i.x>j.x)
        return -1;
    if(i.x<j.x)
        return 1;
    if(i.y>j.y)
        return -1;
    if(i.y<j.y)
        return 1;
    if(i.z>j.z)
        return -1;
    if(i.z<j.z)
        return 1;
    return 0;
}

int check(struct beacon stat[40], struct beacon comp[40])
{
    int xoff,yoff,zoff;
    int xflip=0,yflip=0,zflip=0;
    int i,j,x,y,z;
    int equal=0,correct=0,flag;

    qsort(comp, 35,sizeof(struct beacon),cmp);
    for(i=0;i<36;i++)
    {
        for(j=0;j<36;j++)
        {
            xoff=stat[i].x-comp[j].x;
            yoff=stat[i].y-comp[j].y;
            zoff=stat[i].z-comp[j].z;
            equal=0;
            for(int k=i;k<36;k++)
            {
                if(!stat[k].x&&!stat[k].y&&!stat[k].z)
                    break;
                for(int l=j;l<36;l++)
                    if(((stat[k].x-xoff)==comp[l].x)&&
                      ((stat[k].y-yoff)==comp[l].y) &&
                      ((stat[k].z-zoff)==comp[l].z))
                    {
                        equal++;
                        if(equal==12)
                            correct++;
                        break;
                    }
                if(correct)
                    break;
            }
            if(correct)
                break;
            }
        if(correct)
            break;
    }
    if(!correct)
        return 0;
    comp[36].x=xoff;
    comp[36].y=yoff;
    comp[36].z=zoff;

    return 1;
}

void dedupe(void)
{
    int o=0, i;
    qsort(space, 1000,sizeof(struct beacon),cmp);
    for(i=1;(space[i].z)||(space[i].y)||(space[i].x);i++)
    {
        if((space[i].x!=space[o].x)||(space[i].y!=space[o].y)||(space[i].z!=space[o].z))
        {
            o++;
            if(i-o)
            {
                space[o].x=space[i].x;
                space[o].y=space[i].y;
                space[o].z=space[i].z;
            }
        }
    }
    i++;
    for(o++;o<i;o++)
        space[o].x=space[o].y=space[o].z=0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long orecalc(unsigned long long map2[15625][10][3], int len);
int orehash(char *word);

int main (int argc, char *argv[])
{
    char part=1, *chem;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    static unsigned long long map[15625][10][3]={0};
    char buf[90], *buf2;
    int len=0;
    int in = 0, out=0;
    unsigned long long x=0, y=0;
    while(fgets(buf, 90, fp) != NULL)
    {
        len++;
        chem=buf+strlen(buf);
        chem--;
        *chem='\0';
        while(*chem != ' ')
            chem--;
        in = orehash(buf);
        map[in][9][1] = atoi(chem-2);
        while(*chem != '=')
            chem--;
        *chem='\0';
        buf2 = strtok(buf, " ");
        map[in][0][1] = atoi(buf2);
        buf2 = strtok(NULL, " ,");
        map[in][0][0] = orehash(buf2);
        map[map[in][0][0]][9][2]++;
        out=1;
        for(buf2 = strtok(NULL, " ");buf2;buf2 = strtok(NULL, " "))
        {
            map[in][out][1] = atoi(buf2);
            buf2 = strtok(NULL, " ,");
            map[in][out][0] = orehash(buf2);
            map[map[in][out][0]][9][2]++;
            out++;
        }
    }
    if(part==1)
    {
        map[15624][9][0]=1;
        printf("%lld\n",orecalc(map,len));
    }
    else
    {
        y=2500000000;
        for(x=1250000000;x>0;x/=2)
        {
            map[15624][9][0]=y;
            if(orecalc(map,len)>=1000000000000)
                y-=x;
            else
                y+=x;
        }
        map[15624][9][0]=y;
        if(orecalc(map,len)>=1000000000000)
            y-=1;
        printf("%lld\n",y);
    }
}

int orehash(char *word)
{
    int y=strlen(word);
    int chem=0;
    for(int x =0;x<3;x++)
        chem+=(word[--y]-66)*pow(25,x);
    if(chem==8528)
        return 0;
    if(chem==11960)
        return 15624;
    return chem;
}

long long orecalc(unsigned long long map2[15625][10][3],int len)
{
    long long x,y;
    int out,in=0, index[len+1];
    index[len]=0;
    index[0]=15624;
    static unsigned long long map[15625][10][3]={0};
    memcpy(map, map2, 468750*sizeof(long long));
    for(int outa=0;(out=index[outa]);outa++)
    {
        y=map[out][9][0]/map[out][9][1];
        if(map[out][9][0]%map[out][9][1])
            y++;
        for(x=0;(map[out][x][1]&&(x<9));x++)
        {
            map[map[out][x][0]][9][0]+=y*map[out][x][1];
            if(!--(map[map[out][x][0]][9][2]))
                index[++in]=map[out][x][0];
        }
    }
    return map[0][9][0];
}

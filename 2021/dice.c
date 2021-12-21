#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long universes[10][21][10][21];
long game(int ap, int as, int bp, int bs, int f);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0,x;
    int part=1;
    char buf[35];
    long players[2][2]={0},roll=0,die=1,i=0,z;
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
        players[i++][0]=strtol(buf+28,NULL,10);
    if(part==1)
    {
        for(i=0;(players[0][1]<1000)&&(players[1][1]<1000);i=(i+1)%2)
        {
            x=0;
            for(int j=0;j<3;j++)
            {
                if(die==101)
                {
                    die=1;
                    roll++;
                }
                x+=die++;
            }
            players[i][0]+=x;
            players[i][0]%=10;
            if(!players[i][0])
                players[i][0]=10;
            players[i][1]+=players[i][0];
        }
        result=players[i][1]*((roll*100)+die-1);
    }
    else
    {
        players[0][0]%=10;
        players[1][0]%=10;
        result=game(players[0][0],0,players[1][0],0,1);
        memset(universes,0,44100*sizeof(long));x=0;
        for(int i=1;i<4;i++)
            for(int j=1;j<4;j++)
                for(int k=1;k<4;k++)
                {
                    z=(i+j+k+players[0][0])%10;
                    if(!z)
                        z=10;
                    x+=game(players[1][0],0,z,z+0,1);
                }
        if(x>result)
            result=x;
    }
    printf("%ld\n",result);
    return 0;
}

long game(int ap, int as, int bp, int bs, int f)
{
    int apa=ap,asa=as,bpa=bp,bsa=bs;
    long x=0,y;
    if(universes[ap][as][bp][bs])
        return universes[ap][as][bp][bs];
    if(ap==0)
        ap=10;
    if(bp==0)
        bp=10;
    if(!f)
    {
        as+=ap;
        bs+=bp;
    }

    if(as>20)
        return 1;
    if(bs>20)
        return 0;
    if(as>19)
        return 27;
    if((as<11)&&(bs>19))
        return 0;
    for(int i=1;i<4;i++)
      for(int j=1;j<4;j++)
        for(int k=1;k<4;k++)
        {
        y=0;
        int z=0;
          for(int l=1;l<4;l++)
            for(int m=1;m<4;m++)
              for(int n=1;n<4;n++)
              {
                y+=game((ap+i+j+k)%10,as,(bp+l+m+n)%10,bs, 0);
                if(++z!=y)
                    z=0;
              }
          if(z==27)
              x++;
          else
              x+=y;
        }
    universes[apa][asa][bpa][bsa]=x;
    return x;
}

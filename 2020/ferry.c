#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    long north=0,east=0;
    long wnorth=1,weast=10;
    long temp, temp2;
    char direction =2;
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
    if(part==1)
        while(fgets(buf, 16, fp) != NULL)
            switch(buf[0])
            {
              case 'N':
                  north+=strtol(buf+1,NULL,10);
                  break;
              case 'S':
                  north-=strtol(buf+1,NULL,10);
                  break;
              case 'E':
                  east+=strtol(buf+1,NULL,10);
                  break;
              case 'W':
                  east-=strtol(buf+1,NULL,10);
                  break;
              case 'R':
                  direction+=(strtol(buf+1,NULL,10)/90);
                  if(direction>4)
                      direction-=4;
                  break;
              case 'L':
                  direction-=(strtol(buf+1,NULL,10)/90);
                  if(direction<1)
                      direction+=4;
                  break;
              case 'F':
                  switch(direction)
                  {
                    case 1 :
                        north+=strtol(buf+1,NULL,10);
                        break;
                    case 2 :
                        east+=strtol(buf+1,NULL,10);
                        break;
                    case 3 :
                        north-=strtol(buf+1,NULL,10);
                        break;
                    case 4 :
                        east-=strtol(buf+1,NULL,10);
                        break;
                  }
                  break;
              default :
                  break;
            }
    else
        while(fgets(buf, 16, fp) != NULL)
            switch(buf[0])
            {
              case 'N':
                  wnorth+=strtol(buf+1,NULL,10);
                  break;
              case 'S':
                  wnorth-=strtol(buf+1,NULL,10);
                  break;
              case 'E':
                  weast+=strtol(buf+1,NULL,10);
                  break;
              case 'W':
                  weast-=strtol(buf+1,NULL,10);
                  break;
              case 'R':
                  for(temp2=(strtol(buf+1,NULL,10)/90);temp2;temp2--)
                  {
                      temp=wnorth;
                      wnorth=-(weast);
                      weast=temp;
                  }
                  break;
              case 'L':
                  for(temp2=(strtol(buf+1,NULL,10)/90);temp2;temp2--)
                  {
                      temp=wnorth;
                      wnorth=weast;
                      weast=-(temp);
                  }
                  break;
              case 'F':
                  temp=strtol(buf+1,NULL,10);
                  east+=(temp*weast);
                  north+=(temp*wnorth);
                  break;
              default :
                  break;
            }
    result=labs(north)+labs(east);
    printf("%ld\n",result);
    return 0;
}

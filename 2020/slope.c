#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long long result=1;
    int counter=0;
    int part=1;
    int rows=323;
    int cols=31;
    char buf[35];
    char *p;
    char grid[rows][cols];
    int r,c,x;
    int rise[5]={1,1,1,1,2};
    int run[5]={3,7,1,5,1};
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
    r=c=x=0;
    while(fgets(buf, 35, fp) != NULL)
    {
         p=buf;
         x=c=0;
         while(x==0)
         {
             switch(*p)
             {
               case '#':
                   grid[r][c]=1;
                   break;
               case '.':
                   grid[r][c]=0;
                   break;
               default:
                   r++;
                   x=1;
             }
             p++;
             c++;
         }
    }
    if(part==1)
    {
        for(int n=1;n<5;n++)
            rise[n]=rows;
    }
    for(int n=0;n<5;n++)
    {
        c=r=counter=0;
        while(r<rows)
        {
            if(grid[r][c])
                counter++;
            r+=rise[n];
            c= (c+run[n]) % (cols);
        }
        if(counter)
            result*=counter;
    }
    printf("%lld\n",result);
    return 0;
}

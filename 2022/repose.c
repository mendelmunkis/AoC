#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char slice[700][700]={0};

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[300];
    char *p;
    int xs,xe,ys,ye,i;
    int max=0;
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
    while(fgets(buf, 300, fp) != NULL)
    {
        p=strtok(buf,",>");
        xs=atoi(p);
        p=strtok(NULL,",>");
        ys=atoi(p);
        for(p=strtok(NULL,",>");p!=NULL;p=strtok(NULL,",>"))
        {
            xe=atoi(p);
            p=strtok(NULL,",>");
            ye=atoi(p);
            if(ye>max)
                max=ye;
            while((xs!=xe)||(ys!=ye))
            {
                slice[xs][ys]=5;
                if(xs<xe)
                    xs++;
                else if(xs>xe)
                    xs--;
                else if(ys<ye)
                    ys++;
                else if(ys>ye)
                    ys--;
            }
                slice[xs][ys]=5;

        }
   }
   if(part==2)
       for(int x=0;x<700;x++)
           slice[x][max+2]=5;

        for(i=0;;i++)
        {
            xs=500;
            ys=0;
            while(1)
            {
                if(ys>max+3)
                    break;
                if(slice[xs][ys+1]==0)
                {
                    ys++;
                    continue;
                }
                if(slice[xs-1][ys+1]==0)
                {
                    xs--;
                    ys++;
                    continue;
                }
                if(slice[xs+1][ys+1]==0)
                {
                    xs++;
                    ys++;
                    continue;
                }
                slice[xs][ys]=1;
                break;
            }
            if(((xs==500)&&(!ys))||(ys>max+3))
                break;
        }
    if(part==2)
        i++;
    result=i;
    printf("%ld\n",result);
    return 0;
}

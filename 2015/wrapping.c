#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN3(x,y,z) x<y?x<z?x:z:y<z?y:z
#define MIN2(x,y) x<y?x:y
#define MAX(x,y) x>y?x:y

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    char *bufp;
    FILE * fp;
    int l,w,h,f,s,b,box,min;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 16, fp) != NULL)
    {
//        if(buf[0]==' ')
//            break;
        bufp=strtok(buf,"x");
        l=strtol(bufp,NULL,10);
        bufp=strtok(NULL,"x");
        w=strtol(bufp,NULL,10);
        bufp=strtok(NULL,"x");
        h=strtol(bufp,NULL,10);
        if(part==1)
        {
            f=w*h;
            s=h*l;
            b=l*w;
            box=f;
            box+=s;
            box+=b;
            box*=2;
            box+=MIN3(f,s,b);
        }
        else
        {
            min=MIN2(w,h);
            f=MAX(w,h);
            min+=MIN2(f,l);
            box=min*2;
            box+=h*w*l;
        }
        result+=box;
//        printf("%dx%dx%d=%d\n",l,w,h,box);
//        printf("%dx%dx%d=%d\n",f,s,b,box);
  //     printf("%d\n",box);
    }
    printf("%ld\n",result);
    return 0;
}

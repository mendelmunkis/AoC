#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    int max[4]={0}, i=0;
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
    while(fgets(buf, 16, fp) != NULL)
    {
        if(buf[0] == '\n')
        {
            if(max[0]>max[1])
            {
                memmove(max+1,max,3*sizeof(int));
            }
            else if(max[0]>max[2])
            {
                memmove(max+2,max,2*sizeof(int));
            }
            else if(max[0]>max[3])
            {
                memmove(max+3,max,1*sizeof(int));
            }
            max[0]=0;
        }
        max[0]+=atoi(buf);
    }
    if(part==1)
        result = max[1];
    else
        result=max[1]+max[2]+max[3];
    printf("%ld\n",result);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    char buf[7010];
    FILE * fp;
    char *bufp=buf;
    int floor=0;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    fgets(buf, 7010, fp);
    while((*bufp != '\n')&&(*bufp != '\0'))
    {
        if(*bufp=='(')
            floor++;
        else
            floor--;
        bufp++;
        if(floor==-1)
            if(result==0)
                result=(bufp-buf);
    }
    if(part==1)
        result=floor;
    printf("%d\n",result);
    return 0;
}

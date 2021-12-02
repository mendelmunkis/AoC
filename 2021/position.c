#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16], *bufp;
    int x=0, y=0, aim=0, move;
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
        bufp=strtok(buf, " ");
        bufp=strtok(NULL, " ");
        move=strtol(bufp, NULL, 10);
        switch (buf[0])
        {
            case 'u':
                aim-=move;
                break;
            case 'd':
                aim+=move;
                break;
            case 'f':
                x+=move;
                y+=aim*move;
                break;
            default:
                printf("invalid direction\n");
        }
    }
    if(part==1)
        y=aim;
    result=x*y;
    printf("%ld\n",result);
    return 0;
}

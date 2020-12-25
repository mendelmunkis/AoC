#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
    long door, card;
    long hash=1,i=1;
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
    fgets(buf, 16, fp);
    card=strtol(buf,NULL,10);
    fgets(buf, 16, fp);
    door=strtol(buf,NULL,10);

    while(hash!=card)
    {
        i++;
        hash*=7;
        hash%=20201227;
    }
    hash=1;
    for(int j=1;j<i;j++)
    {
        hash*=door;
        hash%=20201227;
    }
    result=hash;
    printf("%ld\n",result);
    return 0;
}

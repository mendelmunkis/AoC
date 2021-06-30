#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NODES 8

//The Graph
int edges[NODES][NODES];

int compar (const void *a, const void *b);


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=LONG_MAX;
    int part=1;
    char buf[45];
    char *bufp;
    int i=NODES,z;
    int to,from;
    int distance, permutations=1;
    int perms[NODES];
    int stack[NODES];
    int x, temp;
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
    while(fgets(buf, 45, fp) != NULL)
    {
        bufp=strtok(buf," ");
        switch(*bufp)
        {
          case 'A':
            if(*(bufp+1)=='l')
                to=0;
            else
                to=1;
            break;
          case 'F':
            to=2;
            break;
          case 'N':
            to=3;
            break;
          case 'S':
            if(*(bufp+1)=='n')
                to=4;
            else
                to=5;
            break;
          case 'T':
            if(*(bufp+1)=='a')
                to=6;
            else
                to=7;
            break;
        }
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        switch(*bufp)
        {
          case 'A':
            if(*(bufp+1)=='l')
                from=0;
            else
                from=1;
            break;
          case 'F':
            from=2;
            break;
          case 'N':
            from=3;
            break;
          case 'S':
            if(*(bufp+1)=='n')
                from=4;
            else
                from=5;
            break;
          case 'T':
            if(*(bufp+1)=='a')
                from=6;
            else
                from=7;
            break;
        }
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        distance=strtol(bufp,NULL,10);
        edges[to][from]=edges[from][to]=distance;
    }
    if(part==2)
    result=LONG_MIN;
    for(i=0;i<NODES;i++)
    {
        perms[i]=i;
        permutations*=i+1;
    }
    for(/*permutations/=2*/;permutations;permutations--)
    {
        distance=0;
        for(i=0; i<=NODES-2;i++)
            distance+=edges[perms[i]][perms[i+1]];
        if( part==1 ? (distance< result) : (distance > result))
            result=distance;

        //worlds worst permutator
        i=NODES-2;
        z=0;
        stack[z++]=perms[i+1];
        while(perms[i]>perms[i+1])
        {
            stack[z++]=perms[i];
            i--;
        }
        qsort(stack,z-1,sizeof(int),compar);
        for(x=0;stack[x]<perms[i];x++);
        temp=perms[i];
        perms[i++]=stack[x];
        stack[x]=temp;
        qsort(stack,z,sizeof(int),compar);
        i=NODES-1;
        for(z-=1;z>=0;z--)
        {
            perms[i--]=stack[z];
        }
    }
    printf("%ld\n",result);
    return 0;
}


int compar (const void *a, const void *b)
{
    if(*(int *)a < *(int *)b)
        return -1;
    if(*(int *)a > *(int *)b)
        return 1;
    return 0;
}

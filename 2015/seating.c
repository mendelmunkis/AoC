#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NODES 9

//The Graph
int edges[NODES][NODES];

int compar (const void *a, const void *b);


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=LONG_MAX;
    int part=1;
    char buf[67];
    char *bufp;
    int nodes=NODES;
    if(argc > 1)
        part=atoi(argv[1]);
    if(part==1)
        nodes--;
    int i=nodes,z,neg;
    int to,from;
    int distance, permutations=1;
    int perms[nodes];
    int stack[nodes];
    int x, temp;
    FILE * fp;
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 67, fp) != NULL)
    {
        bufp=strtok(buf," ");
        switch(*bufp)
        {
          case 'A':
            to=0;
            break;
          case 'B':
            to=1;
            break;
          case 'C':
            to=2;
            break;
          case 'D':
            to=3;
            break;
          case 'E':
            to=4;
            break;
          case 'F':
            to=5;
            break;
          case 'G':
            to=6;
            break;
          case 'M':
            to=7;
            break;
        }
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        neg=strcmp(bufp,"lose")?0:1;
        bufp=strtok(NULL," ");
        distance=strtol(bufp,NULL,10);
        if(neg)
            distance=0-distance;
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        bufp=strtok(NULL," ");
        switch(*bufp)
        {
          case 'A':
            from=0;
            break;
          case 'B':
            from=1;
            break;
          case 'C':
            from=2;
            break;
          case 'D':
            from=3;
            break;
          case 'E':
            from=4;
            break;
          case 'F':
            from=5;
            break;
          case 'G':
            from=6;
            break;
          case 'M':
            from=7;
            break;
        }
        edges[to][from]=distance;
    }
    result=LONG_MIN;
    for(i=0;i<nodes;i++)
    {
        perms[i]=i;
        permutations*=i+1;
    }
    for(/*permutations/=2*/;permutations;permutations--)
    {
        distance=0;
        for(i=0; i<=nodes-2;i++)
            distance+=(edges[perms[i]][perms[i+1]] + edges[perms[i+1]][perms[i]]);
        distance+=(edges[perms[0]][perms[nodes-1]] + edges[perms[nodes-1]][perms[0]]);
        if(distance > result)
            result=distance;

        //worlds worst permutator
        i=nodes-2;
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
        i=nodes-1;
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

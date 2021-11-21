#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cup
{
    struct cup *next;
};
struct cup  cups[1000000];

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1, total=100, size=9;
    char buf[16];
    char intemp[2];
    int temp;
    int dest;
    int shufflea,shuffleb,shufflec;
//    int circj, circk;
    struct cup *last, *first, *current, *shuffle;
//    int k,l, j;
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
        intemp[0]=buf[0];
        last=first=&cups[strtol(intemp,NULL,10)-1];
        for(int i=1;i<9;i++)
        {
            intemp[0]=buf[i];
            temp=strtol(intemp,NULL,10);
            last->next=&cups[temp-1];
            last=&cups[temp-1];
        }
    }
    if(part==2)
    {
        total=10000000;
        size=1000000;
    }
    for(int i=9;i<size;i++)
    {
        last->next=&cups[i];
        last=&cups[i];
    }

    //Linked list implementation
    last->next=first;
    current=first;
    for(int i=0;i<total;i++)
    {
        shuffle=current->next;
        shufflea=((current->next+1)-cups);
        shuffleb=((current->next->next+1)-cups);
        shufflec=((current->next->next->next+1)-cups);
        current->next=current->next->next->next->next;
        dest =(current)-cups;
        if(!dest)
            dest=size;
        while((dest==shufflea)||(dest==shuffleb)||(dest==shufflec))
        {
            dest--;
            if(!dest)
                dest=size;
        }
        last=cups[dest-1].next;
        cups[dest-1].next=shuffle;
        shuffle->next->next->next=last;
        current=current->next;
    }
    current=cups[0].next;
    if(part==1)
        for(int i=0;i<8;i++)
        {
            result*=10;
            result+=(current+1)-cups;
            current=current->next;
        }
    else
    {
        result=1;
        result*=(current+1)-cups;
        current=current->next;
        result*=(current+1)-cups;
    }
    printf("%ld\n",result);
    return 0;

    //Double buffer implementation (requires some variable changes)
    /*
    total /=2;
    for(int i=0;i<total;i++)
    {
        if( !(i%50))
            printf("%ld\n",i);
        circj=current+1;
        for(j=0;j<3;j++)
        {
            circj%=size;
            temp[j]=circa[circj];
            circj++;
        }
        dest=circa[current]-1;
        if(!dest)
            dest=size;
        while((dest==temp[0])||(dest==temp[1])||(dest==temp[2]))
        {
            dest--;
            if(!dest)
                dest=size;
        }
        circj=current;
        circk=circj+3;
        circj%=size;
        circk%=size;
        while(circa[circj]!=dest)
        {
            circj++;
            circk++;
            circj%=size;
            circk%=size;
            circa[circj]=circa[circk];
        }
        circj++;
        for(j=0;j<3;j++)
        {
            circj%=size;
            circa[circj]=temp[j];
            circj++;
        }
        current++;
        current%=size;
    }
    */

    //Circular buffer implementation (requires some variable changes)
    /*
    for(int i=0;i<total;i++)
    {
        memcpy(temp,circa+1,3*sizeof(int));
        dest=circa[0]-1;
        if(!dest)
            dest=size;
        while((dest==temp[0])||(dest==temp[1])||(dest==temp[2]))
        {
            dest--;
            if(!dest)
                dest=size;
        }
        k=4;
        for(l=k;circa[l]!=dest;l++);
        memcpy(circb, circa+k, (l-(k-1))*sizeof(int));
        j=l-k;
        memcpy(circb+j+1, temp, 3*sizeof(int));
        memcpy(circb+j+4, circa+k+j+1, ((size-1)-l)*sizeof(int));
        circb[size-1]=circa[0];

        memcpy(temp,circb+1,3*sizeof(int));
        dest=circb[0]-1;
        if(!dest)
            dest=size;
        while((dest==temp[0])||(dest==temp[1])||(dest==temp[2]))
        {
            dest--;
            if(!dest)
                dest=size;
        }
        k=4;
        for(l=k;circb[l]!=dest;l++);
        memcpy(circa, circb+k, (l-(k-1))*sizeof(int));
        j=l-k;
        memcpy(circa+j+1, temp, 3*sizeof(int));
        memcpy(circa+j+4, circb+k+j+1, ((size-1)-l)*sizeof(int));
        circa[size-1]=circb[0];
    }
    */
    //Output for the last two
    /*
    k=0;
    for(int i=0;circa[i]!=1;i++)
        k=i;
    if(circa[k]!=1)
        k++;
    if(part==1)
    {
        for(int i=0;i<8;i++)
        {
            k++;
            k%=9;
            circb[i]=circa[k];
        }
        for(int i=0;i<8;i++)
            printf("%d",circb[i]);
        printf("\n");
    }
    else
        result=circa[k+1]*circa[k+2];
    printf("%ld\n",result);
    return 0;
    */
}

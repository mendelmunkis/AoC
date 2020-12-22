#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hand(char *state1, char *state2, int onecard, int twocards, int depth);

int part=1;

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    char buf[16];
    FILE * fp;
    int i=0,player=0;
    char cards[2][50];
    int onecards, twocards,total;
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
    while(fgets(buf, 16, fp) != NULL)
    {
        if(buf[0]=='\n')
        {
            player++;
            onecards=i;
            i=0;
            fgets(buf, 16, fp);
            continue;
        }
        cards[player][i]=atoi(buf);
        i++;
    }
    twocards=i;
    total=onecards+twocards;
    player=hand(cards[0], cards[1],onecards,twocards, 0);
    player--;
    for(i=1;i<=total;i++)
        result+=cards[player][total-i]*i;
    printf("%ld\n",result);
    return 0;
}

int hand(char *state1, char *state2, int onecard, int twocard, int depth)
{
    int onecards=onecard;
    int twocards=twocard;
    int winner=1;
    int one,two,i,j=0;
    char cards[2][onecards+twocards];
    memcpy(cards[0],state1,onecards*sizeof(char));
    memcpy(cards[1],state2,twocards*sizeof(char));
    while(onecards && twocards)
    {
        winner=1;
        one=cards[0][0];
        two=cards[1][0];
        twocards--;
        onecards--;
        memmove(cards[0],&cards[0][1],onecards*sizeof(char));
        memmove(cards[1],&cards[1][1],twocards*sizeof(char));
        if(part==1)
        {
            if(one<two)
                winner=2;
        }else
        {
            if((one<=onecards)&&(two <= twocards))
                winner=hand(cards[0], cards[1], one, two, depth+1);
            else if(one<two)
                winner=2;
        }
        if(winner==2)
        {
            cards[1][twocards]=two;
            twocards++;
            cards[1][twocards]=one;
            twocards++;
        }
        else
        {
            cards[0][onecards]=one;
            onecards++;
            cards[0][onecards]=two;
            onecards++;
        }
        j++;
        if(j>1500)
            return 1;
    }
    if(!depth)
    {
        memcpy(state1,cards,onecards*sizeof(char));
        memcpy(state2,cards[1],twocards*sizeof(char));
    }
    if(onecards)
        return 1;
    return 2;
}

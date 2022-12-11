#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct monkey
{
    long items[60];
    int operation;
    int operand;
    int test;
    int true;
    int false;
    int inspections;

};

int gcd(int x, int y);


int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long long result=0;
    int part=1;
    char buf[50];
    char *bufp;
    struct monkey monkeys[8]={0};
    int pass,k;
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
    while(fgets(buf, 50, fp) != NULL)
    {
        int monkey = atoi(buf+7);
        fgets(buf,50,fp);
        strtok(buf,":");
        int i=0;
        for(bufp=strtok(NULL,",");bufp!=NULL;bufp=strtok(NULL,","))
        {
            monkeys[monkey].items[i]=atoi(bufp);
            i++;
        }
        fgets(buf,50,fp);
        if(buf[23]=='*')
            monkeys[monkey].operation=1;
        else
            monkeys[monkey].operation=2;
        if(buf[25]!='o')
            monkeys[monkey].operand = atoi(buf+24);
        fgets(buf,50,fp);
        monkeys[monkey].test = atoi(buf+21);
        fgets(buf,50,fp);
        monkeys[monkey].true = atoi(buf+29);
        fgets(buf,50,fp);
        monkeys[monkey].false = atoi(buf+29);
        fgets(buf,50,fp);
    }
    long lcm=1;
    for(int monkey=0;monkey<8;monkey++)
        if(monkeys[monkey].test)
            lcm*=monkeys[monkey].test;
    lcm/=gcd(monkeys[0].test,gcd(monkeys[1].test,gcd(monkeys[2].test,gcd(monkeys[3].test,gcd(monkeys[4].test,gcd(monkeys[5].test,gcd(monkeys[6].test,monkeys[7].test)))))));
    for(int i=0; i<(part==1?20:10000);i++)
        for(int monkey=0;monkey<8;monkey++)
        {
            for(int j=0;monkeys[monkey].items[j];j++)
            {
                long item = monkeys[monkey].items[j];
                if(monkeys[monkey].operation==1)
                    item*=monkeys[monkey].operand?monkeys[monkey].operand:item;
                else
                    item+=monkeys[monkey].operand?monkeys[monkey].operand:item;
                if(part==1)
                    item/=3;
                else
                    item%=lcm;
                if(!(item%(monkeys[monkey].test)))
                    pass =monkeys[monkey].true;
                else
                    pass =monkeys[monkey].false;
                for(k=0;monkeys[pass].items[k];k++);
                monkeys[pass].items[k]=item;
                monkeys[monkey].inspections++;
            }
                memset(monkeys[monkey].items,0,sizeof(monkeys[monkey].items));
        }
    long long max[2]={0};
    for(int i=0;i<8;i++)
    {
        if(monkeys[i].inspections>max[0])
        {
            int temp=max[0];
            max[0]=monkeys[i].inspections;
            monkeys[i].inspections=temp;
        }
        if(monkeys[i].inspections>max[1])
            max[1]=monkeys[i].inspections;
    }
    result =max[0]*max[1];
    printf("%lu\n",result);
    return 0;
}

int gcd(int x, int y)
{
    int temp;
    while(y)
    {
        temp=y;
        y=x%y;
        x=temp;
    }
    return x;
}

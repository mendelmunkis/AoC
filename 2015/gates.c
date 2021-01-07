#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wire
{
    int set;
    unsigned short value;
    int operator;
    int opa;
    int opb;
};

struct wire wires[800]={0};

int hash(char *in);
int recurse(int in);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[20];
    char *bufp;
    unsigned int i,j,top,tops[2],tval,temp;
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
    wires[0].set=1;
    wires[0].value=0;
    while(fgets(buf, 20, fp) != NULL)
    {
        i=top=0;
        bufp=strtok(buf," ");
        while(bufp!=NULL)
        {
            if(*bufp>96)
            {
                tops[i]=hash(bufp);
                i++;
            }
            else if(*bufp>64)
                switch(*bufp)
                {
                   case 'A':
                     top=1;
                     break;
                   case 'L':
                     top=2;
                     break;
                   case 'N':
                     top=3;
                     break;
                   case 'O':
                     top=4;
                     break;
                   case 'R':
                     top=5;
                     break;
                }
            else if(*bufp==45)
                tval=hash(strtok(NULL,"\n"));
            else
            {
                temp=strtol(bufp,NULL,10);
                if(!temp)
                {
                    tops[i]=0;
                    i++;
                }
                else
                {
                    for(j=735;wires[j].set&&(wires[j].value !=temp);j++);
                    if(j>=800)
                        printf("HASH OVERFLOW\n");
                    wires[j].value=temp;
                    wires[j].set=1;
                    tops[i]=j;
                    i++;
                }
            }
            bufp=strtok(NULL," ");
        }
        wires[tval].operator=top;
        wires[tval].opa=tops[0];
        wires[tval].opb=tops[1];
    }
    result=recurse(1);
    if(part==2)
    {
        wires[2].value=recurse(1);
        for(int k=1;k<734;k++)
            wires[k].set=0;
        wires[2].set=1;
        result=recurse(1);
    }
    printf("%ld\n",result);
    return 0;
}

int hash(char *in)
{
    if(strlen(in)==1)
        return (*in)-96;
    return ((*in)-96)*27+*(in+1)-96;
}

int recurse(int in)
{
    int a,b,value;
    if(wires[wires[in].opa].set)
        a=wires[wires[in].opa].value;
    else
        a=recurse(wires[in].opa);
    if(wires[in].operator)
        if(wires[in].operator!=3)
            if(wires[wires[in].opb].set)
                b=wires[wires[in].opb].value;
            else
                b=recurse(wires[in].opb);
    switch(wires[in].operator)
    {
      case 0:
          wires[in].value=a;
          break;
      case 1:
          wires[in].value=a&b;
          break;
      case 2:
          wires[in].value=a<<b;  //TODO:verify in
          break;
      case 3:
          wires[in].value=~a;
          break;
      case 4:
          wires[in].value=a|b;
          break;
      case 5:
          wires[in].value=a>>b; //TODO: verify in
          break;
    }
    wires[in].set=1;
    return wires[in].value;
}

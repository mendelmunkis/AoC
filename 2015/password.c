#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check (char pass[8]);

int main (int argc, char * argv[])
{
    char *filename = "input";
    char *result;
    int part=1;
    char buf[16], pass[9];
    FILE * fp;
    int i;
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
        strcpy(pass, buf);
    }
    pass[8]='\0';
    for(i =0; i< 8; i++)
    {
        if((pass[i]=='i')||(pass[i]=='o')||(pass[i]=='l'))
        {
            pass[i]++;
            while(++i < 8)
                pass[i]='a';
        }
    }
    do
    {
        i=7;
        pass[i]++;
        if((pass[i]=='i')||(pass[i]=='o')||(pass[i]=='l'))
            pass[i]++;
        while(pass[i]=='{')
        {
            i--;
            pass[i]++;
            if((pass[i]=='i')||(pass[i]=='o')||(pass[i]=='l'))
                pass[i]++;
        }
        for(i++;i<8;i++)
            pass[i]='a';
    }while(!check(pass));
    if(part==2)
        do
        {
            i=7;
            pass[i]++;
            if((pass[i]=='i')||(pass[i]=='o')||(pass[i]=='l'))
                pass[i]++;
            while(pass[i]=='{')
            {
                i--;
                pass[i]++;
                if((pass[i]=='i')||(pass[i]=='o')||(pass[i]=='l'))
                    pass[i]++;
            }
            for(i++;i<8;i++)
                pass[i]='a';
        }while(!check(pass));
    result=pass;
    printf("%s\n",result);
    return 0;
}

int check (char pass[8])
{
    int rep=0;
    for(int i=0;i<8;i++)
        if(pass[i]==pass[i+1])
        {
            rep++;
            i++;
        }
    if(rep<2)
        return 0;
    for(int i=2;i<8;i++)
        if((pass[i]==pass[i-1]+1)&&(pass[i]==pass[i-2]+2))
            return 1;
    return 0;
}

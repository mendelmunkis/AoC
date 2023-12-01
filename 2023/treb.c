#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isnumber(char* c);

int part=1;

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    char buf[65];
    char ones, temp, tens=0;
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
    while(fgets(buf, 65, fp) != NULL)
    {
        int i =0;
        tens= 10*isnumber(buf+i);
        while(!tens)
            tens= 10*isnumber(buf+(++i));
        result+= tens;
        ones=temp=isnumber(buf+i);
        while(buf[++i]!='\n')
        {
            temp=isnumber(buf+i);
            if(temp)
                ones = temp;
        }
        result += ones;
    }
    printf("%ld\n",result);
    return 0;
}

int isnumber(char* c)
{
    if(*c > 48 && *c < 58)
        return (*c)-48;
    if(part== 1)
        return 0;
    switch(*c){
      case 'o':
        if(*(c+1)=='n'&& *(c+2)=='e')
            return 1;
        break;
      case 't':
        if(*(c+1)=='w'&& *(c+2)=='o')
            return 2;
        if(*(c+1)=='h'&& *(c+2)=='r')
            if(*(c+3)=='e'&& *(c+4)=='e')
            return 3;
        break;
      case 'f':
        if(*(c+1)=='o'&& *(c+2)=='u'&& *(c+3)=='r')
            return 4;
        if(*(c+1)=='i'&& *(c+2)=='v'&& *(c+3)=='e')
            return 5;
        break;
      case 's':
        if(*(c+1)=='i'&& *(c+2)=='x')
            return 6;
        if(*(c+1)=='e'&& *(c+2)=='v')
            if(*(c+3)=='e'&& *(c+4)=='n')
            return 7;
        break;
      case 'e':
        if(*(c+1)=='i'&& *(c+2)=='g')
            if(*(c+3)=='h'&& *(c+4)=='t')
            return 8;
        break;
      case 'n':
        if(*(c+1)=='i'&& *(c+2)=='n'&& *(c+3)=='e')
            return 9;
    }
    return 0;
}

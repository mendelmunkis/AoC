#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcnt(char *in);
int strcnt2(char *in);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[50];
//    char shortbuf[16];
    int chars=0, points=0;
    int (*f)(char *in)=strcnt;
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
    if(part==2)
        f=strcnt2;
    while(fgets(buf, 50, fp) != NULL)
    {
        chars+=strlen(buf)-1;
 //       buf[strlen(buf)-2]='\0';
//        snprintf(shortbuf,15,buf+1);
        points+=f(buf+1);
//       printf("%d\n",strlen(buf)-1);
//        printf("%d\n",strlen(shortbuf));
//        printf(shortbuf);
//        printf("\n");
    }
    if(part==1)
        result=chars-points;
    else
        result=points-chars;
//    printf("%ld\n",points);
//    printf("%ld\n",chars);
    printf("%ld\n",result);
    return 0;
}

int strcnt(char *in)
{
    int count=0;
    while(*in != '"')
    {
        if(*in=='\\')
        {
            in++;
            if(*in=='x')
                in+=2;
        }
        in++;
        count++;
    }
    return count;
}

int strcnt2(char *in)
{
    int count=6;
    while(*in != '"')
    {
        if(*in=='\\')
        {
            in++;
            if(*in=='\\')
                count+=3;
            else if(*in=='"')
                count+=3;
            else
                count+=2;
        }
        in++;
        count++;
    }
    return count;
}

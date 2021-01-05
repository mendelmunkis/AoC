#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1,flag=0;
    char buf[17];
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
    int vowels;
    while(fgets(buf, 20, fp) != NULL)
    {
        flag=vowels=0;
        for(int i=0;i<17;i++)
        {
            if(part==1)
            {
                if(i<16)
                {
                    if(!flag)
                        if(buf[i]==buf[i+1])
                            flag=1;
                    if((buf[i]=='a')&& (buf[i+1]=='b')||(buf[i]=='c')&& (buf[i+1]=='d')||(buf[i]=='p')&& (buf[i+1]=='q')||(buf[i]=='x')&& (buf[i+1]=='y'))
                    {
                        flag=2;
                        break;
                    }
                }
                if((buf[i]=='a')||(buf[i]=='e')||(buf[i]=='i')||(buf[i]=='o')||(buf[i]=='u'))
                    vowels++;
            }
            else
            {
                if(!flag)
                    if(i<15)
                        if(buf[i]==buf[i+2])
                            flag=1;
                if(!vowels)
                    if(i<13)
                        for(int j=i+2;j<15;j++ )
                            if((buf[i]==buf[j])&&(buf[i+1]==buf[j+1]))
                                vowels=3;
            }
        }
        if((vowels>2)&(flag==1))
            result++;
//            printf("%s\n",buf);
    }
    printf("%ld\n",result);
    return 0;
}

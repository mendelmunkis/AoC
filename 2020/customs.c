#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0, counter=0,group=0;
    int part=1;
    char buf[36];
    char *cp;
    char questions[26]={0};
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
    while(fgets(buf, 36, fp) != NULL)
    {
        group++;
        for(cp=buf;*cp!='\n'&&(*cp!='\0');cp++)
            questions[*(cp)-97]++;
        if((buf[0]=='\n')|| buf[0]=='\0')
        {
            for(int i=0;i<26;i++)
                if(part==1)
                {
                    if(questions[i])
                        counter++;
                }
                else
                    if(questions[i]==(group-1))
                        counter++;
            memset(questions,0,26);
            result+=counter;
            counter=group=0;
        }
    }
    for(int i=0;i<26;i++)
        if(part==1)
        {
            if(questions[i])
                counter++;
        }
        else
            if(questions[i]==group)
                counter++;
    result+=counter;
    printf("%d\n",result);
    return 0;
}

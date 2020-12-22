#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1,flag=1;
    char buf[90];
    char exps[140][3000]={0};
    char *bufp;
    int inputs[140][7]={0};
    int rule,i,start,end;
    regex_t preg, endreg;
    regmatch_t pmatch, endmatch;
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
    while(fgets(buf, 90, fp) != NULL)
    {
        i=0;
        if(buf[0]=='\n')
            break;
        rule=strtol(buf,&bufp,10);
        if(*(bufp+2)=='"')
        {
            exps[rule][0]=*(bufp+3);
            continue;
        }
        exps[rule][0]='(';
        while(*(bufp++))
        {
            if(*bufp=='|')
                inputs[rule][i]=150;
            else
                inputs[rule][i]=strtol(bufp,&bufp,10);
           i++;
        }
    }
    exps[0][0]='^';
    exps[0][1]='(';
    if(part==2)
    {
        exps[42][0]='^';
        exps[42][1]='(';
    }
    while(flag)
    {
        flag=0;
        for(int j=0;j<140;j++)
        {
            if(inputs[j][0]==150)
            {
                strcat(exps[j],"|");
                flag=1;
                for(int k=0;k<6;k++)
                    inputs[j][k]=inputs[j][k+1];
                continue;
            }
            if(!inputs[j][0])
                continue;
            if(!inputs[inputs[j][0]][0])
            {
                strcat(exps[j],exps[inputs[j][0]]);
                flag=1;
                for(int k=0;k<6;k++)
                    inputs[j][k]=inputs[j][k+1];
                if(inputs[j][0]==0)
                {
                    strcat(exps[j],")");
                }
            }
        }
    }
    strcat(exps[0],"$");
    if(part==1)
    {
        if(regcomp(&preg, exps[0], REG_NOSUB|REG_EXTENDED|REG_NEWLINE))
            printf("Regex ERROR\n");
        while(fgets(buf, 90, fp) != NULL)
        {
            if(!regexec(&preg, buf, 0,0,0))
                result++;
        }
    }
    else
    {
        strcat(exps[42],"+$");
        strcat(exps[31],"+$");
        if(regcomp(&preg, exps[42], REG_EXTENDED|REG_NEWLINE))
            printf("Regex ERROR\n");
        if(regcomp(&endreg, exps[31], REG_EXTENDED|REG_NEWLINE))
            printf("Regex ERROR\n");
        while(fgets(buf, 90, fp) != NULL)
        {
            start=end=0;
            if(!regexec(&endreg, buf, 1,&endmatch,0))
                end=(endmatch.rm_eo-endmatch.rm_so);
            buf[endmatch.rm_so]='\0';
            if(!regexec(&preg, buf, 1,&pmatch,0))
                start=(pmatch.rm_eo-pmatch.rm_so);
            if(end&&(start>end))
                result++;
        }
    }
    printf("%d\n",result);
    return 0;
}

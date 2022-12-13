#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char **left, char **right);
int cmp(const void *left, const void *right);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char bufa[250], bufb[250];
    char sorted[500][250];
    int pair=0;
    int i;
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
    if(part==1)
        while((fgets(bufa, 250, fp) != NULL)&&(fgets(bufb, 250, fp) != NULL))
        {
            char *a = bufa+1;
            char *b = bufb+1;
            pair++;
            if(compare(&a,&b)>0)
                result+=pair;
            fgets(bufa,50,fp);
        }
    else
    {
        while(fgets(bufa, 250, fp) != NULL)
        {
            if(bufa[0]=='\n')
                continue;
            strcpy(sorted[pair++],bufa);
        }
            strcpy(sorted[pair++],"[[2]]");
            strcpy(sorted[pair++],"[[6]]");
            qsort(sorted,pair,250,cmp);
            for(i=0;i<pair;i++)
                if(!strcmp(sorted[i],"[[2]]"))
                    break;
            result=i+1;
            for(;i<pair;i++)
                if(!strcmp(sorted[i],"[[6]]"))
                    break;
            result*=(i+1);
    }
    printf("%ld\n",result);
    return 0;
}

int cmp(const void *left, const void *right)
{
    char a[250];
    char b[250];
    char *x =a+1;
    char *y =b+1;
    strcpy(a,left);
    strcpy(b,right);
    int ret=0-compare(&x,&y);
    return ret;
}

// 0 further consideration, 1 correct, -1 wrong
int compare(char **left, char **right)
{
    char enlist[10]={'['};
    char *e =enlist+1;
    int x,y;
    while(1)
    {
        if(*(*left)==',')
            (*left)++;
        if(*(*right)==',')
            (*right)++;
        if((*(*right)==']')&&(*(*left)!=']'))
            return -1;
        if(*(*left)=='[')
        {
             if(*(*right)=='[')
             {
                 (*left)++;
                 (*right)++;
                 x= compare(left,right);
                 if(x)
                    return x;
                 continue;
             }
             int i=1;
             for(;*(*right)<58 && *(*right)>47;(*right)++)
                 enlist[i++]=*(*right);
             enlist[i]=']';
                (*left)++;
                //(*right)++;
                 x= compare(left,&e);
             if(x)
                return x;
             continue;
        }
        if(*(*left)==']')
            if(*(*right)==']')
            {
            (*left)++;
            (*right)++;
                return 0;
            }
            else
                return 1;
        if(*(*right)=='[')
        {
             int i=1;
             for(;*(*left)<58 && *(*left)>47;(*left)++)
                 enlist[i++]=*(*left);
             enlist[i]=']';
                //(*left)++;
                (*right)++;
                 x= compare(&e, right);
             if(x)
                return x;
             continue;
        }
        x=atoi(*left);
        y=atoi(*right);
        if(x<y)
            return 1;
        if(x>y)
            return -1;
        for(;*(*left)<58 && *(*left)>47;(*left)++);
        for(;*(*right)<58 && *(*right)>47;(*right)++);
    }
}

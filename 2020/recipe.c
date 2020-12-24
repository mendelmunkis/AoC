#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char key[10];
    int seen;
};
struct node hashmap[3000]={0};

int shash(const char *s);
int compare(const void *a, const void *b);

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[530];
    int pot[8][82]={0};
    int list[82], final[8];
    char *bufp;
    int hash,allergen;
    int i=0;
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
    strcat(hashmap[0].key,"ae");
    while(fgets(buf, 530, fp) != NULL)
    {
        i=0;
        memset(list, 0, 82*sizeof(int));
        bufp=strtok(buf," ");
        while(bufp!=NULL)
        {
            hash = shash(bufp);
            while((hashmap[hash].key[0])&&(strcmp(hashmap[hash].key,bufp)))
                hash=((hash+1)%3000);
            strcpy(hashmap[hash].key,bufp);
            hashmap[hash].seen++;
            list[i]=hash;
            i++;
            bufp=strtok(NULL, " ");
            if(*bufp=='(')
                break;
        }
        qsort(list,82,sizeof(int),compare);
        while((bufp=strtok(NULL,", \n"))!=NULL)
        {
            switch(*bufp)
            {
                case 'd':
                  allergen=0;
                  break;
                case 'e':
                  allergen=1;
                  break;
                case 'f':
                  allergen=2;
                  break;
                case 'n':
                  allergen=3;
                  break;
                case 'p':
                  allergen=4;
                  break;
                case 's':
                  if(*(bufp+1)=='e')
                      allergen=5;
                  else
                      allergen=6;
                  break;
                case 'w':
                  allergen=7;
                  break;
                default:
                  printf("Allergen error\n");
                  break;
            }
            if(!pot[allergen][0])
                memcpy(pot[allergen],list,82*sizeof(int));
            else
            {
                for(int j=0, k=0; pot[allergen][j];)
                    if(pot[allergen][j]==list[k])
                    {
                        j++;
                        k++;
                    }
                    else if((pot[allergen][j]<list[k])||(!list[k]))
                    {
                        pot[allergen][j]=0;
                        j++;
                    }
                    else if(pot[allergen][j]>list[k])
                    {
                        k++;
                        if(k>=82)
                            break;
                    }
                qsort(pot[allergen],82,sizeof(int),compare);
            }
        }
    }
    if(part==1)
    {
        for(int j=1;j<3000;j++)
        {
            if(!hashmap[j].seen)
                continue;
            for(int k=0;k<8;k++)
                for(int l=0;pot[k][l];l++)
                {
                    if(pot[k][l]==j)
                        goto seen;
                }
            result+=hashmap[j].seen;
seen:;
        }
        printf("%ld\n",result);
        return 0;
    }
    hashmap[0].key[0]=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(pot[j][1]==0)
            {
                hash=pot[j][0];
                pot[j][1]=25;
                final[j]=hash;
                for(int k=0;k<8;k++)
                {
                    if(k==j)
                        continue;
                    for(int l=0;l<8;l++)
                        if(pot[k][l]==hash)
                        {
                            if(l!=7)
                                pot[k][l]=pot[k][l+1];
                            else
                                pot[k][l]=0;
                            while(pot[k][l])
                            {
                                l++;
                                if(l!=7)
                                    pot[k][l]=pot[k][l+1];
                                else
                                    pot[k][l]=0;
                            }
                        }
                }
            }

    for(int i =0; i<7;i++)
    {
            printf(hashmap[final[i]].key);
                printf(",");
    }
    printf(hashmap[final[7]].key);
    printf("\n");
    return 0;
}

int shash(const char *s)
{
    unsigned int hash=1;
    while(*s!='\0'){
        hash*=*(s++)-60;
        hash+=*(s)-60;}
    hash%=3000;
    return hash;
}

int compare(const void *a, const void *b)
{
    const int *x=a;
    const int *y=b;
    if(!(*x))
        if(!(*y))
            return 0;
        else
            return 1;
    if(!(*y))
        return -1;
    if(*x<*y)
        return -1;
    if(*x>*y)
        return 1;
    return 0;
}





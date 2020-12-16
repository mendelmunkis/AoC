#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELDS 20

int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long long result=0, flag=0;
    int part=1, value;
    char buf[85];
    int ranges[20][4];
    int mine[20], tickets[250][20]={0};
    int field[20][20], final[20];
    int c, k=0;
    char *bufp;
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
    for(int i=0;i<FIELDS;i++)
    {
        fgets(buf, 85, fp);
        strtok(buf,":");
        bufp=strtok(NULL,"-");
        ranges[i][0]=strtol(bufp,NULL,10);
        bufp=strtok(NULL,"r");
        ranges[i][1]=strtol(bufp,NULL,10);
        bufp=strtok(NULL,"-");
        ranges[i][2]=strtol(bufp,NULL,10);
        bufp=strtok(NULL,"-");
        ranges[i][3]=strtol(bufp,NULL,10);
    }
    for(int i=0;i<3;i++)
        fgets(buf, 85, fp);
    if(part==2)
    {
        bufp=strtok(buf,",");
        mine[0]=strtol(bufp,NULL,10);
        for(int i=1;i<FIELDS;i++)
        {
            bufp=strtok(NULL,",");
            mine[i]=strtol(bufp,NULL,10);
        }
    }
    for(int i=0;i<2;i++)
        fgets(buf, 85, fp);
    while(fgets(buf, 85, fp)!=NULL)
    {
        flag=0;
        bufp=strtok(buf,",");
        value=strtol(bufp,NULL,10);
        for(int j=0;j<FIELDS;j++)
            if((value<ranges[j][0])||((value<ranges[j][2])&&(value>ranges[j][1]))||(value>ranges[j][3]))
                flag++;
        if(flag==FIELDS)
        {
            result+=value;
            continue;
        }else
        {
            k++;
            tickets[k][0]=value;
        }
        for(int i=1;i<FIELDS;i++)
        {
            flag=0;
            bufp=strtok(NULL,",");
            value=strtol(bufp,NULL,10);
            for(int j=0;j<FIELDS;j++)
                if((value<ranges[j][0])||((value<ranges[j][2])&&(value>ranges[j][1]))||(value>ranges[j][3]))
                    flag++;
            if(flag==FIELDS)
            {
                result+=value;
                k--;
                break;
            }else
                tickets[k][i]=value;
        }
    }
    if(part==2)
    {
        for(int l = 0;l<FIELDS;l++)
        {
            for(int i=0;i<FIELDS;i++)
            {
                flag=0;
                for(int j=1; j<=k;j++)
                {
                    value=tickets[j][i];
                    if((value<ranges[l][0])||((value<ranges[l][2])&&(value>ranges[l][1]))||(value>ranges[l][3]))
                    {
                        flag++;
                        break;
                    }
                }
                if(!flag)
                {
                    field[l][i]=1;
                }
            }
        }
        flag=0;
        while(flag<FIELDS)
        {
            for(int i=0;i<FIELDS;i++)
            {
                value=0;
                for(int j=0;j<FIELDS;j++)
                    value+=field[j][i];
                if(value==1)
                {
                    for(int j=0;j<FIELDS;j++)
                        if(field[j][i])
                        {
                            final[j]=i;
                            flag++;
                            memset(field[j],0,FIELDS*sizeof(int));
                            break;
                        }
                }
            }
        }
        result=1;
        for(int i=0;i<6;i++)
            result*=mine[final[i]];
    }
    printf("%llu\n",result);
    return 0;
}

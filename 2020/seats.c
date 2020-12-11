#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iterate1(char room[94][94]);
int iterate2(char room[94][94]);

int part=1;

int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    char buf[95];
    char room[94][94]={0};
    int i=1;
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
    while(fgets(buf, 95, fp) != NULL)
    {
        for(int j=0;buf[j]!='\n';j++)
            if(buf[j]=='#')
                room[i][j+1]=2;
            else if(buf[j]=='L')
                room[i][j+1]=1;
        i++;
    }
    if(part==1)
        while(iterate1(room));
    else
        while(iterate2(room));
    for(int r=0;r<94;r++)
        for(int c=0;c<94;c++)
            if(room[r][c]==2)
                result++;
    printf("%d\n",result);
    return 0;
}

int iterate1(char room[94][94])
{
    int a;
    char out[94][94]={0};
    for(int r=0;r<94;r++)
        for(int c=0;c<94;c++)
            if(room[r][c]==2)
            {
                a=0;
                for(int i=r-1;i<=r+1;i++)
                    for(int j=c-1;j<=c+1;j++)
                        if(room[i][j]==2)
                            a++;
                if(a>4)
                   out[r][c]=1;
               else
                   out[r][c]=2;
            }
            else if(room[r][c]==1)
            {
                a=0;
                for(int i=r-1;i<=r+1;i++)
                    for(int j=c-1;j<=c+1;j++)
                        if(room[i][j]==2)
                            a++;
                if(a)
                   out[r][c]=1;
               else
                   out[r][c]=2;
            }
    a=0;
    for(int r=1;r<94;r++)
        for(int c=1;c<94;c++)
            if(out[r][c]!=room[r][c])
            {
                a=1;
                break;
            }
    memcpy(room,out,(sizeof(char)*94*94));
    return a;
}

int iterate2(char room[94][94])
{
    int a, i,j;
    char out[94][94]={0};
    for(int r=1;r<93;r++)
        for(int c=1;c<93;c++)
            if(room[r][c]==2)
            {
                a=0;
                for(i=r-1;(room[i][c]==0)&&(i>0);i--);
                    if(room[i][c]==2)
                        a++;
                for(i=r+1;(room[i][c]==0)&&(i<94);i++);
                    if(room[i][c]==2)
                        a++;
                for(i=c-1;(room[r][i]==0)&&(i>0);i--);
                    if(room[r][i]==2)
                        a++;
                for(i=c+1;(room[r][i]==0)&&(i<94);i++);
                    if(room[r][i]==2)
                        a++;
                for(i=r-1,j=c-1;(room[i][j]==0)&&((i>0)&&(j>0));i--)
                    j--;
                    if(room[i][j]==2)
                        a++;
                for(i=r-1,j=c+1;(room[i][j]==0)&&((i>0)&&(j<94));i--)
                    j++;
                    if(room[i][j]==2)
                        a++;
                for(i=r+1,j=c-1;(room[i][j]==0)&&((i<94)&&(j>0));i++)
                    j--;
                    if(room[i][j]==2)
                        a++;
                for(i=r+1,j=c+1;(room[i][j]==0)&&((i<94)&&(j<94));i++)
                    j++;
                    if(room[i][j]==2)
                        a++;
                if(a>4)
                   out[r][c]=1;
               else
                   out[r][c]=2;
            }
            else if(room[r][c]==1)
            {
                a=0;
                for(i=r-1;(room[i][c]==0)&&(i>0);i--);
                    if(room[i][c]==2)
                        a++;
                for(i=r+1;(room[i][c]==0)&&(i<94);i++);
                    if(room[i][c]==2)
                        a++;
                for(i=c-1;(room[r][i]==0)&&(i>0);i--);
                    if(room[r][i]==2)
                        a++;
                for(i=c+1;(room[r][i]==0)&&(i<94);i++);
                    if(room[r][i]==2)
                        a++;
                for(i=r-1,j=c-1;(room[i][j]==0)&&((i>0)&&(j>0));i--)
                    j--;
                    if(room[i][j]==2)
                        a++;
                for(i=r-1,j=c+1;(room[i][j]==0)&&((i>0)&&(j<94));i--)
                    j++;
                    if(room[i][j]==2)
                        a++;
                for(i=r+1,j=c-1;(room[i][j]==0)&&((i<94)&&(j>0));i++)
                    j--;
                    if(room[i][j]==2)
                        a++;
                for(i=r+1,j=c+1;(room[i][j]==0)&&((i<94)&&(j<94));i++)
                    j++;
                    if(room[i][j]==2)
                        a++;
               if(a)
                   out[r][c]=1;
               else
                   out[r][c]=2;
            }
    a=0;
    for(int r=1;r<94;r++)
        for(int c=1;c<94;c++)
            if(out[r][c]!=room[r][c])
            {
                a=1;
                break;
            }
    memcpy(room,out,(sizeof(char)*94*94));
    return a;
}

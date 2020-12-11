#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iterate1(char room[94][94]);
int iterate2(char room[94][94]);
void load(char room[94][94]);

unsigned char visible[94][94][8][2]={0};
//#pragma GCC push_options
//#pragma GCC optimize (0)

int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
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
            if(buf[j]=='L')
                room[i][j+1]=1;
//            else if(buf[j]=='#')
//                room[i][j+1]=2;
        i++;
    }
    if(part==1)
        while(iterate1(room));
    else
    {
        load(room);
        while(iterate2(room));
    }
    for(int r=1;r<93;r++)
        for(int c=1;c<93;c++)
            if(room[r][c]==2)
                result++;
    printf("%d\n",result);
    return 0;
}
//#pragma GCC pop_options

int iterate1(char room[94][94])
{
    int a;
    char out[94][94]={0};
    for(int r=1;r<93;r++)
        for(int c=1;c<93;c++)
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
    for(int r=0;r<94;r++)
        for(int c=0;c<94;c++)
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
    int a;
    char out[94][94]={0};
    for(int r=1;r<93;r++)
        for(int c=1;c<93;c++)
            if(room[r][c])
            {
                a=0;
                for(int i=0;i<8;i++)
                    if(room[visible[r][c][i][0]][visible[r][c][i][1]]==2)
                        a++;
               if((a>4)||((room[r][c]==1)&& a))
                   out[r][c]=1;
               else
                   out[r][c]=2;
            }
    a=0;
    for(int r=1;r<93;r++)
        for(int c=1;c<93;c++)
            if(out[r][c]!=room[r][c])
            {
                a=1;
                break;
            }
    memcpy(room,out,(sizeof(char)*94*94));
    return a;
}

void load(char room[94][94])
{
    int i,j;
    for(int r=1;r<93;r++)
        for(int c=1;c<93;c++)
            if(room[r][c])
            {
                for(i=r-1;(room[i][c]==0)&&(i>0);i--);
                    visible[r][c][0][0]=i;
                    visible[r][c][0][1]=c;
                for(i=r+1;(room[i][c]==0)&&(i<94);i++);
                    visible[r][c][1][0]=i;
                    visible[r][c][1][1]=c;
                for(i=c-1;(room[r][i]==0)&&(i>0);i--);
                    visible[r][c][2][0]=r;
                    visible[r][c][2][1]=i;
                for(i=c+1;(room[r][i]==0)&&(i<94);i++);
                    visible[r][c][3][0]=r;
                    visible[r][c][3][1]=i;
                for(i=r-1,j=c-1;(room[i][j]==0)&&((i>0)&&(j>0));i--)
                    j--;
                    visible[r][c][4][0]=i;
                    visible[r][c][4][1]=j;
                for(i=r-1,j=c+1;(room[i][j]==0)&&((i>0)&&(j<94));i--)
                    j++;
                    visible[r][c][5][0]=i;
                    visible[r][c][5][1]=j;
                for(i=r+1,j=c-1;(room[i][j]==0)&&((i<94)&&(j>0));i++)
                    j--;
                    visible[r][c][6][0]=i;
                    visible[r][c][6][1]=j;
                for(i=r+1,j=c+1;(room[i][j]==0)&&((i<94)&&(j<94));i++)
                    j++;
                    visible[r][c][7][0]=i;
                    visible[r][c][7][1]=j;
            }
}

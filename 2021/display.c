#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[95], *bufp;
    char display[10][8];
    int digit[4];
    char show[8];
    int i,j,k,l,m, n,o;
    char a,b,c,d,e,f,g;
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
        bufp=strtok(buf," ");
        strncpy(display[0],bufp,8);
        for(i=1; i< 10;i++)
        {
            bufp=strtok(NULL," ");
            strncpy(display[i],bufp,8);
        }
        if(part==2)
        {
            for(i=0;i<10;i++)         //i=1
                if(display[i][2]=='\0')
                    break;
            for(j=0;j<10;j++)         //j=7
                if((j!=i)&&(display[j][3]=='\0'))
                    break;
            if((display[j][0]!=display[i][0])&&(display[j][0]!=display[i][1]))
                a=display[j][0];
            else if((display[j][1]!=display[i][0])&&(display[j][1]!=display[i][1]))
                a=display[j][1];
            else if((display[j][2]!=display[i][0])&&(display[j][2]!=display[i][1]))
                a=display[j][2];
            else printf("no single 1 7 \n");


            for(o=0;o<10;o++)         //o=8
                if(display[o][6]!='\0')
                    break;
            for(k=0;k<10;k++)         //k=3
                if((display[k][5]=='\0')&&(display[k][4]!='\0'))
                    if((a==display[k][0])||(a==display[k][1])||(a==display[k][2])||(a==display[k][3])||(a==display[k][4]))
                        if((display[i][0]==display[k][0])||(display[i][0]==display[k][1])||(display[i][0]==display[k][2])||
                          (display[i][0]==display[k][3])||(display[i][0]==display[k][4]))
                            if((display[i][1]==display[k][0])||(display[i][1]==display[k][1])||(display[i][1]==display[k][2])
                              ||(display[i][1]==display[k][3])||(display[i][1]==display[k][4]))
                                break;
            for(l=0;l<10;l++)         //l=4
                if((display[l][4]=='\0')&&(display[l][3]!='\0'))
                    break;

            for(int tmp=0;tmp<4;tmp++)
                if((display[l][tmp]!=display[k][0])&&(display[l][tmp]!=display[k][1])&&(display[l][tmp]!=display[k][2])
                  &&(display[l][tmp]!=display[k][3])&&(display[l][tmp]!=display[k][4]))
                {
                    b=display[l][tmp];
                    break;
                }


            for(m=0;m<10;m++)         //m=5
                if((display[m][5]=='\0')&&(display[m][4]!='\0'))
                    if((m!=k)&&((b==display[m][0])||(b==display[m][1])||(b==display[m][2])||(b==display[m][3])||(b==display[m][4])))
                        break;
            for(n=0;n<10;n++)         //n=2
                if((display[n][5]=='\0')&&(display[n][4]!='\0'))
                    if((n!=k)&&(n!=m))
                        break;

            for(int tmp=0;tmp<2;tmp++)
                if((display[i][tmp]==display[n][0])||(display[i][tmp]==display[n][1])||(display[i][tmp]==display[n][2])||(display[i][tmp]==display[n][3])||(display[i][tmp]==display[n][4]))
                    c=display[i][tmp];
            for(int tmp=0;tmp<2;tmp++)
                if(display[i][tmp]!=c)
                    f=display[i][tmp];
            for(int tmp=0;tmp<4;tmp++)
                if((display[l][tmp]!=b)&&(display[l][tmp]!=c)&&(display[l][tmp]!=f))
                    d=display[l][tmp];
            for(int tmp=0;tmp<5;tmp++)
                if((display[k][tmp]!=a)&&(display[k][tmp]!=c)&&(display[k][tmp]!=d)&&(display[k][tmp]!=f))
                    g=display[k][tmp];
            for(int tmp=0;tmp<7;tmp++)
                if((display[o][tmp]!=a)&&(display[o][tmp]!=b)&&(display[o][tmp]!=c)&&(display[o][tmp]!=d)&&(display[o][tmp]!=f)&&(display[o][tmp]!=g))
                    e=display[o][tmp];

        }
        bufp=strtok(NULL," ");
        if(part==1)
        {
            for(i=0;i<4;i++)
            {
                j=0;
                bufp=strtok(NULL," ");
                while((*bufp !='\0')&&(*bufp !='\n'))
                {
                    bufp++;
                    j++;
                }
                if((j==2)||(j==3)||(j==4)||(j==7))
                    result++;
            }
        }else
        {
            for(i=0;i<4;i++)
            {
                bufp=strtok(NULL," ");
                strncpy(show,bufp,8);
                if((show[0]==b)||(show[1]==b)||(show[2]==b)||(show[3]==b)||(show[4]==b)||(show[5]==b)||(show[6]==b)||(show[7]==b))
                {
                    if((show[0]==e)||(show[1]==e)||(show[2]==e)||(show[3]==e)||(show[4]==e)||(show[5]==e)||(show[6]==e)||(show[7]==e))
                    {
                        if((show[0]==c)||(show[1]==c)||(show[2]==c)||(show[3]==c)||(show[4]==c)||(show[5]==c)||(show[6]==c)||(show[7]==c))
                        {
                            if((show[0]==d)||(show[1]==d)||(show[2]==d)||(show[3]==d)||(show[4]==d)||(show[5]==d)||(show[6]==d)||(show[7]==d))
                                digit[i]=8;
                            else
                                digit[i]=0;
                        }else
                            digit[i]=6;
                    }
                    else if((show[0]==c)||(show[1]==c)||(show[2]==c)||(show[3]==c)||(show[4]==c)||(show[5]==c)||(show[6]==c)||(show[7]==c))
                    {
                        if((show[0]==a)||(show[1]==a)||(show[2]==a)||(show[3]==a)||(show[4]==a)||(show[5]==a)||(show[6]==a)||(show[7]==a))
                            digit[i]=9;
                        else
                            digit[i]=4;
                    }else
                        digit[i]=5;
                }else if((show[0]==g)||(show[1]==g)||(show[2]==g)||(show[3]==g)||(show[4]==g)||(show[5]==g)||(show[6]==g)||(show[7]==g))
                {
                    if((show[0]==e)||(show[1]==e)||(show[2]==e)||(show[3]==e)||(show[4]==e)||(show[5]==e)||(show[6]==e)||(show[7]==e))
                        digit[i]=2;
                    else
                        digit[i]=3;
                }else if((show[0]==a)||(show[1]==a)||(show[2]==a)||(show[3]==a)||(show[4]==a)||(show[5]==a)||(show[6]==a)||(show[7]==a))
                    digit[i]=7;
                 else
                    digit[i]=1;
            }
            result+=digit[3];
            result+=digit[2]*10;
            result+=digit[1]*100;
            result+=digit[0]*1000;
        }
    }
    printf("%ld\n",result);
    return 0;
}

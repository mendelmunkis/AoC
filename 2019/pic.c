#include <stdio.h>
#include <string.h>

int main (int argc, char * argv[])
{
    char part=1;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    int layer[6][25]={0};
    int ans  [6][25];
    int zeros,row,col=0;
    int anszeros = 150;
    int ones,twos,layernum;
    if(part==2)
    {
        for(row=0;row < 6;row++)
            for(col=0;col < 25;col++)
                ans[row][col] = 50;
    }
    for(layernum=0;layernum < 100;layernum++)
    {
        for(row=0;row < 6;row++)
            for(col=0;col < 25;col++)
                layer[row][col] = fgetc(fp);
        zeros=ones=twos=0;
        for(row=0;row < 6;row++)
        {
            for(col=0;col < 25;col++)
            {
                if(part==1)
                    switch(layer[row][col])
                    {
                        case 48:
                            zeros++;
                            break;
                        case 49:
                            ones++;
                            break;
                        case 50:
                            twos++;
                    }
                else if (ans[row][col] == 50)
                    ans[row][col] = layer[row][col];
            }
        }
        if(part == 1)
            if(zeros<anszeros)
            {
                anszeros=zeros;
                ans[0][0]=ones*twos;
            }
    }
    if(part==2)
    {
        printf("\x1b[41m");
        for(row=0;row < 6;row++)
        {
            for(col=0;col < 25;col++)
            {
                if(ans[row][col] == 48)
                    printf("\x1b[30m" "ש");
                else if(ans[row][col] == 49)
                    printf("\x1b[37m" "ש");
                else
                    printf("error");
            }
            printf("\n");
        }
        printf("\x1b[40m");
    }
    else
        printf("%d\n", ans[0][0]);
}

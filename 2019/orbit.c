#include <stdio.h>
#include <string.h>

int main (int argc, char * argv[])
{
    int x=0,y=0,in=0,out=0;
    char part=1;
    FILE * fp;
    static int ram[1000000][2]={0};
    char buf[30], *buf2;
    static char buf3 [2000][2][4]={0};
    static int buf4 [2000][2]={0};
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    for(;fgets(buf, 3000, fp) != NULL;out=0)
    {
        for(buf2 = strtok(buf, ")"); buf2 ; buf2 = strtok(NULL, "\n"))
        {
            strcpy(buf3[in][out], buf2);
            out++;
        }
        in++;
    }
    for(in=0;in < 2000;in++)
        for(out=0;out < 2;out++)
        {
            buf4[in][out] += buf3[in][out][2];
            buf4[in][out] += buf3[in][out][1] * 100;
            buf4[in][out] += buf3[in][out][0] * 10000;
        }
    for(in=0;in < 2000;in++)
        ram[buf4[in][1]][0] = buf4[in][0];
    if(part==1)
    {
        for(x=1;x!=0;in=0)
            for(x=0;in<1000000;in++)
                if(ram[in][0] != 0)
                    if (ram[in][1] == 0)
                    {
                        if(ram[in][0] == 677977)
                            ram[in][1] =1;
                        else if(ram[ram[in][0]][1] !=0)
                            ram[in][1] =ram[ram[in][0]][1] + 1;
                        else
                            x++;
                    }
        for(;in<1000000;in++)
            y+=ram[in][1];
        printf("%d\n",y);
    }
    else
    {
        in=836578;
        for(x=0;in != 677977;x++)
        {
            in=ram[in][0];
            ram[in][1] = x;
        }
        in=897985;
        for(x=0;in != 677977;x++)
        {
            in=ram[in][0];
            if(ram[in][1])
            {
                printf("%d\n", ram[in][1]+x);
                break;
            }
            ram[in][1] = x;
        }
    }
}


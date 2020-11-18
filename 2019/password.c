#include <stdio.h>
#include <string.h>

int checkpass1(unsigned char guess[6]);
int checkpass2(unsigned char guess[6]);

int main (int argc, char * argv[])
{
    unsigned char start[6];
    unsigned char end[6];
    int answer=0;
    char part=1;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    fscanf(fp, "%1hhu%1hhu%1hhu%1hhu%1hhu%1hhu-%1hhu%1hhu%1hhu%1hhu%1hhu%1hhu", &start[0],&start[1],&start[2],&start[3],&start[4],&start[5],&end[0],&end[1],&end[2],&end[3],&end[4],&end[5]);
    for(int i=1;i<6;i++)
        if(start[i]<start[i-1])
            for(;i<6;i++)
                start[i]=start[i-1];
    for(;start[0] < 10;start[1]=start[0]++) // TODO modify loop to run on i (work for any length pass)
        for(;start[1] <  10;start[5]=start[4]=start[3]=start[2]=++start[1])
            for(;start[2] <  10;start[5]=start[4]=start[3]=++start[2])
                for(;start[3] <  10;start[5]=start[4]=++start[3])
                    for(;start[4] <  10;start[5]=++start[4])
                        for(;start[5] < 10;++start[5])
                            if (memcmp(start, end, 6) >= 0)
                            {
                                printf("%d\n", answer);
                                return 0;
                            }
                            else if(((part==1)&&checkpass1(start))||((part==2)&&checkpass2(start)))
                                answer++;
    return 1;
}

int checkpass2(unsigned char guess[6])
{
    if(((guess[0] == guess[1]) && (guess[1] != guess[2])) || ((guess[4] == guess[5]) && (guess[3] != guess[4])) || ((guess[3] == guess[4]) && (guess[3] != guess[2]) &&(guess[3] !=guess[5])) \
    || ((guess[3] == guess[2]) && (guess[1] != guess[2]) &&(guess[4] !=guess[3])) || ((guess[1] == guess[2]) && (guess[1] != guess[0]) &&(guess[1] !=guess[3])))
        return 1;
    return 0;
}

int checkpass1(unsigned char guess[6])
{
    if((guess[0] != guess[1]) &&(guess[2] != guess[1]) &&(guess[2] != guess[3]) &&(guess[3] != guess[4]) &&(guess[4] != guess[5]))
        return 0;
    return 1;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadram(FILE *fp);
int runcompute(int halt,short ram[1000][3]);

short ram[1000][3];
int acc;

int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    int halt,i=0;
    short ram2[1000][3];
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
    halt=loadram(fp);
    if(part==1)
        runcompute(halt,ram);
    else
    {
        while(1)
        {
            memcpy(ram2,ram,3000*sizeof(short));
            acc=0;
            if(ram2[i][0]==0) ram2[i][0]=2;
            else if(ram2[i][0]==2) ram2[i][0]=0;
            if(!runcompute(halt,ram2))
                break;
            i++;
        }
    }
    printf("%d\n",acc);
    return 0;
}

int loadram(FILE *fp)
{
    char buf[16];
    int counter=0;
    while(fgets(buf, 16, fp) != NULL)
    {
        if(strncmp(buf, "nop",3)==0)
            ram[counter][0]=0;
        if(strncmp(buf, "acc",3)==0)
            ram[counter][0]=1;
        if(strncmp(buf, "jmp",3)==0)
            ram[counter][0]=2;
        ram[counter][1]=strtol(buf+3,NULL,10);
        counter++;
    }
    return counter;
}
int runcompute(int halt, short ram[1000][3])
{
    int pc=0;
    while(1)
    {
        if(pc>=halt) //EOF
            break;
        if(ram[pc][2]) //loop detection
            break;
        ram[pc][2]=1;
        switch(ram[pc][0])
        {
          case 0:
            pc++;
            break;
          case 1:
            acc+=ram[pc][1];
            pc++;
            break;
          case 2:
             pc+=ram[pc][1];
             break;
          default :
//            fprintf(stderr, "unidentified opcode");
            return -1;
        }
    }
    return pc-halt;
}

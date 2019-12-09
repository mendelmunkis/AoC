#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#define RAM_SIZE 80000
#define MAX_PARAMS 3
#define INFILE   "program.ic"
#define CUSTOM_OPS
//#define PROTECTED_MEMORY

char ascii=0;
//registers
int inc =0; //instructions executed counter
char halt = 0;
int offset = 0;
int reg1, reg2, reg3;

void loadram( FILE * fp, long ram[]);
int  getinput(void);
void intoutput(long output);
void runcompute(long  ram[], int ip);

int main (int argc, char *argv[])
{
    if((argc == 2)&&(!strcmp(argv[1],"a")))
        ascii=1;
    FILE * fp;
    if((fp = fopen (INFILE, "r")) == NULL)
    {
        printf("Error opening file %s\n", INFILE);
        return 1;
    }
    long  ram[RAM_SIZE];
    loadram(fp, ram);
    runcompute(ram, 0);
    return(0);
}

int getinput(void)
{
    int in = 1;
    scanf("%d", &in);
    return in;
}

void intoutput(long output)
{
    if (ascii)
        printf("%c\n", output);
    else
        printf("%ld\n", output);
}

void loadram( FILE * fp, long ram[])
{
    char buf[30000], *buf2;
    int in = 0;
    while(fgets(buf, 30000, fp) != NULL)
    {
        for(buf2 = strtok(buf, ","); buf2 ; buf2 = strtok(NULL, ","))
        {
            ram[in] = atol(buf2);
            in++;
        }
    }
    rewind(fp);
}


void runcompute( long ram[],  int ip)
{
    int inp = 0;
    long p[MAX_PARAMS +1]  = {0};
    int x =1;
    long param, temp;
    while(halt !=1)
    {
        inc +=1;
        while(x < MAX_PARAMS+1)
        {
            temp =  ((int)(ram[ip] / (pow(10,x+1))) % 10);
            param=ram[ip+x];
            p[x] = ( temp ? temp == 2 ? param+offset : ip+x :  ((param > RAM_SIZE)||(param < 0) ? RAM_SIZE :param));
            x++;
        }
        x=1;

        if(ip > RAM_SIZE)
            printf("Out of Memory.\n");
        switch(ram[ip] % 100)
        {
            case  1: //add
                ram[p[3]] = (ram[p[1]]+ram[p[2]]);
                ip+=4;
                break;
            case  2: // mult
                ram[p[3]]= (ram[p[1]]*ram[p[2]]);
                ip+=4;
                break;
            case  3: //read
                ram[p[1]] = getinput();
                ip+=2;
                inp++;
                break;
            case  4: // write
                intoutput(ram[p[1]]);
                ip+=2;
                break;
            case  5: //jnz
                if(ram[p[1]])
                    ip=(ram[p[2]]);
                else
                    ip+=3;
                break;
            case  6: //jne
                if(ram[p[1]])
                    ip+=3;
                else
                    ip=(ram[p[2]]);
                break;
            case  7: //lt
                    ram[p[3]]= (ram[p[1]]  <  ram[p[2]] )? 1 :0;
                    ip+=4;
                    break;
            case  8: //eq
                    ram[p[3]]= (ram[p[1]]  ==  ram[p[2]]) ? 1 :0;
                    ip+=4;
                    break;
            case  9: //offset
                    offset +=ram[p[1]];
                    ip+=2;
                    break;
#ifdef CUSTOM_OPS
            case 0: //nop
                   ip++;
                   break;
            case 90: //call
                    runcompute(ram, ram[p[1]]);
                    ip+=2;
                    break;
            case 92: // fork
                    if(fork())
                        ip+=2;
                    else
                        ip=ram[p[1]];
                    break;
            case 93: // fork thread
            case 94: // call child
            case 95: // call parent
                   printf("Opcode %ld not yet implemented.\n", ram[ip] % 100);
                   return;
            case 99: //halt
                    halt = 1;
            case 91://ret
                   return;
#endif
#ifndef CUSTOM_OPS
            case 99:
                halt =1;
                return;
#endif
            default:
                printf("Error invalid opcode %ld. ip: %ld, inc: %ld\n", ram[ip], ip, inc);
                exit(1);
        }
    }
}

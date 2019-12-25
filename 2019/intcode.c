#include "intcode.h"

int inc =0; //instructions executed counter
char halt;
int offset = 0;

int defaultinput(void)
{
    int in = 1;
    scanf("%d", &in);
    return in;
}

void defaultoutput(long output, char ascii)
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
    halt=0;
    offset=0;
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
                sendoutput(ram[p[1]]);
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

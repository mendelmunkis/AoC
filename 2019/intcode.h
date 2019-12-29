#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#define RAM_SIZE 80000
#define MAX_PARAMS 3
//#define CUSTOM_OPS
//#define PROTECTED_MEMORY

void loadram( FILE * fp, long ram[]);
int  defaultinput(void);
int  getinput(void);
void defaultoutput(long output, char ascii);
void sendoutput(long output);
void runcompute(long  ram[], int *ipp);

char halt;

#include <time.h>

#define START float starttime = (float)clock()/(CLOCKS_PER_SEC/1000);
float endtime;
#define TIME endtime-starttime
#define END endtime = (float)clock()/(CLOCKS_PER_SEC/1000); printf("%f ms\n",TIME);

//unsigned long long start; asm volatile ("rdtsc" : "=A" (start));

#include <time.h>

#define START float starttime = (float)clock()/(CLOCKS_PER_SEC/1000);
#define END float endtime = (float)clock()/(CLOCKS_PER_SEC/1000);
#define TIME endtime-starttime

//unsigned long long start; asm volatile ("rdtsc" : "=A" (start));

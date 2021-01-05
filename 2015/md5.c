#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ROT(x,y) ((x << y) | (x >> (32 - y)))
#define BYTESWAP(x) x=((x&0xff)<<24)+((x&0xff00)<<8)+((x&0xff0000)>>8)+((x&0xff000000)>>24);

uint32_t k[64]={
0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

uint32_t md5(uint32_t message[16], char fresh);
uint32_t f(uint32_t b, uint32_t c, uint32_t d);
uint32_t g(uint32_t b, uint32_t c, uint32_t d);
uint32_t h(uint32_t b, uint32_t c, uint32_t d);
uint32_t e(uint32_t b, uint32_t c, uint32_t d);


int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=0;
    int part=1;
    char buf[16];
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
    uint32_t message[16]={0};
    uint32_t len=0,ans,out=0x1000;
    char input[500];
    while(fgets(buf, 16, fp) != NULL)
    {
        for(int i=0;buf[i];i++)
        {
            message[i/4]+=(uint32_t)buf[i]<<24-((i%4)*8);
        }
        len=strlen(buf);
        message[(len)/4]+=1<<(31-((len%4)*8));
    }
    if(len>=0x20000000)
    {
        message[15]=(len-0x20000000)*8;
        len-=0x20000000;
    }
    message[14]=len*8;
//    message[0]=1<<31;
    for(int i=0; i<14; i++)
    {
        BYTESWAP(message[i]);
    }

//    message[0]=128;
//    printf("%ld\n",message[0]);
//    message[14]=6;
    ans=md5(message, 1);
    if(part==2)
        out=0x100;
    for(long i=1;ans>=out;result=i++)
    {
        memset(message,0,16*sizeof(uint32_t));
        snprintf(input,450,"%s%d",buf,i);
        for(int j=0;input[j];j++)
        {
            message[j/4]+=(uint32_t)input[j]<<((j%4)*8);
        }
        len=strlen(input);
        message[(len)/4]+=1<<(((len)%4)*8+7);
    message[14]=len*8;
//    printf("%ld\n",message[0]);
/*        for(int j=0; j<14; j++)
        {
            BYTESWAP(message[j]);
        }
*/        ans=md5(message, 1);
        result=i;
    }

//    printf("%lX\n",ans);
    printf("%ld\n",result);
//    printf("%ld\n",message[0]);
    return 0;
}

uint32_t md5(uint32_t message[16], char fresh)
{
    static uint32_t a,b,c,d;
    uint32_t aa,bb,cc,dd, temp;
    int j;
    if(fresh)
    {
        a=0x67452301;
        b=0xefcdab89;
        c=0x98badcfe;
        d=0x10325476;
    }
    aa=a;
    bb=b;
    cc=c;
    dd=d;
    for(int i=0;i<16;i++)
    {
        j=7+((i%4)*5);
        temp=a+f(b,c,d)+message[i]+k[i];
        a=b+ROT(temp,j);
        temp=a; a=d; d=c; c=b; b=temp;
    }
    for(int i=0;i<16;i++)
    {
        switch(i%4)
        {
            case 0: j=5; break;
            case 1: j=9; break;
            case 2: j=14; break;
            case 3: j=20; break;
        }
        temp=a+g(b,c,d)+message[(1+(5*i))%16]+k[i+16];
        a=b+ROT(temp,j);
        temp=a; a=d; d=c; c=b; b=temp;
    }
    for(int i=0;i<16;i++)
    {
        switch(i%4)
        {
            case 0: j=4; break;
            case 1: j=11; break;
            case 2: j=16; break;
            case 3: j=23; break;
        }
        temp=a+h(b,c,d)+message[(5+(3*i))%16]+k[i+32];
        a=b+ROT(temp,j);
        temp=a; a=d; d=c; c=b; b=temp;
    }
    for(int i=0;i<16;i++)
    {
        switch(i%4)
        {
            case 0: j=6; break;
            case 1: j=10; break;
            case 2: j=15; break;
            case 3: j=21; break;
        }
        temp=a+e(b,c,d)+message[(7*i)%16]+k[i+48];
        a=b+ROT(temp,j);
        temp=a; a=d; d=c; c=b; b=temp;
    }
    a+=aa;
    b+=bb;
    c+=cc;
    d+=dd;
    BYTESWAP(a);
    return a;
}

uint32_t f(uint32_t b, uint32_t c, uint32_t d)
{
    c&=b;
    d&=~b;
    return c|d;
}

uint32_t g(uint32_t b, uint32_t c, uint32_t d)
{
    b&=d;
    c&=~d;
    return c|b;
}

uint32_t h(uint32_t b, uint32_t c, uint32_t d)
{
    b^=c;
    return b^d;
}

uint32_t e(uint32_t b, uint32_t c, uint32_t d)
{
    b|=~d;
    return c^b;
}

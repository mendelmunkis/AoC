#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#define vabs(x) __builtin_ia32_pabsd128(x)
#define THREADED
typedef int vec4i __attribute__((vector_size(4*sizeof(int))));

long period[3]={0,0,0};

void *vup(void *in);
long long bgcd( long u, long v);

int main (int argc, char *argv[])
{
    char part=1;
    FILE * fp;
    if((fp = fopen (argv[1], "r"))==NULL)
        printf("error opening file\n");
    if((argc == 3) &&(argv[2][0] == '2'))
        part++;
    vec4i  pot,ken,a,b,c;
    long x,y,z,gcd;
    long long tot=0;
    char bufa[23], *bufb;
    pthread_t xthread,ythread,zthread;
    int p[4][3];
    vec4i xp,xv,yp,yv,zp,zv;
    for(x=0;x<4;x++)
    {
        fgets(bufa,23,fp);
        bufb=strtok(bufa+3,",");
        p[x][0]=atoi(bufb);
        bufb=strtok(NULL,",");
        p[x][1]=atoi(bufb+3);
        bufb=strtok(NULL,">");
        p[x][2]=atoi(bufb+3);
    }
    for(x=0;x<4;x++)
    {
        xp[x]=p[x][0];
        yp[x]=p[x][1];
        zp[x]=p[x][2];
        xv[x]=yv[x]=zv[x]=0;
    }
    if(part ==1)
    {
        for(x=0;x<1000;x++)
        {
            a=__builtin_ia32_pshufd(xp, 147);
            b=__builtin_ia32_pshufd(yp, 147);
            c=__builtin_ia32_pshufd(zp, 147);
            for(y=0;y<3;y++)
            {
                xv+=-(xp<a);
                xv+=xp>a;
                yv+=-(yp<b);
                yv+=yp>b;
                zv+=-(zp<c);
                zv+=zp>c;
                a=__builtin_ia32_pshufd(a, 147);
                b=__builtin_ia32_pshufd(b, 147);
                c=__builtin_ia32_pshufd(c, 147);
            }
            xp+=xv;
            yp+=yv;
            zp+=zv;
        }
        tot=0;
        {
            pot=vabs(xp)+vabs(yp)+vabs(zp);
            ken=vabs(xv)+vabs(yv)+vabs(zv);
            xp=pot*ken;
        }
        for(x=0;x<4;x++)
            tot+=xp[x];
    }else
    {
#ifdef THREADED
        pthread_create(&xthread,NULL,vup,&xp);
        pthread_create(&ythread,NULL,vup,&yp);
        pthread_create(&zthread,NULL,vup,&zp);
        pthread_join(xthread, NULL);
        pthread_join(ythread, NULL);
        pthread_join(zthread, NULL);
#else
        vup(&xp);
        vup(&yp);
        vup(&zp);
#endif
        x=period[0];
        y=period[1];
        z=period[2];
        gcd=bgcd(x,y);
        tot=((x*y)/gcd);
        gcd=bgcd(tot,z);
        tot=((tot*z)/gcd);
    }
    printf("%lld\n",tot);
}

void *vup(void *in)
{
    vec4i *input=(vec4i *)in;
    vec4i axis = *input;
    vec4i a,v ={0,0,0,0};
    static int z=0;
    long x;
    for(x=0;x<3;x++)
    {
        a=__builtin_ia32_pshufd(axis, 147);
        for(int y =0;y<3;y++)
        {
            v+=-(axis<a);
            v+=axis>a;
            a=__builtin_ia32_pshufd(a, 147);
        }
        axis+=v;
    }
    for(;((v[0]|v[1]|v[2]|v[3])!=0);x++)
    {
        a=__builtin_ia32_pshufd(axis, 147);
        for(int y =0;y<3;y++)
        {
            v+=-(axis<a);
            v+=axis>a;
            a=__builtin_ia32_pshufd(a, 147);
        }
        axis+=v;
    }
    x*=2;
    period[z]=x;
    z++;
    return NULL;
}


long long bgcd ( long u, long v) // function copied from wikipedia
{
    unsigned long shift = 0;

    /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
//    if (u == 0) return v;
//    if (v == 0) return u;
 
    /* Let shift := lg K, where K is the greatest power of 2
        dividing both u and v. */
    while (((u | v) & 1) == 0) {
        shift++;
        u >>= 1;
        v >>= 1;
    }
 
    while ((u & 1) == 0)
        u >>= 1;
 
    /* From here on, u is always odd. */
    do {
        /* remove all factors of 2 in v -- they are not common */
        /*   note: v is not zero, so while will terminate */
        while ((v & 1) == 0)
            v >>= 1;

        /* Now u and v are both odd. Swap if necessary so u <= v,
            then set v = v - u (which is even). For bignums, the
             swapping is just pointer movement, and the subtraction
              can be done in-place. */
        if (u > v) {
            unsigned long t = v; v = u; u = t; // Swap u and v.
        }
       
        v -= u; // Here v >= u.
    } while (v != 0);

    /* restore common factors of 2 */
    return u << shift;
}

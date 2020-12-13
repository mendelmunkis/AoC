#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

long long inverse(long long a, long long n);


int main (int argc, char * argv[])
{
    char *filename = "input";
    unsigned long long result=0;
    int part=1;
    char buf[200];
    unsigned long long bus[15]={0};
    unsigned long long mod[15];
    char *busp;
    long origin;
    unsigned long long mult=1,sum;
    int i=0,y=0,flag=0,wait=876543;
    mpz_t a,b,c,tot,tot2;
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
    fgets(buf, 16, fp);
    origin=strtol(buf,NULL,10);
    fgets(buf, 200, fp);
    busp=strtok(buf,",");
    bus[i]=strtol(busp,NULL,10);
    mult=bus[i];
    while((busp=strtok(NULL,","))!=NULL)
    {
        y++;
        if(bus[i])
            i++;
        bus[i]=strtol(busp,NULL,10);
        if(part==2)
            if(bus[i])
            {
                mult*=bus[i];
                mod[i]=bus[i]-y;
            }
    }
    if(part==1)
    {
        for(i=0;bus[i];i++)
            if((bus[i]-(origin%bus[i]))<wait)
            {
                wait=(bus[i]-(origin%bus[i]));
                result=wait*bus[i];
            }
    }
    else
    {
        mpz_init(a);
        mpz_init(b);
        mpz_init(c);
        mpz_init(tot);
        mpz_init(tot2);
        for(i=1;bus[i];i++)
        {
            sum=inverse(mult/bus[i],bus[i]);
            mpz_import(a, 1, -1, sizeof sum, 0, 0, &sum);
            mpz_set_ui(b,mod[i]);
            mpz_set_ui(c,(mult/bus[i]));
            mpz_set_ui(tot,0);
            mpz_mul(tot,a,b);
            mpz_mod_ui(tot,tot,mult);
            mpz_mul(tot,tot,c);
            mpz_mod_ui(tot,tot,mult);
            mpz_add(tot2,tot2,tot);
            mpz_mod_ui(tot2,tot2,mult);
        }
        mpz_out_str(stdout,10,tot2);
        printf("\n");
    }
    if(part==1)
        printf("%llu\n",result);
    return 0;
}

long long inverse(long long a, long long n)
{
    long long t=0,nt=1;
    long long r=n,nr=a;
    long long q,temp;
    while(nr)
    {
        q = r/nr;
        temp=t;
        t=nt;
        nt=temp-(q*nt);
        temp=r;
        r=nr;
        nr=temp-(q*nr);
    }

    if (t<0)
        t+=n;

    return t;
}

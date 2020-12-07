#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hash(char* str, int *modif, int*color);
int recurse(int modif, int color);

int bags[19][34][120]={0};
int outsides[19][34]={0};
int part=1;


int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    char buf[260];
    char *ip;
    int modif,outmodif,color,outcolor;
    int z, subbags;
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
    while(fgets(buf, 260, fp) != NULL)
    {
        z=0;
        hash(buf,&outmodif,&outcolor);
        strtok(NULL, " \n");
        while((ip=strtok(NULL, " \n"))!=NULL)
        {
            hash(NULL,&modif,&color);
            if(part==1)
            {
                for(z=0;bags[modif][color][z];z++);
                bags[modif][color][z]=outmodif;
                bags[modif][color][z+1]=outmodif;
                bags[modif][color][z+2]=outcolor;
        }
            else{
                subbags=strtol(ip,NULL,10);
                bags[outmodif][outcolor][z]=subbags;
                bags[outmodif][outcolor][z+1]=modif;
                bags[outmodif][outcolor][z+2]=color;
            }
            z+=3;
        }
    }
    result=recurse(18,33);
    outsides[18][33]=0;
    if(part==1)
    {
        result=0;
        for(int a=0;a<19;a++)
            for(int b=0;b<34;b++)
                if(outsides[a][b])
                    result++;
    }
    printf("%d\n",result);
    return 0;
}

void hash(char* str, int *modif, int *color)
{
    char *ip;
    ip=strtok(str, " \n");
    switch(ip[0])
    {
      case 'b' :
        *modif=1;
        break;
      case 'c' :
        *modif=2;
        break;
      case 'd' :
        if(!strcmp(ip,"dark"))
            *modif=3;
        else if(!strcmp(ip,"dim"))
            *modif=4;
        else if(!strcmp(ip,"dotted"))
            *modif=5;
        else if(!strcmp(ip,"drab"))
            *modif=6;
        else if(!strcmp(ip,"dull"))
            *modif=7;
        break;
      case 'f' :
        *modif=8;
        break;
      case 'l' :
        *modif=9;
        break;
      case 'm' :
        if(!strcmp(ip,"mirrored"))
            *modif=10;
        else if(!strcmp(ip,"muted"))
            *modif=11;
        break;
      case 'p' :
        if(!strcmp(ip,"pale"))
            *modif=12;
        else if(!strcmp(ip,"plaid"))
            *modif=13;
        else if(!strcmp(ip,"posh"))
            *modif=14;
        break;
      case 's' :
        if(!strcmp(ip,"shiny"))
            *modif=18;
        else if(!strcmp(ip,"striped"))
            *modif=15;
        break;
      case 'v' :
        *modif=16;
        break;
      case 'w' :
        *modif=17;
        break;
      default :
        *modif=*color=0;
        strtok(NULL,"\n");
        return;
    }
    ip=strtok(NULL, " \n");
    if(!strcmp(ip,"aqua"))
        *color=1;
    else if(!strcmp(ip,"beige"))
        *color=2;
    else if(!strcmp(ip,"black"))
        *color=3;
    else if(!strcmp(ip,"blue"))
        *color=4;
    else if(!strcmp(ip,"bronze"))
        *color=5;
    else if(!strcmp(ip,"brown"))
        *color=6;
    else if(!strcmp(ip,"chartreuse"))
        *color=7;
    else if(!strcmp(ip,"coral"))
        *color=8;
    else if(!strcmp(ip,"crimson"))
        *color=9;
    else if(!strcmp(ip,"cyan"))
        *color=10;
    else if(!strcmp(ip,"fuchsia"))
        *color=11;
    else if(!strcmp(ip,"gold"))
        *color=33;
    else if(!strcmp(ip,"gray"))
        *color=12;
    else if(!strcmp(ip,"green"))
        *color=13;
    else if(!strcmp(ip,"indigo"))
        *color=14;
    else if(!strcmp(ip,"lavender"))
        *color=15;
    else if(!strcmp(ip,"lime"))
        *color=16;
    else if(!strcmp(ip,"magenta"))
        *color=17;
    else if(!strcmp(ip,"maroon"))
        *color=18;
    else if(!strcmp(ip,"olive"))
        *color=19;
    else if(!strcmp(ip,"orange"))
        *color=20;
    else if(!strcmp(ip,"plum"))
        *color=21;
    else if(!strcmp(ip,"purple"))
        *color=22;
    else if(!strcmp(ip,"red"))
        *color=23;
    else if(!strcmp(ip,"salmon"))
        *color=24;
    else if(!strcmp(ip,"silver"))
        *color=25;
    else if(!strcmp(ip,"tan"))
        *color=26;
    else if(!strcmp(ip,"teal"))
        *color=27;
    else if(!strcmp(ip,"tomato"))
        *color=28;
    else if(!strcmp(ip,"turquoise"))
        *color=29;
    else if(!strcmp(ip,"violet"))
        *color=30;
    else if(!strcmp(ip,"white"))
        *color=31;
    else if(!strcmp(ip,"yellow"))
        *color=32;
    strtok(NULL, " \n");
    return;
}

int recurse(int modif, int color)
{
    int counter=0;
    if(part==1)
    {
        if(outsides[modif][color])
            return 0;
        outsides[modif][color]=1;
    }
    if (part==2)
        if (bags[modif][color][1]==0)
            return 0;
    for(int z=0;bags[modif][color][z+1]!=0;z+=3)
        counter+=(recurse(bags[modif][color][z+1],bags[modif][color][z+2])+1)*bags[modif][color][z];
    return counter;
}

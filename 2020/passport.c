#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct passportdata {
    int  byr;
    int  iyr;
    int  eyr;
    char ecl[4];
    char hgt[6];
    int  hcl;
    long pid;
    int  cid;
};

int main (int argc, char * argv[])
{
    char *filename = "input";
    int result=0;
    int part=1;
    char buf[100];
    static struct passportdata passports[500]={0};
    FILE * fp;

    int x=0,i=0;
    char *field;
    char tempstr[10];
    int len, temp, f;

    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    if(part==1)
        while(fgets(buf, 100, fp) != NULL)
        {
            field=buf;
            if(buf[0]=='\n')
                x++;
            else
                while(*field !='\n')
                {
                     if(strncmp(field, "byr", 3)==0)
                     {
                         passports[x].byr=1;
                         field+=1;
                     }
                     else if(strncmp(field, "cid", 3)==0)
                     {
                         passports[x].cid=1;
                         field+=1;
                     }
                     else if(strncmp(field, "ecl", 3)==0)
                     {
                         passports[x].ecl[0]='a';
                        field+=1;
                     }
                     else if(strncmp(field, "eyr", 3)==0)
                     {
                         passports[x].eyr=1;
                         field+=1;
                     }
                     else if(strncmp(field, "hcl", 3)==0)
                     {
                         field+=1;
                         passports[x].hcl=1;
                     }
                     else if(strncmp(field, "hgt", 3)==0)
                     {
                         passports[x].hgt[0]='a';
                         field+=1;
                     }
                     else if(strncmp(field, "iyr", 3)==0)
                     {
                         passports[x].iyr=1;
                         field+=1;
                     }
                     else if(strncmp(field, "pid", 3)==0)
                     {
                         passports[x].pid=1;
                         field+=1;
                     }
                     else field++;

                }
        }
    else
    input :
        while(fgets(buf, 100, fp) != NULL)
        {
            field=buf;
            if(buf[0]=='\n')
                x++;
            else
                while(*field !='\n')
                {
                 if(strncmp(field, "byr", 3)==0)
                 {
                     for(i=4;i<8;i++)
                         if(!isdigit(*(field+i)))
                             goto input;
                     temp=strtol(field+4,NULL,10);
                     if((temp>=1920)&&(temp<=2002))
                         passports[x].byr=temp;
                     field+=7;
                 }
                 else if(strncmp(field, "cid", 3)==0)
                 {
                     for(i=4;i<7;i++)
                         if(!isdigit(*(field+i)))
                             goto end;
                     passports[x].cid=strtol(field+4,NULL,10);
                     field+=6;
end :
                     field++;
                 }
                 else if(strncmp(field, "ecl", 3)==0)
                 {
                     strncpy(tempstr,field+4,3);
                     if(!((strncmp(tempstr, "amb", 3)==0)||(strncmp(tempstr, "blu", 3)==0)||
                     (strncmp(tempstr, "brn", 3)==0)||(strncmp(tempstr, "gry", 3)==0)||
                     (strncmp(tempstr, "grn", 3)==0)||(strncmp(tempstr, "hzl", 3)==0)||
                     (strncmp(tempstr, "oth", 3)==0)))
                             goto input;
                     strncpy(passports[x].ecl,tempstr,3);
                     passports[x].ecl[3]='\0';
                     field+=7;
                 }
                 else if(strncmp(field, "eyr", 3)==0)
                 {
                     for(i=4;i<8;i++)
                         if(!isdigit(*(field+i)))
                             goto input;
                     temp=strtol(field+4,NULL,10);
                     if((temp>=2020)&&(temp<=2030))
                         passports[x].eyr=temp;
                     field+=8;
                 }
                 else if(strncmp(field, "hcl", 3)==0)
                 {
                     field+=4;
                     strncpy(tempstr,field,7);
                     if(*field != '#')
                     {
                         goto input;
                     }
                     else
                     {
                         field++;
                         f=0;
                         for(i=0;i<6;i++)
                             if(!isxdigit(*(field+i)))
                             {
                                 goto input;
                             }
                         passports[x].hcl=strtol(field,NULL,16);
                         field+=6;
                     }
                 }
                 else if(strncmp(field, "hgt", 3)==0)
                 {
                     field+=4;
                     if(strncmp(field+2, "in", 2)==0)
                     {
                         temp=strtol(field,NULL,10);
                         if((temp<59)||(temp>76))
                             goto input;
                         strncpy(passports[x].hgt,field,4);
                         passports[x].hgt[4]='\0';
                     }
                     else if(strncmp(field+3, "cm", 2)==0)
                     {
                         temp=strtol(field,NULL,10);
                         if((temp<150)||(temp>193))
                             goto input;
                         strncpy(passports[x].hgt,field,5);
                         passports[x].hgt[5]='\0';
                     }
                     field++;
                 }
                 else if(strncmp(field, "iyr", 3)==0)
                 {
                     f=0;
                     for(i=4;i<8;i++)
                         if(!isdigit(*(field+i)))
                             goto input;
                     temp=strtol(field+4,NULL,10);
                     if((temp<2010)||(temp>2020))
                             goto input;
                     passports[x].iyr=temp;
                     field+=8;
                 }
                 else if(strncmp(field, "pid", 3)==0)
                 {
                     field+=4;
                     for(i=0;i<9;i++)
                         if(!isdigit(*(field+i)))
                             goto input;
                         if(isdigit(*(field+9)))
                             goto input;
                     temp=strtol(field,NULL,10);
                     passports[x].pid=temp;
                     field+=8;
                 }
                 else field++;

            }
        }
    for(x=0;x<500;x++)
       if(passports[x].byr && passports[x].iyr
          && passports[x].eyr && passports[x].pid
          && passports[x].ecl[0] && passports[x].hcl
          && passports[x].hgt[0])
            result++;
    printf("%d\n",result);
    return 0;
}

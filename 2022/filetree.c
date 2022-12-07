#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dir
{
    long size;
    char map[50][20];
    struct dir *children[50];
    struct dir *parent;
};

int size(struct dir * dir);
void walk(struct dir * dir);

long result=0;
int part=1;
int total=70000000;
int needed=30000000;

int main (int argc, char * argv[])
{
    char *filename = "input";
    char buf[25];
    struct dir root;
    struct dir *current = &root;
    memset(current,0,sizeof(struct dir));
    int x;
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
    while(fgets(buf, 25, fp) != NULL)
    {
        if(buf[0]=='$')
        {
            if(buf[2] == 'l')
                continue;
            switch(buf[5])
            {
              case '.':
                current=current->parent;
                break;
              case '/':
                current=&root;
                break;
              default :
                for(x=0;strncmp(buf+5,current->map[x],20);x++);
                //assumes null = 0
                current->children[x]=calloc(1,sizeof(struct dir));
                current->children[x]->parent=current;
                current=current->children[x];
            }
        }
        else
        {
            if(buf[0]=='d')
            {
                for(x=0;current->map[x][0]!='\0';x++);
                strncpy(current->map[x],buf+4,20);
            }
            else
                current->size+=atoi(buf);
        }
    }
    needed-=(total-size(&root));
    if(part==2)
        result=total;
    walk(&root);
    printf("%ld\n",result);
    return 0;
}


int size(struct dir * dir)
{
    for(int i=0; dir->map[i][0]!='\0';i++)
        dir->size+=size(dir->children[i]);
    return dir->size;
}

void walk(struct dir * dir)
{
    for(int i=0; dir->map[i][0]!='\0';i++)
        walk(dir->children[i]);
    if(part==1)
        if(dir->size<100000)
            result+=dir->size;
    if(part==2)
        if(dir->size>=needed && dir->size<result)
            result=dir->size;
}


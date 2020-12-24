#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matchsort (const void *a, const void *b);
void char_rev(char *base, size_t nmeb);
void flip(char *grid, int axis, int size);
void rot(char *grid, int direction, int size);

struct tile
{
    char grid[10][10];
    char edges[8][10];
    long matches;
    int tid;
};

int main (int argc, char * argv[])
{
    char *filename = "input";
    long result=1;
    int part=1, flag;
    char buf[16];
    FILE * fp;
    struct tile grid[12][12]={0};
    struct tile array[144];
    struct tile *arptr=array;
    char image[96][96];
    int monsters=0;
    int tile=0, tiles, arraysize;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen (filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 16, fp) != NULL)
    {
        array[tile].tid=strtol(buf+5,NULL,10);
        for(int i=0;i<10;i++)
        {
            fgets(buf, 16, fp);
            for(int j=0;j<10;j++)
                if(buf[j]=='.')
                    array[tile].grid[i][j]=0;
                else
                    array[tile].grid[i][j]=1;
        }
        tile++;
        fgets(buf, 16, fp);
    }
    tiles=tile;
    for(tile=0;tile<144;tile++)
        for(int i=0;i<10;i++)
        {
            array[tile].edges[0][i]=array[tile].grid[0][i];
            array[tile].edges[1][i]=array[tile].grid[9][i];
            array[tile].edges[2][i]=array[tile].grid[i][0];
            array[tile].edges[3][i]=array[tile].grid[i][9];
            array[tile].edges[4][i]=array[tile].grid[0][9-i];
            array[tile].edges[5][i]=array[tile].grid[9][9-i];
            array[tile].edges[6][i]=array[tile].grid[9-i][0];
            array[tile].edges[7][i]=array[tile].grid[9-i][9];
        }
    for(tile=0;tile<tiles;tile++)
    {
        for(int i=0;i<tiles;i++)
        {
            flag=0;
            if(i==tile)
                continue;
            for(int j=0;j<8;j++)
                if ( !memcmp(array[tile].edges[j], array[i].edges[0], 10*sizeof(char)) ||
                  !memcmp(array[tile].edges[j], array[i].edges[1], 10*sizeof(char))  ||
                  !memcmp(array[tile].edges[j], array[i].edges[2], 10*sizeof(char))  ||
                  !memcmp(array[tile].edges[j], array[i].edges[3], 10*sizeof(char))  ||
                  !memcmp(array[tile].edges[j], array[i].edges[4], 10*sizeof(char))  ||
                  !memcmp(array[tile].edges[j], array[i].edges[5], 10*sizeof(char))  ||
                  !memcmp(array[tile].edges[j], array[i].edges[6], 10*sizeof(char))  ||
                  !memcmp(array[tile].edges[j], array[i].edges[7], 10*sizeof(char))  )
                    flag=1;
            if(flag)
                array[tile].matches++;
        }
    }
    qsort(array, tiles,sizeof(struct tile), matchsort);
    if(part==1)
    {
        for(int i=0; i<4; i++)
            result*=array[i].tid;
        printf("%ld\n",result);
        return 0;
    }
    grid[0][0]=array[0];
    arptr++;
    arraysize=tiles-1;
    for(int r=0;r<12;r++)
       for(int c=0;c<12;c++)
       {
           flag=0;
           if(!c)
           {
               if(!r)
                   continue;
              if(!grid[r-1][0].tid)
                   continue;
               for(int i=0;i<arraysize;i++)
               {
                   if (!memcmp(grid[r-1][c].edges[1], arptr[i].edges[0], 10*sizeof(char)))
                       flag=1;
                   else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[1], 10*sizeof(char)))
                   {
                       flip((char *)arptr[i].grid,0,10);
                       flag=1;
                   }
                   else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[2], 10*sizeof(char)))
                   {
                       flip((char *)arptr[i].grid,0,10);
                       rot ((char *)arptr[i].grid,0,10);
                       flag=1;
                   }
                   else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[3], 10*sizeof(char)))
                   {
                       rot ((char *)arptr[i].grid,1,10);
                       flag=1;
                   }
                   else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[4], 10*sizeof(char)))
                   {
                       flip((char *)arptr[i].grid,1,10);
                       flag=1;
                   }
                   else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[5], 10*sizeof(char)))
                   {
                       flip((char *)arptr[i].grid,1,10);
                       flip((char *)arptr[i].grid,0,10);
                       flag=1;
                   }
                   else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[6], 10*sizeof(char)))
                   {
                       rot((char *)arptr[i].grid,0,10);
                       flag=1;
                   }
                   else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[7], 10*sizeof(char)))
                   {
                       flip((char *)arptr[i].grid,1,10);
                       rot((char *)arptr[i].grid,0,10);
                       flag=1;
                   }
                   if(flag)
                   {
                       grid[r][c]=arptr[i];
                       for(int j=0;j<10;j++)
                       {
                           grid[r][c].edges[0][j]=grid[r][c].grid[0][j];
                           grid[r][c].edges[1][j]=grid[r][c].grid[9][j];
                           grid[r][c].edges[2][j]=grid[r][c].grid[j][0];
                           grid[r][c].edges[3][j]=grid[r][c].grid[j][9];
                       }
                       memmove(arptr+1,arptr,i*sizeof(struct  tile));
                       arraysize--;
                       arptr++;
                       break;
                   }
               }
           }
           else
           {
               for(int i=0;i<arraysize;i++)
               {
                   if ( !memcmp(grid[r][c-1].edges[3], arptr[i].edges[0], 10*sizeof(char)) ||
                     !memcmp(grid[r][c-1].edges[3], arptr[i].edges[1], 10*sizeof(char)) ||
                     !memcmp(grid[r][c-1].edges[3], arptr[i].edges[2], 10*sizeof(char)) ||
                     !memcmp(grid[r][c-1].edges[3], arptr[i].edges[3], 10*sizeof(char)) ||
                     !memcmp(grid[r][c-1].edges[3], arptr[i].edges[4], 10*sizeof(char)) ||
                     !memcmp(grid[r][c-1].edges[3], arptr[i].edges[5], 10*sizeof(char)) ||
                     !memcmp(grid[r][c-1].edges[3], arptr[i].edges[6], 10*sizeof(char)) ||
                     !memcmp(grid[r][c-1].edges[3], arptr[i].edges[7], 10*sizeof(char)) )
                       if(r&&grid[r-1][c].tid)
                       {
                           if (!memcmp(grid[r-1][c].edges[1], arptr[i].edges[0], 10*sizeof(char)))
                               flag=1;
                           else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[1], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[2], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,0,10);
                               rot ((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[3], 10*sizeof(char)))
                           {
                               rot ((char *)arptr[i].grid,1,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[4], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,1,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[5], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,1,10);
                              flip((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[6], 10*sizeof(char)))
                           {
                               rot((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r-1][c].edges[1], arptr[i].edges[7], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,1,10);
                               rot((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                       }else
                       {
                           if (!memcmp(grid[r][c-1].edges[3], arptr[i].edges[0], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,1,10);
                               rot((char *)arptr[i].grid,1,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r][c-1].edges[3], arptr[i].edges[1], 10*sizeof(char)))
                           {
                               rot((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r][c-1].edges[3], arptr[i].edges[2], 10*sizeof(char)))
                               flag=1;
                           else if(!memcmp(grid[r][c-1].edges[3], arptr[i].edges[3], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,1,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r][c-1].edges[3], arptr[i].edges[4], 10*sizeof(char)))
                           {
                               rot((char *)arptr[i].grid,1,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r][c-1].edges[3], arptr[i].edges[5], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,1,10);
                               rot((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r][c-1].edges[3], arptr[i].edges[6], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                           else if(!memcmp(grid[r][c-1].edges[3], arptr[i].edges[7], 10*sizeof(char)))
                           {
                               flip((char *)arptr[i].grid,1,10);
                               flip((char *)arptr[i].grid,0,10);
                               flag=1;
                           }
                       }
                       if(flag)
                       {
                           grid[r][c]=arptr[i];
                           memset(grid[r][c].edges, 0, 80*sizeof(char));
                           for(int j=0;j<10;j++)
                           {
                               grid[r][c].edges[0][j]=grid[r][c].grid[0][j];
                               grid[r][c].edges[1][j]=grid[r][c].grid[9][j];
                               grid[r][c].edges[2][j]=grid[r][c].grid[j][0];
                               grid[r][c].edges[3][j]=grid[r][c].grid[j][9];
                           }
                           memmove(arptr+1,arptr,i*sizeof(struct  tile));
                           arraysize--;
                           arptr++;
                           break;
                   }
               }
           }
       }
   for(int r=0;r<12;r++)
       for(int c=0;c<12;c++)
           for(int i=1;i<9;i++)
               memcpy(&image[(8*r)+i-1][8*c],&grid[r][c].grid[i][1],8*sizeof(char));
  result=0;
  for(int i =0;!monsters;i++)
  {
      for(int r=0;r<94;r++)
          for(int c=18;c<95;c++)
              if(image[r][c] + image[r+1][c-18]+image[r+1][c-13]+
                image[r+1][c-12]+ image[r+1][c-7]+image[r+1][c-6]+
                image[r+1][c-1]+image[r+1][c]+image[r+1][c+1]+
                image[r+2][c-17]+image[r+2][c-14]+image[r+2][c-11]+
                image[r+2][c-8]+image[r+2][c-5]+image[r+2][c-2]==15)
              {
                  image[r][c]=image[r+1][c-18]=image[r+1][c-13]=
                  image[r+1][c-12]=image[r+1][c-7]=image[r+1][c-6]=
                  image[r+1][c-1]=image[r+1][c]=image[r+1][c+1]=
                  image[r+2][c-17]=image[r+2][c-14]=image[r+2][c-11]=
                  image[r+2][c-8]=image[r+2][c-5]=image[r+2][c-2]=0;
                  monsters++;
              }
      if(!(i%5))
          flip((char *)image, 0, 96);
      else
          rot((char *)image, 0, 96);
  }
  for(int r=0;r<96;r++)
      for(int c=0;c<96;c++)
          if(image[r][c])
              result++;
    printf("%ld\n",result);
    return 0;
}

int matchsort (const void *a, const void *b)
{
    const struct tile *x=a;
    const struct tile *y=b;
    if(x->matches<y->matches)
        return -1;
    if(x->matches>y->matches)
        return 1;
    if(x->tid==2971)
        return -1;
    if(y->tid==2971)
        return 1;
    if(x->tid<y->tid)
        return -1;
    if(x->tid>y->tid)
        return 1;
    printf("ERROR: Identical TIDs\n");
    return 0;
}

void char_rev(char *base, size_t nmeb)
{
    char temp;
    char *a = base, *b = base+nmeb-1;
    for(;b>a;a++,b--)
    {
        temp=*a;
        *a=*b;
        *b=temp;
    }
}

void flip(char *grid, int axis, int size)
{
    char temp[100];
    if(axis)
        for(int i=0;i<size;i++)
            char_rev(grid+i*size, size);
    else
        for(int i=0;i<size/2;i++)
        {
            memcpy(temp, grid+i*size, size*sizeof(char));
            memcpy(grid+i*size, grid+(size-i-1)*size, size*sizeof(char));
            memcpy(grid+(size-i-1)*size, temp, size*sizeof(char));
        }

}

void rot(char *grid, int direction, int size)
{
    char temp;
    int m=size-1;
    if(!direction)
        for(int r=0;r<size/2;r++)
            for(int c=0;c<size/2;c++)
            {
               temp=*(grid+r*size+c);
               *(grid+r*size+c)=*(grid+(m-c)*size+r);
               *(grid+(m-c)*size+r)=*(grid+(m-r)*size+m-c);
               *(grid+(m-r)*size+m-c)=*(grid+c*size+m-r);
               *(grid+c*size+m-r)=temp;
            }
    else
        for(int r=0;r<size/2;r++)
            for(int c=0;c<size/2;c++)
            {
               temp=*(grid+r*size+c);
               *(grid+r*size+c)=*(grid+c*size+m-r);
               *(grid+c*size+m-r)=*(grid+(m-r)*size+m-c);
               *(grid+(m-r)*size+m-c)=*(grid+(m-c)*size+r);
               *(grid+(m-c)*size+r)=temp;
            }
}

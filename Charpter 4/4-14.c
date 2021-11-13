#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<search.h>
#define NMEMB 50
#define SIZE 10
int compar(const void *a,const void *b)
{
  return (strcmp((char *) a,(char *) b));
}
int main()
{
  char data[NMEMB][SIZE]={"Linux","freebsd","solzris","windows"};
  char key[80],*base,*offset;
  int i,nmemb=NMEMB,size=SIZE;
    for(i=1;i<5;i++)
    {
      fgets(key,sizeof(key),stdin);
      key[strlen(key)-1]='\0';
      base=data[0];
      offset=(char *)lfind(key,base,&nmemb,size,compar);
      if(offset==NULL)
      {
        printf("%s not found!\n",key);
        offset=(char *)lsearch(key,base,&nmemb,size,compar);
        printf("Add %s to data array\n",offset);
      }
      else
      {
        printf("found: %s \n",offset);
        //printf("\033[5;5H%s",offset);
      }
    }
  return 0;
}

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define m 70
int compar(const void *a,const void *b)
{
  int *pa=(int *)a,*pb=(int *)b;
  if(*pa>*pb)return -1;
  if(*pa==*pb)return 0;
  if(*pa<*pb)return 1;
}

int main()
{
  int base[m],n;
  int i;
  printf("input n(n<50)\n");
  scanf("%d",&n);
  for(i=0;i<n;i++)
    scanf("%d",&base[i]);
  qsort(base,n,sizeof(int),compar);
  for(i=0;i<n;i++)
    printf("%d ",base[i]);
  printf("\n");
  return 0;
}


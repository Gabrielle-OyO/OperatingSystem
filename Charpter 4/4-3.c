#include<stdlib.h>
#include "stdio.h"
int main()
{
int i,j;
  srand((int)time(0));
  for(i=0;i<10;i++)
  {
    j=100+(int)(100.0*rand()/(RAND_MAX+1.0));
    printf(" %d",j);
  }
  printf("\n");
}

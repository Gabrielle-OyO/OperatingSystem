#include "stdio.h"
#include "math.h"
int main()
{
  int n,i;
  float x,y;
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    scanf("%f",&x);
    y=sqrt(x);
    printf("%f ********** %f\n",x,y);
  }
}

#include<stdio.h>
#include<math.h>
int mian()
{
  double a,b;
  printf("Please enter the independence variable:");
  scanf("%lf",&a);
  b=sin(a);
  printf("sin(%lf)=%lf\n",a,b);
  return 0;
}

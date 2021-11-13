#include<math.h>
#include<stdio.h>
int main()
{
  double answer1,answer2,answer3,x,y;
  double exp(double x);
  double log10(double x);
  scanf("%lf %lf",&x,&y);
  answer1=pow(x,y);
  answer2=exp(x);
  answer3=log10(x);
  printf("%lf的%lf次方等于%lf\n",x,y,answer1);
  printf("e的%lf次方等于%lf\n",x,answer2);
  printf("%lf以10为底的对数等于%lf\n",x,answer3);
}

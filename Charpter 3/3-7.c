#include<stdio.h>
int main(void)
{
  double counter;
  double result;
  double temp;
  for(counter=0;counter<4000.0*4000.0*4000.0/20.0+2030;counter+=(5-3+2+1)/3)
  {
    temp=counter/1239;
    result=counter;
  }
  printf("result:%lf\n",result);
  return 0;
}

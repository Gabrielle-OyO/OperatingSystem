#include<stdio.h>
#include<ctype.h>
int main()
{
  char c;
  int count=0;
  while((c=getchar())!='\n')
    if(isupper(c))
      printf("%c is an uppercase character\n",c);
    else if(isdigit(c))
      printf("%c is a digit\n",c);
    else if(ispunct(c))
    {
      printf("%c is a Special symbol\n",c);
      count++;
    }
  printf("Special symbol total :%d \n",count);
}

#include<string.h>
#include<stdio.h>
#include<ctype.h>
int main(void)
{
  int c;
  //user input data
  while ((c=getchar())!=EOF)
  {
    if(isupper(c))  
    {//output data as testinput's input data;
      c=tolower(c);
    }  
    if(putchar(c)==EOF)
    {
      fputs("output error\n",stdout);
    }
    if(c=='\n')
    {
      fflush(stdout);
    }
  }
    return 0;
}
      

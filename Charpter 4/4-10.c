#include<stdlib.h>
#include<stdio.h>
int main()
{
  char *p;
  if((p=getenv("USER")))
  printf("USER=%s\n",p);
  setenv("USER","text",1);
  printf("USER=%s\n",getenv("USER"));
  unsetenv("USER");
  printf("USER=%s\n",getenv("USER"));
  return 1;
}

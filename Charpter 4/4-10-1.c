#include<stdlib.h>
#include<stdio.h>
int main()
{
  extern char **environ;
  int i;
  for(i=0;environ[i]!=NULL;i++)
    printf("%s\n",environ[i]);
  return 0;
}

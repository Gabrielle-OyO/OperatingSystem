#include<stdio.h>
#include<string.h>
int main()
{
  FILE *fp;
  int num;
  char buf[5000];
  memset(buf,0,sizeof(buf));
  printf("building pipeline......\n");
  fp=popen("ps -aux","r");
  if(fp!=NULL)
  {
    num=fread(buf,sizeof(char),5000,fp);
    if(num>0)
    {
      printf("the first order is'ps -aux',result: \n");
      printf("%s\n",buf);
    }
    pclose(fp);
  }
  else
  {
    printf("using popen to create pipeline fail\n");
    return 1;
  }
  return 0;
}

